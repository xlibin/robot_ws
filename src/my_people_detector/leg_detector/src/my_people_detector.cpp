
#include <ros/ros.h>
#include <move_base_msgs/MoveBaseAction.h>
#include <actionlib/client/simple_action_client.h>

#include <leg_detector/LegDetectorConfig.h>
#include <leg_detector/laser_processor.h>
#include <leg_detector/calc_leg_features.h>

#include <opencv/cxcore.h>
#include <opencv/cv.h>
#include <opencv/ml.h>

#include <people_msgs/PositionMeasurement.h>
#include <people_msgs/PositionMeasurementArray.h>
#include <sensor_msgs/LaserScan.h>

#include <tf/transform_listener.h>
#include <tf/message_filter.h>
#include <message_filters/subscriber.h>

#include <people_tracking_filter/tracker_kalman.h>
#include <people_tracking_filter/state_pos_vel.h>
#include <people_tracking_filter/rgb.h>
#include <visualization_msgs/Marker.h>
#include <dynamic_reconfigure/server.h>

#include <algorithm>

#include <vector>
using std :: vector;

#include <geometry_msgs/Pose.h>
#include <geometry_msgs/Quaternion.h>
using geometry_msgs :: Quaternion;
using geometry_msgs :: Pose;

typedef actionlib :: SimpleActionClient<move_base_msgs :: MoveBaseAction> MoveBaseClient;

vector<people_msgs::PositionMeasurement> best_people_array;

void leg_detector_callback(const people_msgs::PositionMeasurementArray::ConstPtr& message)
{
	
/*******************************************/
	vector<people_msgs::PositionMeasurement> leg_array;
	//vector<people_msgs::PositionMeasurement>::iterator iter = best_legs.begin();
	leg_array = message->people;

/*	for (vector<people_msgs::PositionMeasurement*>::iterator iter = message->people.begin();
		iter != message->people.end(); 
		iter++)
	{
		;
	}*/

/*******************************************/

	//tell the action client that we want to spin a thread by default
	MoveBaseClient ac("move_base" , true);
	ROS_INFO("*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/");

	//wait for the action server to come up 
	while(! ac.waitForServer(ros :: Duration(5.0)))
	{
		ROS_INFO("Waiting for the move_base action server to come up");
	}

	move_base_msgs :: MoveBaseGoal goal;

	goal.target_pose.header.frame_id = "base_link";
	goal.target_pose.header.stamp = ros :: Time :: now();
	goal.target_pose.pose.position.x = message->people[0].pos.x - 0.5;//可以使用people.size()获得people的元素个数
	goal.target_pose.pose.position.y = message->people[0].pos.y - 0.5;
	goal.target_pose.pose.orientation.w = 1.0;
	ROS_INFO("Sending goal");
	ac.sendGoal(goal);

	ac.waitForResult();

	if(ac.getState() == actionlib :: SimpleClientGoalState :: SUCCEEDED)
		{
		ROS_INFO("I have find a people_leg");
		}
	else
		ROS_INFO("The base failed to find people_leg for some reason");
}

bool compare(const people_msgs::PositionMeasurement& x, const people_msgs::PositionMeasurement& y)
{
	return x.reliability > y.reliability;
}

tf::StampedTransform get_odom()
{
	tf::TransformListener listener;
	tf::StampedTransform transform;
	listener.waitForTransform("/odom", "/base_link",  ros::Time(0), ros :: Duration(3.0));
	try
	{
		listener.lookupTransform("/odom", "/base_link",  ros::Time(0), transform );
	}
	catch (tf::TransformException ex)
	{
		ROS_ERROR("%s",ex.what());
		ros::Duration(1.0).sleep();
	}
	
	return transform;
}

void people_detector_callback(const people_msgs::PositionMeasurementArray::ConstPtr& message)
{
	ROS_INFO("I have received a people message");

	vector<people_msgs::PositionMeasurement> people_array;
	people_array = message->people;

	/*get the best people from the people_array*/
	sort(people_array.begin(),people_array.end(),compare);
	vector<people_msgs::PositionMeasurement> :: iterator iter = people_array.begin();
	people_msgs::PositionMeasurement best_people;
	best_people = *iter;
	best_people_array.push_back(best_people);//push best_people to best_people_array
/*********************************************************************************/
	//get odom
	tf::StampedTransform transform;
	transform = get_odom();
	float delta_x = best_people.pos.x - transform.getOrigin().x();
	float delta_y = best_people.pos.y - transform.getOrigin().y();
	double L = sqrt(delta_x * delta_x  + delta_y * delta_y);


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
	goal.target_pose.header.frame_id = "base_link";//base_link or map
	goal.target_pose.header.stamp = ros :: Time :: now();
	goal.target_pose.pose.orientation.w = 1.0;

	//goal.target_pose.pose.position =  best_people.pos;//set  goal.position
	float save_dist = 0.3;
	goal.target_pose.pose.position.x = best_people.pos.x - (L - save_dist)*(delta_x/L);
	goal.target_pose.pose.position.y = best_people.pos.y - (L - save_dist)*(delta_y/L);
	
	
	ROS_INFO("I have a found a people and I will go to there");
	//wait for the action server to come up 
	while(! ac.waitForServer(ros :: Duration(5.0)))
	{
		ROS_INFO("Waiting for the move_base action server to come up");
	}
	ac.sendGoal(goal);//sending goal;
	bool finished_within_time = ac.waitForResult(ros :: Duration(2.0));//allow 5 second to get there
	if(!finished_within_time)
	{
		ac.cancelGoal();
		ROS_INFO("Timed out achieving goal ");
	}
	else if(ac.getState() == actionlib :: SimpleClientGoalState :: SUCCEEDED)
		{
		ROS_INFO("I have go there");
		}
	  	else
	  		ROS_INFO("The base failed to go to people for some reason");	
/**********************************/

}


int main(int argc , char ** argv)
{
	ros :: init (argc , argv , "my_people_detector");

	ros::NodeHandle n;	/**/

		/**********************************/
	ROS_INFO("//////////////////////");
	ros::Subscriber sub_leg = n.subscribe( "leg_tracker_measurements" , 0, leg_detector_callback );
	ros :: Subscriber sub_people = n.subscribe("people_tracker_measurements", 1,  people_detector_callback);
	ROS_INFO("**********************");
	/**********************************/

	
	ros::spin();
	return 0;
}


