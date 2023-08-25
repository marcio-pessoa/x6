/* config.h, x6 Mark I - Robotic Arm, Arduino project config file
 *
 * Author: Márcio Pessoa <marcio.pessoa@gmail.com>
 * Contributors: none
 */

// LED
const byte R_pin = 25;
const byte G_pin = 24;
const byte B_pin = 13;

// Speaker
const byte speaker_pin = 12;
const int speaker_timer = 250; // milliseconds

// Power
const byte power_sensor_pin = 43;
const byte relay_stage2_pin = 44;
const byte relay_stage3_pin = 45;

// Axis
const byte axis1_pin = 2;
const byte axis2_pin = 3;
const byte axis3_pin = 4;
const byte axis4_pin = 5;
const byte axis5_pin = 6;
const byte axis6_pin = 7;
const byte axis7_pin = 8;

// Temperature
const byte power_supply_temperature_pin = 15;
const byte microcontroller_temperature_pin = 0;

// Fan
const byte fan_control_pin = 11;
const byte fan_sensor_pin = 2;

// Random number generator Seed pin
const byte random_Seed_pin = 14;

// Timers
const byte health_check_timer = 2; // seconds
const byte temperature_timer = 2;  // seconds
const byte fan_timer = 2;          // seconds
const byte standby_timer = 2;      // minutes

// Debug mode
bool debug_mode = false;

// Serial speed: 4800, 9600, 14400, 19200, 28800, 38400, 57600, 115200
const unsigned long serial_speed = 115200;

// Gerenal status (initial state)
byte general_status = OK;

// Move done
bool done = true;

//
const int FLIMIT = 32767;
