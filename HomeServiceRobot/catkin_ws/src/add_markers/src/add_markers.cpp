#include <ros/ros.h>
#include <visualization_msgs/Marker.h>
#include "nav_msgs/Odometry.h"

// This node assumes pick-up position of (0,2) and drop-off position of (-3,0)
double pick_x=0.0;
double pick_y=2.0;
double drop_x=-3.0;
double drop_y=0.0;

// declare pos_x, pos_y to obtain current pose of robot
double pos_x=0;
double pos_y=0;

void get_pos(const nav_msgs::Odometry::ConstPtr& msg)
{
pos_x=msg->pose.pose.position.x;
pos_y=msg->pose.pose.position.y;

}

double get_dist(double x, double y)
{
double dx = x-pos_x;
double dy = y-pos_y;
double dist = sqrt(dx*dx + dy*dy);
return dist;
}

int main(int argc, char** argv){
  // Initialize the pick objects node
  ros::init(argc, argv, "add_markers");
  
  //Create node handle
  ros::NodeHandle n;
  //Create a publisher to publish message of type <visualization_msgs::Marker>
  ros::Publisher marker_pub = n.advertise<visualization_msgs::Marker>("visualization_marker", 1);
  
  //Create a subscriber to subscribe to robot position
  ros::Subscriber pos_sub = n.subscribe("odom",10,get_pos);
  

  // Set the initial shape type to be a cube
  uint32_t shape = visualization_msgs::Marker::CUBE;

  visualization_msgs::Marker marker;

  // set up the frame parameters
  marker.header.frame_id = "map";
  marker.header.stamp = ros::Time::now();

  // Set the namespace and id for this marker.  This serves to create a unique ID
  // Any marker sent with the same namespace and id will overwrite the old one
  marker.ns = "add_markers";
  marker.id = 0;

  // Set marker shape and action
  marker.lifetime = ros::Duration();
  marker.type = shape;

  // Set the pose of the marker.  This is a full 6DOF pose relative to the frame/time specified in the header
  marker.pose.position.x = pick_x;
  marker.pose.position.y = pick_y;
  marker.pose.position.z = 0.15;
  marker.pose.orientation.x = 0.0;
  marker.pose.orientation.y = 0.0;
  marker.pose.orientation.z = 0.0;
  marker.pose.orientation.w = 1.0;
 
  // Set the scale of the marker -- 1x1x1 here means 1m on a side
  marker.scale.x = 0.3;
  marker.scale.y = 0.3;
  marker.scale.z = 0.3;
 
  // Set the color -- be sure to set alpha to something non-zero!
  marker.color.r = 0.0f;
  marker.color.g = 1.0f;
  marker.color.b = 0.0f;
  marker.color.a = 1.0;
  marker.action = visualization_msgs::Marker::ADD; 
  ros::Duration(1).sleep();
  // publish the markers
  marker_pub.publish(marker);
  ROS_INFO("Object in Pick Up Location");

  bool flag_P = true;
  bool flag_D =true;
  
 while (ros::ok())
 {
  
   ros::spinOnce();// To run subscriber callback function
   marker_pub.publish(marker);
   //ROS_INFO("Robot at x:%f ,y:%f",pos_x,pos_y);//to print current turtlebot x and y coordinates
   if(flag_P&&(get_dist(pick_x,pick_y)<0.5))
   {
   ROS_INFO("Robot at Pick Up Location");
   marker.action = visualization_msgs::Marker::DELETE;
   marker_pub.publish(marker);
   ROS_INFO("Object taken from Pick Up Point");
   flag_P=false;
   }
   if(flag_D&&(get_dist(drop_x,drop_y)<0.5))
   {
   ROS_INFO("Robot at Drop Location");
   marker.pose.position.x = drop_x;
   marker.pose.position.y = drop_y;
   marker.action = visualization_msgs::Marker::ADD;
   marker_pub.publish(marker);
   ROS_INFO("Object placed at Drop Point");
   flag_D=false;
   }
 }

   
}
