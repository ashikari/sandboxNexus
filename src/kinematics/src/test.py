#!/usr/bin/python


import rospy
from std_msgs.msg import Float32MultiArray

test_pub = rospy.Publisher('/vel_cmd',Float32MultiArray,queue_size = 1)


def test():

	print 'testing...'

	for i in range(0,10):
		rospy.init_node('test',anonymous = True)
		t1 = Float32MultiArray(data = [0, 1, 0 , 1])
		test_pub.publish(t1)
		rospy.sleep(0.5)
	# t1 = Float32MultiArray(data = [0, 0, 1 , 1])
	# test_pub.publish(t1)
	# rospy.sleep(0.5)
	# t1 = Float32MultiArray(data = [1, 0, 0 , 1])
	# test_pub.publish(t1)
	# rospy.sleep(0.5)


if __name__ == "__main__":
	test()