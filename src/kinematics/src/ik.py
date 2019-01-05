#!/usr/bin/python

import rospy
from std_msgs.msg import Float32MultiArray
import numpy as np
import numpy.linalg as la # not sure if necessary

motor_cmd_pub = rospy.Publisher('motor_cmd',Float32MultiArray,queue_size = 1)

def ik_cb(msg):
	#convert global position velocities to velocity controller setpoints for each motor
	vel_max = 1  #m/s
	vel_gain = vel_max*(msg.data[3]+1)/2
	rot_gain = 1
	#x_dot, y_dot, theta_dot
	v = np.matrix([ -vel_gain * msg.data[0], vel_gain * msg.data[1], rot_gain* msg.data[2] ]) 

	#geometric properties
	L = 1.0 #characteristic length
	r = 1.0 #wheel radius

	#CHANGE THIS this value must come from the position estimation
	theta = 0

	#determined by the orientation we want to consider for our local coordinate system
	th1 = 30.0/180*np.pi
	th2 = th1 + 120.0/180*np.pi
	th3 = th2 + 120.0/180*np.pi

	#inverse jacobian (global coord to motor vel)
	Jinv = -1/r*np.matrix( [[-np.sin(theta+th1), np.cos(theta+th1), L],
						[-np.sin(theta+th2), np.cos(theta+th2), L],
						[-np.sin(theta+th3), np.cos(theta+th3), L]] )

	u = Jinv * np.transpose(v)

	mCmd = Float32MultiArray( data = [ u[0], u[1], u[2]] ) 
	motor_cmd_pub.publish(mCmd)

def ik():
	print "Evaluating mVel Setpoints..."

	rospy.init_node('ik', anonymous=True)
	rospy.Subscriber("/vel_cmd",Float32MultiArray, ik_cb)
	rospy.spin()

if __name__=='__main__':
	ik()
