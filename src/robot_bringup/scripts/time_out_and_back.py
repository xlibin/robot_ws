#!/usr/bin/env python

import rospy
from geometry_msgs.msg import Twist
from math import pi

class OutAndBack():
	def __init__(self):

		#give the node a name
		rospy.init_node('out_and_back', anonymous = False)

		#set rospy to execute a shutdown function when exiting
		rospy.on_shutdown(self.shutdown)

		#publisher to control the robot's speed
		self.cmd_vel = rospy.Publisher('/cmd_vel', Twist)

		#how fast will wu update the robot's movement?
		rate = 50

		#set the equevalent ros rate variable
		r = rospy.Rate(rate)

		#set the forward linear speed to 0.2, meters per second
		linear_speed = 0.2

		#set the travel distance to 1.0 meters
		goal_distance = 1.0

		#how long should it take us to get there?
		linear_duration = goal_distance / linear_speed

		#set the rotation speed to 1.0 radians per second
		angular_speed = 1.0

		#set the rotation angle to pi radians (180 degrees)
		goal_angle = pi

		#how long should it take to rotate?
		angular_duration = goal_angle / angular_speed

		#loop through the two legs of the trip
		for i in range(2):
			#initial the movement command
			move_cmd = Twist()

			#set the forward speed
			move_cmd.linear.x = linear_speed

			#move forward for a time to go 1 meter
			ticks = int(linear_duration * rate)
			for t in range(ticks):
				self.cmd_vel.publish(move_cmd)
				r.sleep()

			#stop the robot before the rotation
			move_cmd = Twist()
			self.cmd_vel.publish(move_cmd)
			rospy.sleep(1)

			#now rotate lelf roughly 180 degrees
			#set the angular speed
			move_cmd.angular.z = angular_speed

			#rotate for a tiime to go 180 degrees
			ticks = int(goal_angle * rate)

			for t in range(ticks):
				self.cmd_vel.publish(move_cmd)
				r.sleep()

			#stop the robot before the next leg
			move_cmd = Twist()
			self.cmd_vel.publish(move_cmd)
			rospy.sleep(1)

		#stop the robot
		self.cmd_vel.publish(Twist())

	def shutdown(self):
		#always stop the robot when shutting down the node.
		rospy.loginfo("stopping the robot . . .")
		self.cmd_vel.publish(Twist())
		rospy.sleep(1)

if __name__ == '__main__':
	try:
		OutAndBack()
	except:
		rospy.loginfo("Out-and-Back node terminated.")

