//#include <ros/ros.h>
#include <move_base_msgs/MoveBaseAction.h>
#include <actionlib/client/simple_action_client.h>

#include "ros/ros.h"
#include "std_msgs/String.h"
#include "awaken_asr/sr_order.h"
#include "../include/asr_record/play_audio.h"
#include "../include/asr_record/asr_record.h"
typedef actionlib::SimpleActionClient<move_base_msgs::MoveBaseAction>  MoveBaseClient;

void chatterCallback(const awaken_asr::sr_order order)
{
  ROS_INFO("I heard: [%04x]\n", order.order);
  if(order.order == ORDER_BACK_TO_CHARGE){
  	
  	play_wav((char*)concat(PACKAGE_PATH, "audios/back_to_charge.wav"));

  	move_base_msgs :: MoveBaseGoal goal;
  	goal.target_pose.header.frame_id = "map";//base_link or map
	  goal.target_pose.header.stamp = ros::Time::now();
	  goal.target_pose.pose.position.x = 0;
		goal.target_pose.pose.position.y = 0;
		//goal.target_pose.pose.position.z = 0;
		goal.target_pose.pose.orientation.w = 1.0;
		//tell the action client that we want to spin a thread by default
		MoveBaseClient bc("move_base", true);
		//wait for the action server to come up 
		while(! bc.waitForServer(ros :: Duration(5.0)))
		{
			ROS_INFO("Waiting for the move_base action server to come up");
		}
		bc.sendGoal(goal);//sending goal

		
	  //allow 4 second to get there，允许2s到达目标，否则取消goal，从新产生goal
		bool finished_within_time = bc.waitForResult(ros :: Duration(10.0));
		if(!finished_within_time)
		{
			bc.cancelGoal();
			ROS_INFO("Timed out achieving goal ");//未能在2s内到达目标
		}
		else if(bc.getState() == actionlib :: SimpleClientGoalState :: SUCCEEDED)
		{
			ROS_INFO("I have go there");//成功到达目标
		}
		else
		{
			ROS_INFO("The base failed to get there for some reason");
		}
  }
}

int main(int argc, char **argv)
{
  ros::init(argc, argv, "order_listener");
  ros::NodeHandle nh;

  ros::Subscriber sub = nh.subscribe("sr_order", 1000, chatterCallback);

  
	ros::spin();

  return 0;
}
