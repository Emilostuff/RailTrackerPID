void loop (void)
{
  // Read sensor if due
  readSPI();

  // Check if a limit has been hit
  testLimits();

  // Compute new PID if due
  pid();

  // Check for serial input
  checkSerial();

}
