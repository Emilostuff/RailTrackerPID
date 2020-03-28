

void readSPI ()
{
  // get current time
  long now = millis();

  // read SPI if a read is due
  if (now - timer_read > readInterval) {
    
    // reset timer
    timer_read = now;

    // init buffer
    char buf [5];

    // enable Slave Select
    digitalWrite(SS, LOW);
    SPI.transfer (1);   // initiate transmission
    for (int pos = 0; pos < sizeof (buf) - 1; pos++)
    {
      delayMicroseconds (150);
      buf [pos] = SPI.transfer (0);
      if (buf [pos] == 0)
      {
        break;
      }
    }

    buf [sizeof (buf) - 1] = 0;  // ensure terminating null

    // disable Slave Select
    digitalWrite(SS, HIGH);

    // process value
    processValue(atoi(buf));
  }
}
