#include <ros/ros.h>
#include <move_base_msgs/MoveBaseAction.h>
#include <actionlib/client/simple_action_client.h>

#include <people_msgs/PositionMeasurement.h>
#include <people_msgs/PositionMeasurementArray.h>

#include <message_filters/subscriber.h>
#include <algorithm>
#include <tf/transform_listener.h>
#include <tf/message_filter.h>

#include <vector>
using std :: vector;
#include <geometry_msgs/Pose.h>
#include <geometry_msgs/Quaternion.h>
#include <math.h>

using geometry_msgs :: Quaternion;
using geometry_msgs :: Pose;

void people_follow();
bool compare(const people_msgs::PositionMeasurement& x, const people_msgs::PositionMeasurement& y);
void people_follow_callback(const people_msgs::PositionMeasurementArray::ConstPtr& message);
tf::StampedTransform get_base2map();

typedef actionlib :: SimpleActionClient<move_base_msgs :: MoveBaseAction> MoveBaseClient;
people_msgs::PositionMeasurement best_people;

int main(int argc , char ** argv)
{
	ros :: init (argc , argv , "people_follow");
	ros::NodeHandle n;	/**/

//订阅行人检测topic，每受到一个people_tracker_measurements消息，调用people_follow_callback函数
	ros :: Subscriber sub_people = n.subscribe("people_tracker_measurements", 1,  people_follow_callback);
	//people_follow();
	ros::spin();

	return 0;
}
/*********************************************************************************/
//行人自动跟随函数
void people_follow()
{

	//ROS_INFO("I will go to the goal!");
	double linear_speed;
	double angular_speed;

	//get odom,get  current position of robot
	tf::StampedTransform transform;
  transform = get_base2map();//获取机器人位置
	//caculate distance of robot to people计算机器人与行人目标的距离
	float delta_x = best_people.pos.x - transform.getOrigin().x();
	float delta_y = best_people.pos.y - transform.getOrigin().y();
	double dist_robot_people = sqrt(delta_x * delta_x  + delta_y * delta_y);
	double speed_val = 0.2;
/*********************************************************************************/
	//tell the action client that we want to spin a thread by default
	MoveBaseClient ac("move_base" , true);
	//wait for the action server to come up 
	while(! ac.waitForServer(ros :: Duration(5.0)))
	{
		ROS_INFO("Waiting for the move_base action server to come up");
	}
	/*createting MoveBaseActionGoal*/
	move_base_msgs :: MoveBaseGoal goal;
	goal.target_pose.header.frame_id = "map";//base_link or map
	goal.target_pose.header.stamp = ros :: Time :: now();
	
	//goal.target_pose.pose.position =  best_people.pos;//set  goal.position
	double dist_robot_goal = dist_robot_people- 0.2;//0.2m的安全距离，导航目标与行人距离0.2m
	if(dist_robot_people <= 0.2)
	{
		double yaw, pitch, roll;
		ROS_WARN("The goal is too close to robot!");//获得无效的行人目标
		goal.target_pose.pose.position.x = transform.getOrigin().x();
		goal.target_pose.pose.position.y = transform.getOrigin().y();
		transform.getBasis().getEulerYPR(yaw, pitch, roll);
		goal.target_pose.pose.orientation.w = yaw;
		//wait for the action server to come up 
		while(! ac.waitForServer(ros :: Duration(5.0)))
		{
			ROS_INFO("Waiting for the move_base action server to come up");
		}
		ac.sendGoal(goal);//sending goal
		ac.cancelGoal();
	}
	else
	{
		ROS_INFO("Recesive a valuable goal !");//获得有效的行目标
		ROS_INFO("I will go to the goal!");
//设置goal的坐标，x=(L-0.2)*dx/L，y=（L-0.2）*dy/L
		goal.target_pose.pose.position.x = transform.getOrigin().x()+ dist_robot_goal*(delta_x/dist_robot_people);
		goal.target_pose.pose.position.y = transform.getOrigin().y() + dist_robot_goal*(delta_y/dist_robot_people);
		goal.target_pose.pose.orientation.w = atan2(delta_y, delta_x);
	
		//wait for the action server to come up 等待move_base启动
		while(! ac.waitForServer(ros :: Duration(5.0)))
		{
			ROS_INFO("Waiting for the move_base action server to come up");
		}
		ac.sendGoal(goal);//sending goal发送导航目标
//allow 2 second to get there，允许2s到达目标，否则取消goal，从新产生goal
		bool finished_within_time = ac.waitForResult(ros :: Duration(4.0));
		if(!finished_within_time)
		{
			ac.cancelGoal();
			ROS_INFO("Timed out achieving goal ");//未能在2s内到达目标
		}
		else if(ac.getState() == actionlib :: SimpleClientGoalState :: SUCCEEDED)
		{
			ROS_INFO("I have go there");//成功到达目标
		}
		else
		{
			ROS_INFO("The base failed to go to people for some reason");
		}
	}
	  	
	//ros::spin();
}

/*compare function . return the highest reliability of people_array*/
//people_array排序函数，根据reliability属性从大到小排序
bool compare(const people_msgs::PositionMeasurement& x, const people_msgs::PositionMeasurement& y)
{
	return x.reliability > y.reliability;
}
void people_follow_callback(const people_msgs::PositionMeasurementArray::ConstPtr& message)//people_tracker_measurements回调函数
{
	ROS_INFO("I have received a people message");//打印收到一条people_tracker_measurements消息
	vector<people_msgs::PositionMeasurement> people_array;
	people_array = message->people;//people_array用于存放行人目标阵列

	  vector<people_msgs::PositionMeasurement>:: iterator iter;

	/*get the best people from the people_array*/
	sort(people_array.begin(),people_array.end(),compare);//根据reliability，对people_array进行排序，按从大到小的顺序排序


	  for(iter=people_array.begin();iter!=people_array.end();++iter)
 	 {
		ROS_WARN("people_array1.pos.x= %f",(*iter).pos.x);
		ROS_WARN("people_array1.pos.y= %f",(*iter).pos.y);
		ROS_WARN("people_array1.pos.z= %f",(*iter).pos.z);
		ROS_WARN("people_array1.reliability= %f",(*iter).reliability);
 	 }
	vector<people_msgs::PositionMeasurement> :: iterator iter1 = people_array.begin();
	best_people = *iter1;//获得people_array的第一个元素，即reliability最大的行人目标，将其视为跟踪目标

	people_follow();//调用行人自动跟随函数
}
/********************************************/
//获取里程计函数，用于获取机器人的实时位置，存放与transform中
tf::StampedTransform get_base2map()
{
	tf::TransformListener listener;
	tf::StampedTransform transform;
	listener.waitForTransform("/map", "/base_link",  ros::Time(0), ros :: Duration(3.0));
	try
	{
		listener.lookupTransform("/map", "/base_link",  ros::Time(0), transform );//获取base_link到odom的坐标系变换
	}
	catch (tf::TransformException ex)
	{
		ROS_ERROR("%s",ex.what());
		ros::Duration(1.0).sleep();
	}
	
	return transform;
}

