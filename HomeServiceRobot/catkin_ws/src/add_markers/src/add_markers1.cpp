#include <ros/ros.h>
#include <visualization_msgs/Marker.h>


int main(int argc, char** argv){
  // Initialize the pick objects node
  ros::init(argc, argv, "add_markers");
  
  //Create node handle
  ros::NodeHandle n;
  //Create a publisher to publish message of type <visualization_msgs::Marker>
  ros::Publisher marker_pub = n.advertise<visualization_msgs::Marker>("visualization_marker", 1);
  

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
  marker.type = shape;
  marker.action = visualization_msgs::Marker::ADD;

  // Set the pose of the marker.  This is a full 6DOF pose relative to the frame/time specified in the header
  marker.pose.position.x = 0.0;
  marker.pose.position.y = 2.0;
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
 
  marker.lifetime = ros::Duration();
  
  ROS_INFO("Waiting for Rviz to load");
  ros::Duration(8.0).sleep();

  //PLACING MARKER IN PICK UP LOCATION FOR 5s
  marker_pub.publish(marker);
  ROS_INFO("Object in Pick Up Location");
  ros::Duration(5.0).sleep();
 
  //DELETING MARKER FOR 5s
  marker.action = visualization_msgs::Marker::DELETE;
  marker_pub.publish(marker);
  ROS_INFO("Object taken from Pick Up Point");
  ros::Duration(5.0).sleep();
  
  //PLACING MARKER AT DROP OFF LOCATION
  marker.pose.position.x = -3.0;
  marker.pose.position.y = 1.0;
  marker.action = visualization_msgs::Marker::ADD;  
  marker_pub.publish(marker);
  ROS_INFO("Object in Drop Off Point");
  ros::Duration(10.0).sleep();// waiting for screen to be displayed for sufficient time
 
  
}
