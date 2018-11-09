//#define SHOW_TRAJECTORY 1
#define SAVE_SPEED_AND_DISTANCE 1
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

#ifdef SHOW_TRAJECTORY
	#include <visualization_msgs/Marker.h>
#endif

#ifdef SAVE_SPEED_AND_DISTANCE
    #include <fstream>
    #include <nav_msgs/Odometry.h>
#endif

using geometry_msgs :: Quaternion;
using geometry_msgs :: Pose;

void people_follow();
bool compare(const people_msgs::PositionMeasurement& x, const people_msgs::PositionMeasurement& y);
void people_follow_callback(const people_msgs::PositionMeasurementArray::ConstPtr& message);
tf::StampedTransform get_base2map();

typedef actionlib :: SimpleActionClient<move_base_msgs :: MoveBaseAction> MoveBaseClient;
people_msgs::PositionMeasurement best_people;

#ifdef SHOW_TRAJECTORY
	ros::Publisher marker_pub;
#endif

#ifdef SAVE_SPEED_AND_DISTANCE
    ofstream g_log_file;
    ros::Subscriber sub_odom;
    void SubOdomCallback(const nav_msgs::Odometry::ConstPtr& msg);
    double g_robot_speed;
#endif

int main(int argc , char ** argv)
{
	ros :: init (argc , argv , "people_follow");
	ros::NodeHandle n;	/**/
#ifdef SHOW_TRAJECTORY
	marker_pub = n.advertise<visualization_msgs::Marker>("visualization_marker", 1);
#endif
#ifdef SAVE_SPEED_AND_DISTANCE
    g_log_file.open("~/Documents/robot_speed_and_dist.txt", ios::out);
    sub_odom = n.subscribe("odom", 50, SubOdomCallback);
#endif
//订阅行人检测topic，每受到一个people_tracker_measurements消息，调用people_follow_callback函数
	ros :: Subscriber sub_people = n.subscribe("people_tracker_measurements", 1,  people_follow_callback);
	//people_follow();
	ros::spin();

#ifdef SAVE_SPEED_AND_DISTANCE
    g_log_file.close();
#endif
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
// #ifdef SHOW_TRAJECTORY//show robot's trajectory
// 	static int marker_id = 0;
// 	//robot
	
    
// #endif
	//caculate distance of robot to people计算机器人与行人目标的距离
	float delta_x = best_people.pos.x - transform.getOrigin().x();
	float delta_y = best_people.pos.y - transform.getOrigin().y();
	double dist_robot_people = sqrt(delta_x * delta_x  + delta_y * delta_y);
	double speed_val = 0.2;
#ifdef SAVE_SPEED_AND_DISTANCE
    g_log_file  << dist_robot_people << " " << g_robot_speed << endl;
#endif
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
	double dist_robot_goal = dist_robot_people- 0.4;//0.2m的安全距离，导航目标与行人距离0.2m
	if(dist_robot_people <= 0.5)
	{
		double yaw, pitch, roll;
		ROS_INFO("The goal is too close to robot!");//获得无效的行人目标
		// goal.target_pose.pose.position.x = transform.getOrigin().x();
		// goal.target_pose.pose.position.y = transform.getOrigin().y();
		// transform.getBasis().getEulerYPR(yaw, pitch, roll);
		// goal.target_pose.pose.orientation.w = yaw;
		// //wait for the action server to come up 
		// while(! ac.waitForServer(ros :: Duration(5.0)))
		// {
		// 	ROS_INFO("Waiting for the move_base action server to come up");
		// }
		// ac.sendGoal(goal);//sending goal
		// ac.cancelGoal();
	}else{
		ROS_INFO("Recesive a valuable goal !");//获得有效的行目标
		ROS_WARN("I will go to the goal!");
//设置goal的坐标，x=(L-0.2)*dx/L，y=（L-0.2）*dy/L
		double yaw, pitch, roll;
		transform.getBasis().getEulerYPR(yaw, pitch, roll);
		goal.target_pose.pose.position.x = transform.getOrigin().x()+ dist_robot_goal*(delta_x/dist_robot_people);
		goal.target_pose.pose.position.y = transform.getOrigin().y() + dist_robot_goal*(delta_y/dist_robot_people);
		goal.target_pose.pose.orientation.z = sin(atan2(delta_y, delta_x) / 2);
		goal.target_pose.pose.orientation.w = cos(atan2(delta_y, delta_x) / 2);
		
		ROS_WARN("robot's yaw: %f, goal's yaw: %f", yaw, atan2(delta_y, delta_x));
		//wait for the action server to come up 等待move_base启动

		while(! ac.waitForServer(ros :: Duration(5.0)))
		{
			ROS_WARN("Waiting for the move_base action server to come up");
		}
		ac.sendGoal(goal);//sending goal发送导航目标
//allow 2 second to get there，允许2s到达目标，否则取消goal，从新产生goal
		bool finished_within_time = ac.waitForResult(ros :: Duration(10.0));
		if(!finished_within_time)
		{
			ac.cancelGoal();
			ROS_WARN("Timed out achieving goal ");//未能在2s内到达目标
		}
		else if(ac.getState() == actionlib :: SimpleClientGoalState :: SUCCEEDED)
		{
			ROS_WARN("I have go there");//成功到达目标
		}
		else
		{
			ROS_WARN("The base failed to go to people for some reason");
		}
	}
	  	
	//ros::spin();
}

/*compare function . return the highest reliability of people_array*/
//people_array排序函数，根据reliability属性从大到小排序
bool compare(const people_msgs::PositionMeasurement& a, const people_msgs::PositionMeasurement& b)
{
	//return x.reliability > y.reliability;
	double yaw, pitch, roll;
	tf::StampedTransform transform;
	transform = get_base2map();//获取机器人位置
	transform.getBasis().getEulerYPR(yaw, pitch, roll);

	float a_delta_x = a.pos.x - transform.getOrigin().x();
	float a_delta_y = a.pos.y - transform.getOrigin().y();
	double a_dist_robot_people = sqrt(a_delta_x * a_delta_x  + a_delta_y * a_delta_y);
	float a_w = atan2(a_delta_y, a_delta_x);

	float b_delta_x = b.pos.x - transform.getOrigin().x();
	float b_delta_y = b.pos.y - transform.getOrigin().y();
	double b_dist_robot_people = sqrt(b_delta_x * b_delta_x  + b_delta_y * b_delta_y);
	float b_w = atan2(b_delta_y, b_delta_x);
	//printf("robot's yaw: %f, a's yaw: %f, b's yaw: %f", yaw, a_w, b_w);
	if(fabs(a_w - yaw) < 0.5 && fabs(b_w - yaw) < 0.5)
		return a_dist_robot_people < b_dist_robot_people;
	else if(fabs(a_w - yaw) < 0.5)
		return true;
	else if(fabs(b_w - yaw) < 0.5)
		return false;
	else
		return a_dist_robot_people < b_dist_robot_people;
}


void people_follow_callback(const people_msgs::PositionMeasurementArray::ConstPtr& message)//people_tracker_measurements回调函数
{	
	//while(ros::ok()){	
		ROS_INFO("I have received a people message");//打印收到一条people_tracker_measurements消息
		vector<people_msgs::PositionMeasurement> people_array;
		people_array = message->people;//people_array用于存放行人目标阵列

		vector<people_msgs::PositionMeasurement>:: iterator iter;

		if(people_array.empty()){
			return;
		}

		/*get the best people from the people_array*/
		sort(people_array.begin(),people_array.end(),compare);//根据reliability，对people_array进行排序，按从大到小的顺序排序


		for(iter=people_array.begin();iter!=people_array.end();++iter)
	 	{
	 		ROS_INFO("people name = %s",(*iter).name.c_str());
	 		ROS_INFO("people id = %s",(*iter).object_id.c_str());
			ROS_INFO("(%f, %f, %f)",(*iter).pos.x, (*iter).pos.y, (*iter).pos.z);
			ROS_INFO("people_array1.reliability= %f",(*iter).reliability);
	 	}
#ifdef SHOW_TRAJECTORY//show robot's trajectory
	 	static int marker_id = 0;
	 	marker_id++;
	 	//robot
	 	tf::StampedTransform transform;
		transform = get_base2map();//获取机器人位置
	 	visualization_msgs::Marker marker_robot;
		marker_robot.header.frame_id = "/map";
		marker_robot.header.stamp = ros::Time::now();
		marker_robot.ns = "robot";
		marker_robot.id = marker_id;
		marker_robot.type = visualization_msgs::Marker::SPHERE;
		marker_robot.action = visualization_msgs::Marker::ADD;
		marker_robot.pose.position.x = transform.getOrigin().x();
	    marker_robot.pose.position.y = transform.getOrigin().y();
	    marker_robot.pose.position.z = 0;
	    marker_robot.pose.orientation.x = 0.0;
	    marker_robot.pose.orientation.y = 0.0;
	    marker_robot.pose.orientation.z = 0.0;
	    marker_robot.pose.orientation.w = 1.0;
	    marker_robot.scale.x = 0.1;
	    marker_robot.scale.y = 0.1;
	    marker_robot.scale.z = 0.1;
	    marker_robot.color.r = 0.0f;
	    marker_robot.color.g = 0.0f;
	    marker_robot.color.b = 0.0f;
	    marker_robot.color.a = 0.5;
	    marker_robot.lifetime = ros::Duration();
	    marker_pub.publish(marker_robot);
	 	iter=people_array.begin();
	 	//best people
	    visualization_msgs::Marker marker_best;
		marker_best.header.frame_id = "/map";
		marker_best.header.stamp = ros::Time::now();
		marker_best.ns = "best";
		marker_best.id = marker_id;
		marker_best.type = visualization_msgs::Marker::CUBE;
		marker_best.action = visualization_msgs::Marker::ADD;
		marker_best.pose.position.x = (*iter).pos.x;
	    marker_best.pose.position.y = (*iter).pos.y;
	    marker_best.pose.position.z = 0;
	    marker_best.pose.orientation.x = 0.0;
	    marker_best.pose.orientation.y = 0.0;
	    marker_best.pose.orientation.z = 0.0;
	    marker_best.pose.orientation.w = 1.0;
	    marker_best.scale.x = 0.1;
	    marker_best.scale.y = 0.1;
	    marker_best.scale.z = 0.1;
	    marker_best.color.r = 1.0f;
	    marker_best.color.g = 1.0f;
	    marker_best.color.b = 1.0f;
	    marker_best.color.a = 0.5;
	    marker_best.lifetime = ros::Duration();
	    marker_pub.publish(marker_best);
	    //people
	 	iter++;
	 	for(;iter!=people_array.end();++iter){
			visualization_msgs::Marker marker_people;
			marker_people.header.frame_id = "/map";
			marker_people.header.stamp = ros::Time::now();
			marker_people.ns = (*iter).name;
			marker_people.id = marker_id;
			marker_people.type = visualization_msgs::Marker::CUBE;
			marker_people.action = visualization_msgs::Marker::ADD;
			marker_people.pose.position.x = (*iter).pos.x;
		    marker_people.pose.position.y = (*iter).pos.y;
		    marker_people.pose.position.z = 0;
		    marker_people.pose.orientation.x = 0.0;
		    marker_people.pose.orientation.y = 0.0;
		    marker_people.pose.orientation.z = 0.0;
		    marker_people.pose.orientation.w = 1.0;
		    marker_people.scale.x = 0.05;
		    marker_people.scale.y = 0.1;
		    marker_people.scale.z = 0.1;
		    marker_people.color.r = 1.0f;
		    marker_people.color.g = 1.0f;
		    marker_people.color.b = 1.0f;
		    marker_people.color.a = 0.5;
		    //marker_people.text = "X";
		    marker_people.lifetime = ros::Duration();
		    marker_pub.publish(marker_people);
	 	}
#endif
		vector<people_msgs::PositionMeasurement> :: iterator iter1 = people_array.begin();
		best_people = *iter1;//获得people_array的第一个元素，即reliability最大的行人目标，将其视为跟踪目标

		people_follow();//调用行人自动跟随函数
	//}
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


#ifdef SAVE_SPEED_AND_DISTANCE
void SubOdomCallback(const nav_msgs::Odometry::ConstPtr& msg)
{
    g_robot_speed = msg->twist.twist.linear.x;
}
#endif

