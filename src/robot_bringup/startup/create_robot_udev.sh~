echo  'KERNEL=="ttyACM*", ATTRS{idVendor}=="2341", ATTRS{idProduct}=="0042", MODE:="0666", GROUP:="dialout",  SYMLINK+="serial_robot_driver"' >/etc/udev/rules.d/serial_robot_driver.rules

service udev reload
sleep 2
service udev restart
