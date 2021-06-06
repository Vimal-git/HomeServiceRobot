This project was submitted as part of Udacity's, Robotic Software Engineer, Nano Degree program.
The codes in the files are developed from the learning material provided in the program.
This project was developed in ROS-Kinetic.

The link addresses from which packages required of launch files were downloaded are  provided below:
1)gmapping_demo.launch  requires the package gmapping from https://github.com/ros-perception/slam_gmapping
2)keyboard_teleop.launch requires the package turtlebot_teleop from https://github.com/turtlebot/turtlebot
3)view_navigation.launch requires the package turtlebot_rviz_launchers from  https://github.com/turtlebot/turtlebot_interactions
4)turtlebot_world.launch requires the package turtlebot_gazebo from https://github.com/turtlebot/turtlebot_simulator

Other packages created as part of the project are
1)map: contain the vimal.world file in which the robot is to be launched and also contains nav_map.pgm and nav_map.yaml files required to load the map of world in Rviz.
2)rvizConfig: It contains saved rviz configuration called rviz_nav.rviz and a launch file named rviz_navigation.launch to launch this configuration in Rviz.
3)pick_objects: This package has an executable pick_objects.cpp file acting as a ros node to move the turtlebot. It is run with the command
rosrun pick_objects pick_object
4)add_markers:This package has two executable cpp files
i) add_markers.cpp:It acts as a ros node to publish a marker based on turtlebot pos obtained from subscription to odometry. It is run while processing ./home_service.sh with the following command included in the home_service.sh file: 
rosrun add_markers add_markers
ii)add_markers1.cpp:It acts as a ros node to add a marker at a particular location and maintain it for 5s and then delete it for 5s and then display it at another location.It is run by executing ./add_markers.sh with the following command included in the add_markers.sh file:
rosrun add_markers add_markers1

Running the Project
1)Downloadrun catkin_make from the catkin_ws directory in the folder of HomeServiceRobot
2)run source devel/setup.bash
3)run cd src/scripts
4)run ./test_navigation.sh to make turtlebot move to target locations manually selected on map displayed in Rviz. 
5)run ./add_markers.sh runs with other mandatory files the program in add_markers1.cpp in add_markers pakage to vary the position of a marker on map displayed in Rviz.
6)run ./home_service.sh runs with other mandatory files the program in add_markers.cpp in add_markers pakage and pick_objects.cpp in pick_objects package to simulate a robotic pick and drop action.
7)run ./test_slam.sh to generate a map by moving the turtlebot around via the keyboard keys.
8)All the required .sh files are saved in the HomeServiceRobot/catkin_ws/src/scripts folder.