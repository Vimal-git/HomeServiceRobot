#!/bin/sh
xterm  -e  " roslaunch turtlebot_gazebo turtlebot_world.launch world_file:=$(rospack find map)/vimal.world" &
sleep 5
xterm  -e  " roslaunch turtlebot_gazebo amcl_demo.launch map_file:=$(rospack find map)/nav_map.yaml " &
sleep 5
xterm  -e  " roslaunch rvizConfig rviz_navigation.launch " &
sleep 5
xterm  -e  " rosrun add_markers add_markers " &
sleep 5
xterm  -e  " rosrun pick_objects pick_objects " 
