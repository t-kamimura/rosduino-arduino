/* rosduino_motor */

#include <ros.h>
#include <std_msgs/String.h>
#include "geometry_msgs/Twist.h"

// set pin numbers:
const int analogPin1 =  5;
const int analogPin2 =  6;
const int analogPin3 =  9;
const int analogPin4 =  10;

double vel,avel;
double wr_tmp, wl_tmp;
double right,left;
double r_flg,l_flg;

void VelCallback(const geometry_msgs::Twist& msg)
{
//  vel = msg.linear.x;
//  avel = msg.angular.z;
  r_flg =msg.linear.y;
  l_flg =msg.linear.z;
  right = msg.angular.x;
  left = msg.angular.y;
  
  if(r_flg>0.5)
  {
    analogWrite(analogPin1, 0);
    analogWrite(analogPin2, int(left));
  }
  else
  {
    analogWrite(analogPin1, int(left));
    analogWrite(analogPin2, 0);
  }
  
  if(l_flg>0.5)
  {
    analogWrite(analogPin3, 0);
    analogWrite(analogPin4, int(right));
  }
  else
  {
    analogWrite(analogPin3, int(right));
    analogWrite(analogPin4, 0);
  }
}

std_msgs::String str_msg;
ros::NodeHandle  n;
ros::Subscriber<geometry_msgs::Twist> sub("cmd_vel", VelCallback);
ros::Publisher chatter("chatter", &str_msg);
char hello[13] = "hello world!";

void setup()
{
  n.initNode();
  n.subscribe(sub);
  n.advertise(chatter);
  pinMode(analogPin1, OUTPUT);
  pinMode(analogPin2, OUTPUT);
  pinMode(analogPin3, OUTPUT);
  pinMode(analogPin4, OUTPUT);
}

void loop()
{
  str_msg.data = hello;
  chatter.publish( &str_msg );
  n.spinOnce();
  delay(100);
}
