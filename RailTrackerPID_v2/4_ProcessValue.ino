void processValue (int input)
{
  // start by excluding unwanted/bad values and do nothing
  if (input > 500)
  {
    activated = false;

    // reset all accumulated values.
    actCount = 0;
    integral = 0;
    lastError = 0;
    lastSpeed = 0;
    return;
  }

  // Value is good. Activate.
  activated = true;

  // compute new value with trustfactor
  dist = tf * input + (1 - tf) * dist;

  // debug
  //Serial.println(dist);
}
