#include <ESP8266WiFi.h>
#include <ros.h>
#include <std_msgs/String.h>

/*  ESP AP Config.  */
#ifndef APSSID
#define APSSID "ESP_AP"
#define APPSK  "ROSserial@nodeMCU"
#endif

const char *ssid = APSSID;
const char *password = APPSK;

/*  ROS  */
IPAddress server(192,168,4,2);
const uint16_t serverPort = 11411;

ros::NodeHandle nh;
std_msgs::String str_msg;
ros::Publisher chatter("chatter", &str_msg);

char firstMsg[5] = "Hey,"; bool recievedFirstMsg = false;
char msgtxt[19] = "Message Recieved !";

void setup() {
  ESP.eraseConfig();
  WiFi.disconnect(true);
  WiFi.mode(WIFI_AP);
  WiFi.softAP(ssid, password);
  delay(1000);
  
  nh.getHardware()->setConnection(server, serverPort);
  nh.initNode();
  nh.advertise(chatter);
}

void loop() {
  if (nh.connected()) {
    if(!recievedFirstMsg){
      str_msg.data = firstMsg;
      chatter.publish( &str_msg );
      recievedFirstMsg = true;
    }
    str_msg.data = msgtxt;
    chatter.publish( &str_msg );
  } else {
    // Don't publish unless connected..
    recievedFirstMsg = false;
  }
  nh.spinOnce();
  delay(1000);
}
