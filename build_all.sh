#!/bin/bash
catkin_make clean
catkin_make -DCATKIN_WHITELIST_PACKAGES="people_msgs;move_base_msgs;awaken_asr" --make-args -j4
catkin_make -DCATKIN_WHITELIST_PACKAGES="" --make-args -j4
