/*
 * RAILTRACKER v2
 * Created by: Emilostuff, 2020
 * 
 * INTRODUCTION
 * This software is based on using an encoder motor from the company Makeblock, thus the implentation is really simple.
 * You can with no problem use your own encoder motor (or even another motor), you just have to rewrite that part of the code.
 * 
 * Im also using a VL53L0X V2 Laser Ranging Sensor Module. 
 * You can use your own sensor, but you will have to make your own implementation.
 * The sensor is attatched to another microcontroller, that we communicate with via SPI.
 * Check out the SPI slave sketch for the sensor implentation.
 * 
 * I have released this coded mainly because of numerous requests, and I think many of you mostly wants to see 
 * my implementation, not build the exact same machine. 
 * 
 * TUNING
 * This sketch is made to make tuning fun. All PID parameters are therefore set to 0 from start up. 
 * You can then adjust them LIVE through the serial.
 * Check out tab 7_serial for instructions
 * 
 * DISCLAIMER
 * This is definetely not straight forvard to make yourself, and I have given no complete set of instructions.
 * First and foremost I hope this sketch provides answers to the questions I have received.
 * 
 */

// Setup //////////////////////////////////////////////////////

// You will (ideally) need:
/*
 * - 2x microcontrollers with SPI interface. (eg. 2x Arduino Nano/Uno/Mega).
 * - 1x VL53L0X V2 Laser Ranging Sensor Module
 * - 1x encoder motor + driver module.
 * - a belt/track system
 * - 2x endstop switches (not nessecary, but will prevent you potentially destroying the machine).
 */

// You will have to make these connections:
/*
 * Encoder motor driver -> master microcontroller & power (specific connections might vary)
 * VL53L0X V2 -> slave microcontroller VIA I2C (SDA, SCL, 5V/3.3V and ground).
 * Slave microcontroller -> master microcontroller via SPI (MOSI, MISO, SCL and SS) 
 * Slave microcontroller -> master microcontroller 5V/3.3V and ground for powersharing (optional, but recommended).
 */

// NB: This sketch should be uploaded to the master microcontroller

 
// Includes //////////////////////////////////////////////////////
#include <SPI.h>
#include <MeMegaPi.h> // only relevant for my implentation with the Makeblock encoder
#include "MeEEPROM.h" // only relevant for my implentation with the Makeblock encoder


// System parameters /////////////////////////////////////////////
const int readInterval = 20; // time between SPI readings in ms. If changed, remember to set readtime at slave to a shorter interval

const int setPoint = 100; // desired distance to sensor
const float maxSpeed = 300; // Limits maximum motor speed


// PID Tuning constants ////////////////////////////////////////// 
float kp = 0;
float ki = 0.0;
float kd = 0;

float int_max = 1000; // maximum integral value

/* I got good results with these value:
 *  kp: 5.00
 *  ki: 0.01
 *  kd: 2000.00
 *  int_max = 1000
 */


// Trustfactors ////////////////////////////////////////// 
float tf = 1; // Trust factor for new readings (used for filtering input values);
float d_tf = 1; // Trust factor for derivative value (experimental)
float s_tf = 1; //Trust factor for the output speed value (used for filtering motor speed for more smooth motion);

/* I got good results with these value:
 * tf: 1.00
 * d_tf: 1.00
 * s_tf: 0.005
 */
 

// Objects ///////////////////////////////////////////////////////
MeEncoderOnBoard Encoder_1(SLOT1); // only relevant for my implentation with the Makeblock encoder


// PID Algorith variables ////////////////////////////////////////
float integral = 0;
float lastError = 0;
float lastDerivative = 0;
float lastSpeed = 0;


// System variables //////////////////////////////////////////////
int dist = 0; // Current value from sensor
bool activated = false;  
int actCount = 0; // Counter used to delay reactivation
int tuningVariable = 0; // selects which parameter is tuned - check the 7_serial tab
char buf[80]; // Serial buffer


// Timers ////////////////////////////////////////////////////////
long timer_read = 0; 
long timer_pid = 0;


// Pins //////////////////////////////////////////////////////////
#define SS 60 // set pin for slave select
#define LIMIT_BACK 61 // set pin for limit switch
#define LIMIT_FRONT 62 // set pin for limit switch
