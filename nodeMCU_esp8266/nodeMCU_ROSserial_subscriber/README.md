## NodeMCU Esp8266 ROS_serial Subscriber
Upload [sketch](https://www.arduino.cc/en/tutorial/sketch) to NodeMCU from [Arduino IDE](https://www.arduino.cc/en/main/software) and open [Serial Monitor](https://www.arduino.cc/en/guide/environment#toc12).
Connect to wireless access point by ESP.

Publish msgs to `chatter_`, run each in separate terminals
```
    $ roscore
    $ rosrun rosserial_python serial_node.py tcp
    $ rostopic pub /chatter_ std_msgs/String "data: '<your msg here>'" --once
```
