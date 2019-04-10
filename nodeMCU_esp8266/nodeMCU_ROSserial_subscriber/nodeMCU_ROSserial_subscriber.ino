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

void messageCb(const std_msgs::String& str_msg){
  String txt;
  txt = str_msg.data;
  Serial.println(txt);
  int blinkCount = txt.length();
  for(int i=1;i<=blinkCount;i++){
    digitalWrite(LED_BUILTIN, HIGH-digitalRead(LED_BUILTIN));
    delay(200);
    digitalWrite(LED_BUILTIN, HIGH-digitalRead(LED_BUILTIN));
    delay(200);
  }
}

ros::Subscriber<std_msgs::String> sub("chatter_", &messageCb);

void setup() {
  ESP.eraseConfig();
  WiFi.disconnect(true);
  WiFi.mode(WIFI_AP);
  WiFi.softAP(ssid, password);
  delay(1000);

  Serial.begin(9600);
  pinMode(LED_BUILTIN,OUTPUT);

  nh.getHardware()->setConnection(server, serverPort);
  nh.initNode();
  nh.subscribe(sub);
}

void loop() {
  nh.spinOnce();
  delay(1);
}
