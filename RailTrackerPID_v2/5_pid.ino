void pid ()
{
  long now = millis();

  if (now - timer_pid > 5)
  {
    // reset timer
    timer_pid = now;

    // Check for activation
    if (!activated)
    {
      setNewSpeed(0);
      return;
    }

    // Check that enough values have been recorded to initiate movement
    if (actCount < 5)
    {
      setNewSpeed(0);
      actCount++;
      return;
    }

    // Do PID
    float error = float(setPoint - dist);

    // Integral
    integral += error;

    if (integral > int_max) {
      integral = int_max;
    }
    if (integral < -int_max) {
      integral = -int_max;
    }

    // Derivative
    float derivative = error - lastError;
    
    derivative = d_tf * derivative + (1-d_tf) * lastDerivative;
    lastDerivative = derivative;
    lastError = error;

    // Calculate new speed
    float newSpeed = kp * error + ki * integral + kd * derivative;

    // add filter to speed for smoothness
    newSpeed = s_tf * newSpeed + (1-s_tf) * lastSpeed;
    lastSpeed = newSpeed;
    
    setNewSpeed(newSpeed);

    // print for debug
    /*Serial.print(error);
    Serial.print(",");
    Serial.println(newSpeed / 5); */
  }
}
