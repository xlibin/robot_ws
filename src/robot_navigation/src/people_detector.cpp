
#include <ros/ros.h>
#include <move_base_msgs/MoveBaseAction.h>
#include <actionlib/client/simple_action_client.h>

#include <leg_detector/LegDetectorConfig.h>
//#include <leg_detector/laser_processor.h>
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

typedef actionlib :: SimpleActionClient<move_base_msgs :: MoveBaseAction> MoveBaseClient;
//typedef actionlib :: SimpleActionClient<move_base_msgs::MoveBaseAction> MoveBaseClient;
int main(int argc , char ** argv)
{
	ros :: init (argc , argv , "people_detector");

	ros::NodeHandle n;	/**/

	//tell the action client that we want to spin a thread by default
	MoveBaseClient ac("move_base" , true);

	//wait for the action server to come up 
	while(! ac.waitForServer(ros :: Duration(5.0)))
	{
		ROS_INFO("Waiting for the move_base action server to come up");
	}

	move_base_msgs :: MoveBaseGoal goal;


	/**********************************/
	ros::Subscriber sub = n.subscribe("leg_tracker_measurements", 0,leg_detector_callback");
	/**********************************/

	return 0;
}

void leg_detector_callback(const people_msgs::PositionMeasurement::ConstPtr& message)
{
	goal.target_pose.header.frame_id = "base_link";
	goal.target_pose.header.stamp = ros :: Time :: now();
	goal.target_pose.pose.position = message.pos;
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
