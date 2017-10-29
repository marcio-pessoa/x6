/* x6.ino, x6 Mark I - Robotic Arm, Arduino main sketch file
 * 
 * This sketch was developed and tested on: Arduino Mega 2560
 * To work on other Arduino models, some adaptations may be necessary.
 * 
 * Author: Márcio Pessoa <marcio@pessoa.eti.br>
 * Contributors: none
 */

#include <Arduino.h>         // Arduino - Main library
#include <Servo.h>           // Arduino - Servo Motor
#include <Project.h>         // Sciemon - Basic project definitions
#include <Timer.h>           // Sciemon - Timer library with nice features
#include <RGB.h>             // Sciemon - RGB LED controller
#include <SigGen.h>          // Sciemon - Signal Generator
#include <Alarm.h>           // Sciemon - Manage alarms
#include <Switch.h>          // Sciemon - Switch manipulation
#include <Fan.h>             // Sciemon - Fan speed control
#include <Temperature.h>     // Sciemon - Temperature Sensors
#include <Axis.h>            // Sciemon - Motor axis
#include "config.h"          // Sciemon - Configuration
#include <MemoryFree.h>      // 

// Project definitions
Project x6("x6",  // Platform
           "I",  // Mark
           "Robotic Arm",  // Name
           "0.11b",  // Version
           "2017-06-18",  // Version date
           "2",  // Serial number
           "Copyright (c) 2013-2017 Marcio Pessoa",  // Owner
           "undefined. There is NO WARRANTY.",  // License
           "http://pessoa.eti.br/",  // Website
           "Marcio Pessoa <marcio@pessoa.eti.br>");  // Contact

// RGB LED
RGB led(R_pin, G_pin, B_pin);
SigGen wave;

// Speaker
Timer speaker_period(speaker_timer);
byte speaker_beep_counter = 0;

// Power relays
Switch stage2(relay_stage2_pin,  // Electronic identifier
              LOW,  // Initial state
              true);  // Inverse logic
Switch stage3(relay_stage3_pin,  // Electronic identifier
              LOW,  // Initial state
              true);  // Inverse logic

// Temperature sensors
Temperature microcontroller_TMP36;  // Microcontroller Temperature sensor
Alarm microcontroller_temperature(60,  // Maximum warning
                                  70,  // Maximum critical
                                  10,  // Minimum warning
                                  5);  // Minimum critical
Temperature power_supply_TMP36;  // Power Supply Temperature sensor
Alarm power_supply_temperature(60,  // Maximum warning
                               70,  // Maximum critical
                               10,  // Minimum warning
                               5);  // Minimum critical
Timer temperature_status(temperature_timer * 1000);

// Fan
Fan fan_control(fan_control_pin, fan_sensor_pin);
Alarm fan(80,   // Warning
          90);  // Critical
Timer fan_status(fan_timer * 1000);

// System check
Timer health_check_period(health_check_timer * 1000);

// Demonstration timer
Timer demonstration_period(0, COUNTDOWN);

// Create Servo and Axis objects
Axis axis1("X",        // Name
           axis1_pin,  // Electronic identifier
           0,          // Minimum hard position
           180,        // Maximum hard position
           0,          // Minimum soft position
           180,        // Maximum soft position
           0,          // Park position
           20);        // Move delay
Servo servo1;
Axis axis2("Y",        // Name
           axis2_pin,  // Electronic identifier
           0,          // Minimum hard position
           180,        // Maximum hard position
           0,          // Minimum soft position
           180,        // Maximum soft position
           30,         // Park position
           20);        // Move delay
Servo servo2;
Axis axis3("Z",        // Name
           axis3_pin,  // Electronic identifier
           0,          // Minimum hard position
           180,        // Maximum hard position
           0,          // Minimum soft position
           180,        // Maximum soft position
           0,          // Park position
           12);        // Move delay
Servo servo3;
Axis axis4("U",        // Name
           axis4_pin,  // Electronic identifier
           0,          // Minimum hard position
           155,        // Maximum hard position
           0,          // Minimum soft position
           155,        // Maximum soft position
           82,         // Park position
           12);        // Move delay
Servo servo4;
Axis axis5("V",        // Name
           axis5_pin,  // Electronic identifier
           0,          // Minimum hard position
           180,        // Maximum hard position
           0,          // Minimum soft position
           180,        // Maximum soft position
           10,         // Park position
           10);        // Move delay
Servo servo5;
Axis axis6("W",        // Name
           axis6_pin,  // Electronic identifier
           0,          // Minimum hard position
           160,        // Maximum hard position
           0,          // Minimum soft position
           160,        // Maximum soft position
           75,         // Park position
           8);         // Move delay
Servo servo6;
Axis axis7("T",        // Name
           axis7_pin,  // Electronic identifier
           0,          // Minimum hard position
           145,        // Maximum hard position
           0,          // Minimum soft position
           145,        // Maximum soft position
           90,         // Park position
           2);         // Move delay
Servo servo7;

// Wait timer - Wait between moves
Timer wait(0, COUNTDOWN);
Timer wait1(0, COUNTDOWN);
Timer wait2(0, COUNTDOWN);
Timer wait3(0, COUNTDOWN);
Timer wait4(0, COUNTDOWN);
Timer wait5(0, COUNTDOWN);
Timer wait6(0, COUNTDOWN);
Timer wait7(0, COUNTDOWN);

// Power save options
Timer standby((unsigned long)standby_timer * 60 * 1000, COUNTDOWN);
bool standby_status = false;
bool standby_done = true;

// Function definitions
bool CommandM80(byte stage = 0);
bool CommandM81(byte stage = 0);

void setup() {
  // Serial interface
  Serial.begin(serial_speed);
  // Start up message
  echoln("Starting...");
  CommandM92();  // System information
  // Power relays
  stage2.nameWrite("Stage 2");
  stage3.nameWrite("Stage 3");
  if (stage3.status() == false) standby.disable();
  // Power supply DC detection
  pinMode(power_sensor_pin, INPUT);
  // Temperature sensors
  microcontroller_TMP36.attach(microcontroller_temperature_pin);
  microcontroller_TMP36.type(TMP36);
  microcontroller_temperature.nameWrite("Microcontroller temperature");
  microcontroller_temperature.unitWrite(" *C");
  microcontroller_temperature.force_check(OK);  //TODO(Marcio): Remove after sensor installation
  power_supply_TMP36.attach(power_supply_temperature_pin);
  power_supply_TMP36.type(TMP36);
  power_supply_temperature.nameWrite("Power supply temperature");
  power_supply_temperature.unitWrite(" *C");
  power_supply_temperature.force_check(OK);  //TODO(Marcio): Remove after sensor installation
  // Fan
  fan_control.writeSpeed(100);
  attachInterrupt(fan_sensor_pin, spinCounter, RISING);
  fan.force_check(OK);
  fan.nameWrite("Fan");
  fan.unitWrite("%");
  // Attach servo motors
  CommandM17();
  // Random number generator seed
  pinMode(random_Seed_pin, INPUT);
  randomSeed(analogRead(random_Seed_pin));
  // Start up sound
  tone(speaker_pin, 2217, 60);
  // G-code ready to receive commands
  GcodeReady();
}

void loop() {
  SensorsHandler();
  HealthCheckHandler();
  NotificationHandler();
  AxesHandler();
  DemonstrationHandler();
  PowerHandler();
  GcodeCheck();
}
