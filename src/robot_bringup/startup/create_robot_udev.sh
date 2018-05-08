echo  'KERNEL=="ttyUSB*", ATTRS{idVendor}=="1a86", ATTRS{idProduct}=="7523", MODE:="0666", GROUP:="dialout",  SYMLINK+="serial_robot_driver"' >/etc/udev/rules.d/serial_robot_driver.rules

service udev reload
sleep 2
service udev restart
