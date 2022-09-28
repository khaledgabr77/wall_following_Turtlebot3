#include "geometry_msgs/Twist.h"
#include "ros/forwards.h"
#include "ros/init.h"
#include "ros/node_handle.h"
#include "ros/publisher.h"
#include "ros/rate.h"
#include "ros/ros.h"
#include "ros/subscriber.h"
#include "sensor_msgs/LaserScan.h"

class Wall_Follwing {

private:
  ros::NodeHandle nhmove;
  ros::Publisher pub;

public:
  Wall_Follwing() {
    pub = nhmove.advertise<geometry_msgs::Twist>("/cmd_vel", 1000);
  }

  void laser_callback(const sensor_msgs::LaserScanConstPtr &msg) {
    ROS_INFO("%f", msg->ranges[0]);
    ROS_INFO("%f", msg->ranges[360]);

    ros::Rate rate(1);
    geometry_msgs::Twist vel;
    // TODO
    // If the ray distance is bigger than 0.3m, you need to make the robot
    // approach the wall a little, by adding some rotational speed to the robot.
    if (msg->ranges[0] > 0.3) {
      vel.linear.x = 0.05;
      vel.angular.z = -0.05;
      pub.publish(vel);
    }

    // TODO
    // If the ray distance is smaller than 0.2m, you need to move the robot away
    // from the wall, by adding rotational speed in the opposite direction.
    if (msg->ranges[0] < 0.2) {
      vel.linear.x = 0.05;
      vel.angular.z = 0.05;
      pub.publish(vel);
    }

    // TODO
    // If the ray distance is between 0.2m and 0.3m, just keep the robot moving
    // forward
    if (msg->ranges[0] < 0.3 && msg->ranges[0] > 0.2) {
      vel.linear.x = 0.05;
      vel.angular.z = 0.0;
      pub.publish(vel);
    }

    // TODO
    // If the distance measured by that ray is shorter than 0.5m,
    // then make the robot turn fast to the left (moving forward at the same
    // time).
    if (msg->ranges[360] < 0.5) {
      vel.linear.x = 0.1;
      vel.angular.z = 0.5;
      pub.publish(vel);
    }

    if (msg->ranges[0] > 1.0) {
      vel.linear.x = 0.05;
      vel.angular.z = 0.05;
      pub.publish(vel);
    }
    rate.sleep();
  }
};

int main(int argc, char **argv) {

  ros::init(argc, argv, "wall_following_node");
  ros::NodeHandle nh;

  ros::Subscriber sub;
  Wall_Follwing wall_follwing;
  sub =
      nh.subscribe("/scan", 1, &Wall_Follwing::laser_callback, &wall_follwing);

  ros::spin();

  return 0;
}