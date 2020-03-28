
void setNewSpeed (float speed)
{
  // Limit max speed
  if (speed > maxSpeed) 
  {
    speed = maxSpeed;
  }
  else if (speed < -maxSpeed) 
  {
    speed = -maxSpeed;
  }

  // Set speed
  Encoder_1.setMotorPwm(-speed);

  // Debug
  //Serial.println(-speed);
  

}

void testLimits() {
  
  // Read front limit
  if (digitalRead(LIMIT_FRONT) == LOW) {
    Serial.println("Front limit hit!");
    Encoder_1.setMotorPwm(-60);
    delay(1000);
  }

  // read back limit
  else if (digitalRead(LIMIT_BACK) == LOW) {
    Serial.println("Back limit hit!");
    Encoder_1.setMotorPwm(60);
    delay(1000);
  }
}
