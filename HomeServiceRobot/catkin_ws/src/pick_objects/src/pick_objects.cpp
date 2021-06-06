#include <ros/ros.h>
#include <move_base_msgs/MoveBaseAction.h>
#include <actionlib/client/simple_action_client.h>

// Define a client for to send goal requests to the move_base server through a SimpleActionClient
typedef actionlib::SimpleActionClient<move_base_msgs::MoveBaseAction> MoveBaseClient;

int main(int argc, char** argv){
  // Initialize the pick objects node
  ros::init(argc, argv, "pick_objects");

  //tell the action client that we want to spin a thread by default
  MoveBaseClient ac("move_base", true);

  // Wait 5 sec for move_base action server to come up
  while(!ac.waitForServer(ros::Duration(5.0))){
    ROS_INFO("Waiting for the move_base action server to come up");
  }

  move_base_msgs::MoveBaseGoal goal;

  // set up the frame parameters
  goal.target_pose.header.frame_id = "map";
  goal.target_pose.header.stamp = ros::Time::now();

  //Define a boolean variable to confirm if  the robot reached the first position
  bool reachedGoal1= false;
  
  // Define a position and orientation for the robot to reach
  goal.target_pose.pose.position.x = 0.0;
  goal.target_pose.pose.position.y = 2.0;
  goal.target_pose.pose.orientation.w = 1.0;

   // Send the goal position and orientation for the robot to reach
  ROS_INFO("Sending to Pick Up Location");
  ac.sendGoal(goal);

  // Wait an infinite time for the results
  ac.waitForResult();

  // Check if the robot reached its goal
  if(ac.getState() == actionlib::SimpleClientGoalState::SUCCEEDED)
  {
    reachedGoal1=true;
    ROS_INFO("Reached Pick Up Point!");
  }
  else
    ROS_INFO("Failed to reach Pick Up Point for some reason");
 
 if(reachedGoal1)
 {
  	//ros::Duration(5.0).sleep();
  
   	//Assign next target/drop off point
  	goal.target_pose.pose.position.x = -3.0;
  	goal.target_pose.pose.position.y = 0.0;
  	goal.target_pose.pose.orientation.w = 1.0;

   	// Send the goal position and orientation for the robot to reach
  	ROS_INFO("Sending to Drop Off Point");
  	ac.sendGoal(goal);

  	// Wait an infinite time for the results
  	ac.waitForResult();

  	// Check if the robot reached its goal
  	if(ac.getState() == actionlib::SimpleClientGoalState::SUCCEEDED)
  		{ 
    	ROS_INFO("Reached Drop Point!");
    	ros::Duration(1.0).sleep();
      // Code to make robot move away from drop point
    	goal.target_pose.pose.position.x = -3.3;
    	goal.target_pose.pose.position.y = 0.0;
    	ac.sendGoal(goal);
  		}
  	else
    	ROS_INFO("Failed to reach Drop Point Point for some reason");
 }
  return 0;
}
