#include "ros/ros.h"
#include "geometry_msgs/Twist.h"
#include "joystick/js_axes.h"

#define JOYSTICK_INTERFACE_NODE "joystick_interface"
#define JOYSTICK_CMD_TOPIC "joystick"
#define CMD_VEL "joystick_cmd_vel"

ros::Subscriber sub;
ros::Publisher pub;

void translate(const joystick::js_axes& msg){
	geometry_msgs::Twist m;
	m.linear.x = -0.5*msg.y;
	//m.linear.y = msg.x;
	//m.angular.z = -1.0*msg.x;
	float x_temp = msg.x;
	float z_temp = msg.z;
	float sum = x_temp+z_temp;
	x_temp /= sum;
	z_temp /= sum;
	//m.angular.z = -0.1*z_temp - 0.9*x_temp;
	m.angular.z = -0.5*msg.x;
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
