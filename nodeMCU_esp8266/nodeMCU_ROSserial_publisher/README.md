## NodeMCU Esp8266 ROS_serial Publisher
Upload [sketch](https://www.arduino.cc/en/tutorial/sketch) to NodeMCU from [Arduino IDE](https://www.arduino.cc/en/main/software).
Connect to wireless access point by ESP.

Echo msgs published by `chatter`, run each in separate terminals
```
    $ roscore
    $ rosrun rosserial_python serial_node.py tcp
    $ rostopic echo /chatter
```
