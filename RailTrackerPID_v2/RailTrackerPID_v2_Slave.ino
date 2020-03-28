/*
 * RAILTRACKER v2 – Slave Sketch
 * Created by: Emilostuff, 2020
 * 
 */

#include <Wire.h>
#include <VL53L0X.h>

// Sensor object
VL53L0X sensor;

// Variables
volatile char buf [5] = "0";
volatile int pos;
volatile bool active;
volatile bool doRead = true;
const int readBudget = 15000; // in ms – this duration MUST be some ms shorter than the readInterval in the master Sketch


void setup ()
{

  // have to send on master in, *slave out*
  pinMode(MISO, OUTPUT);

  // turn on SPI in slave mode
  SPCR |= bit(SPE);

  // turn on interrupts
  SPCR |= bit(SPIE);


  // serial for debug
  Serial.begin(115200);

  // I2C communication to sensor
  Wire.begin();
  
  // Setup sensor
  sensor.init();
  sensor.setTimeout(500);
  sensor.setMeasurementTimingBudget(readBudget);
} 



// SPI interrupt routine
ISR (SPI_STC_vect)
{
  byte c = SPDR;

  if (c == 1)  // starting new sequence?
  { 
    doRead = true;
    active = true;
    pos = 0;
    SPDR = buf [pos++];   // send first byte
    return;
  }

  if (!active)
  {
    SPDR = 0;
    return;
  }

  SPDR = buf [pos];
  if (buf [pos] == 0 || ++pos >= sizeof (buf)) {
    active = false;
  }
}



void loop ()
{
  if (doRead) {
    // read sensor
    int value = sensor.readRangeSingleMillimeters();
    Serial.print("New reading: "); Serial.println(value);
    
    // put value into buf
    itoa(value, buf, 10);
    //sprintf(buf, "%05d", value);

    // disable further reading
    doRead = false;
  }
}
