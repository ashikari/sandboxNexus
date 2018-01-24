#!/usr/bin/python

import rospy
from std_msgs.msg import Float32MultiArray
from sensor_msgs.msg import Joy

#create publisher
vel_pub = rospy.Publisher('vel_cmd', Float32MultiArray, queue_size = 1)

def joy_cb(msg):
	vCmd = Float32MultiArray(data = [ msg.axes[0], msg.axes[1], msg.axes[2], msg.axes[3] ]) 
	vel_pub.publish( vCmd )

def vel_command():
	print 'Velocity Command Initialized...'
	rospy.init_node('joy_vel', anonymous=True)
	rospy.Subscriber("/joy", Joy,  joy_cb)
	rospy.spin()

if __name__ == '__main__':
	vel_command()

