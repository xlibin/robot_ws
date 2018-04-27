#!/bin/bash
catkin_make clean
catkin_make -DCATKIN_WHITELIST_PACKAGES="people_msgs"
catkin_make -DCATKIN_WHITELIST_PACKAGES="move_base_msgs"
catkin_make -DCATKIN_WHITELIST_PACKAGES="awaken_asr"
catkin_make -DCATKIN_WHITELIST_PACKAGES="" --make-args -j4
