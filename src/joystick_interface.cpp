#include "ros/ros.h"
#include "geometry_msgs/Twist.h"
#include "joystick/js_axes.h"

#define JOYSTICK_INTERFACE_NODE "joystick_interface"
#define JOYSTICK_CMD_TOPIC "joystick_axes"
#define CMD_VEL "cmd_vel"

ros::Subscriber sub;
ros::Publisher pub;

void translate(const joystick::js_axes msg){
	geometry_msgs::Twist m;
	m.linear.x = msg.y;
	//m.linear.y = msg.x;
	m.angular.z = -1.0*msg.x;
	pub.publish(m);
}

int main(int argc, char * argv[]){
	ros::init(argc, argv, JOYSTICK_INTERFACE_NODE);

	ros::NodeHandle n;
	
	sub = n.subscribe(JOYSTICK_CMD_TOPIC, 1000, translate);

	pub = n.advertise<geometry_msgs::Twist>(CMD_VEL, 1000);

	ros::spin();

	return 0;
}
