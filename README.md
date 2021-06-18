# ROS-HomeServiceRobot
This project contains files to launch a turtlebot in a virtual environment in Gazebo and Rviz.
* The launched turtlebot simulates a pick and place operation in the virtual environment.
* The turtlebot can be moved around by keyboard keys to generate a map of the virtual environment.

## Prerequisites
* Ubuntu 16.04 OS or above
* ROS Kinetic
* Gazebo
* Rviz

## Running the project
* Clone the repository and cd to catkin_ws/src
* run catkin_init_workspace
* run cd .. 
* run catkin_make
* cd to src/scripts
* run ./home_service.sh  ` to simulate pick and place robot action `
* run ./test_slam.sh ` to generate a map `

## Acknowledgement
This project was developed from starter codes provided as part of *Udacity's Robotics Software Engineer Nano Degree Program*
and repos were cloned from the following links
* https://github.com/ros-perception/slam_gmapping
* https://github.com/turtlebot/turtlebot
* https://github.com/turtlebot/turtlebot_interactions
* https://github.com/turtlebot/turtlebot_simulator
