
void setup (void)
{
  // Serial setup
  Serial.begin (250000);
  Serial.println ("Starting up ...");

  // SPI setup
  pinMode(SS, OUTPUT);
  digitalWrite(SS, HIGH); 
  SPI.begin ();
  SPI.setClockDivider(SPI_CLOCK_DIV8);

  // Init limit pins
  pinMode(LIMIT_FRONT, INPUT_PULLUP);
  pinMode(LIMIT_BACK, INPUT_PULLUP);

  // init encoder motor
  Encoder_1.setPulsePos(0); // only relevant for my implentation with the Makeblock encoder
  Encoder_1.setRatio(46.67); // only relevant for my implentation with the Makeblock encoder
  Encoder_1.setMotionMode(DIRECT_MODE); // only relevant for my implentation with the Makeblock encoder

  // Test that no limit switch is pressed
  void testLimits();

  // Make a little movement to signal the system is ready
  Encoder_1.setMotorPwm(30);
  delay(100);
  Encoder_1.setMotorPwm(-30);
  delay(100);
  Encoder_1.setMotorPwm(0);

  Serial.println("ready");
}  
