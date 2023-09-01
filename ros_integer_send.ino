#define __STM32F1__ //for stm32 bluepill usb serial comms

#include <ros.h>
#include <std_msgs/Int32.h>

//#include <Arduino.h>

// Initialize ROS node handle

ros::NodeHandle nh;

// Define the publisher
std_msgs::Int32 int_msg_1;
std_msgs::Int32 int_msg_2;
ros::Publisher int_publisher1("load_cell_topic1", &int_msg_1);
ros::Publisher int_publisher2("load_cell_topic2", &int_msg_2);

Load_cell LC1(PB12,PB13, 207); //CHANGE SCALE SET
Load_cell LC2(PB11,PB10, 207); //CHANGE SCALE SET


void setup() {
  // Initialize serial communication
  //Serial.begin(57600);

  nh.initNode();
  nh.advertise(int_publisher1);
  nh.advertise(int_publisher2);
  nh.getHardware()->setBaud(57600); //defining the baudrate instead of variable
  LC1.init();
  LC2.init();
}

void loop() {
  // Publish the integer value
  int_msg_1.data = LC1.weight(); // weight coming from load cell
  int_msg_2.data = LC2.weight(); // weight coming from load cell
  int_publisher1.publish(&int_msg_1);
  int_publisher2.publish(&int_msg_2);

  // Handle ROS callbacks
  nh.spinOnce();

  // Add a delay
  delay(1000);
}
