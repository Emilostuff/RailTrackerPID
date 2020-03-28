/*
 * HOW TO USE THE SERIAL FOR TUNING
 * 
 * To select parameter, input:
 * 'p' for proportional control
 * 'i' for integral control
 * 'd' for derivative control
 * 't' for trust factor of sensorvalue
 * 'e' for trust factor of derivate value (experimental)
 * 's' for trust factor of speed.
 * 
 * To change current parameter, input new value in either int or float
 * NB: for all trust factors only a value between 0.0 and 1.00 is accepted.
 * 
 */


void checkSerial ()
{

  // check for serial input
  if (readline(Serial.read(), buf, 80) > 0)
  {

    // check for characters
    if (buf[0] == 'p')
    {
      tuningVariable = 0;
      Serial.println();
      Serial.println("Proportional gain selected.");
      Serial.print("Current value: "); Serial.println(kp);
      return;
    }
    if (buf[0] == 'i')
    {
      tuningVariable = 1;
      Serial.println();
      Serial.println("Integral gain selected.");
      Serial.print("Current value: "); Serial.println(ki);
      return;
    }
    if (buf[0] == 'd')
    {
      tuningVariable = 2;
      Serial.println();
      Serial.println("Derivative gain selected");
      Serial.print("Current value: "); Serial.println(kd);
      return;
    }

    if (buf[0] == 't')
    {
      tuningVariable = 3;
      Serial.println();
      Serial.println("Trustfactor selected");
      Serial.print("Current value: "); Serial.println(tf);
      return;
    }

    if (buf[0] == 'e')
    {
      tuningVariable = 4;
      Serial.println();
      Serial.println("Derivative trustfactor selected");
      Serial.print("Current value: "); Serial.println(d_tf);
      return;
    }

    if (buf[0] == 's')
    {
      tuningVariable = 5;
      Serial.println();
      Serial.println("Speed trustfactor selected");
      Serial.print("Current value: "); Serial.println(s_tf);
      return;
    }

    if (buf[0] == 'a')
    {
      Serial.println();
      Serial.println("Printing all variables:");
      Serial.print("kp: "); Serial.println(kp);
      Serial.print("ki: "); Serial.println(ki);
      Serial.print("kd: "); Serial.println(kd);
      Serial.print("tf: "); Serial.println(tf);
      Serial.print("d_tf: "); Serial.println(d_tf);
      Serial.print("s_tf: "); Serial.println(s_tf);
      return;
    }


    // No characters, then assume number:
    if  (tuningVariable == 0)
    {
      // adjust proportional gain
      kp = atof(buf);
      Serial.print("New value: "); Serial.println(kp);
      return;
    }
    if  (tuningVariable == 1)
    {
      // adjust integral gain
      ki = atof(buf);
      Serial.print("New value: "); Serial.println(ki);
      return;
    }
    if  (tuningVariable == 2)
    {
      // adjust proportional gain
      kd = atof(buf);
      Serial.print("New value: "); Serial.println(kd);
      return;
    }

    if  (tuningVariable == 3)
    {
       tf = atof(buf);
       if (tf > 1.00)
      {
        tf = 1.00;
      }
      Serial.print("New value: "); Serial.println(tf);
      return;
    }

    if  (tuningVariable == 4)
    {
      d_tf = atof(buf);
      if (d_tf > 1.00)
      {
        d_tf = 1.00;
      }
      Serial.print("New value: "); Serial.println(d_tf);
      return;
    }

    if  (tuningVariable == 5)
    {
      s_tf = atof(buf);
      if (d_tf > 1.00)
      {
        d_tf = 1.00;
      }
      Serial.print("New value: "); Serial.println(s_tf);
      return;
    }






  }
}


// used to read serial input
int readline(int readch, char *buffer, int len)
{
  static int pos = 0;
  int rpos;

  if (readch > 0) {
    switch (readch) {
      case '\r': // Ignore CR
        break;
      case '\n': // Return on new-line
        rpos = pos;
        pos = 0;  // Reset position index ready for next time
        return rpos;
      default:
        if (pos < len - 1) {
          buffer[pos++] = readch;
          buffer[pos] = 0;
        }
    }
  }
  return 0;
}
