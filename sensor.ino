
void calibrateOnWhite()
{
  while (1)
  {
    if (analogRead(0) < smid)
    {
      break;
    }
    for (int i = 0; i < 6; i++)
    {
      smin[i] = min(smin[i], analogRead(i));
      smax[i] = max(smax[i], analogRead(i));
    }
  }
}
void calibrateOnBlack()
{
  while (1)
  {
    if (analogRead(0) > smid)
    {
      break;
    }

    for (int i = 0; i < 6; i++)
    {
      smax[i] = max(smax[i], analogRead(i));
      smin[i] = min(smin[i], analogRead(i));
    }
  }
}


float sensor_read(int i)
{
  float q = (analogRead(i) * alpha) + ((1 - alpha) * lastalpha[i]);
  lastalpha[i] = q;
  float smean = constrain(((((analogRead(i) - smin[i]) * 10) / smax[i]) - 2.7), 0, 3);

  return (smean - 3) * -1;
}

void test_sensor()
{
  while (1)
  {
    for (int i = 0; i < 6; i++)
    {
      Serial.print(sensor_read(i));
      Serial.print(", ");
    }
    Serial.println();
    delay(100);
  }
}

void test_rawSensor()
{
  while (1)
  {
    for (int i = 0; i < 6; i++)
    {
      Serial.print(analogRead(i));
      Serial.print(", ");
    }
    Serial.println();
    delay(100);
  }
}

int positional()
{
  float ssum = (sensor_read(0) * 10) + (sensor_read(1) * 20) + (sensor_read(2) * 30) + (sensor_read(3) * 40) + (sensor_read(4) * 50);
  float saverage = sensor_read(0) + sensor_read(1) + sensor_read(2) + sensor_read(3) + sensor_read(4);
  int total = ssum / saverage;
  if (saverage == 0)
  {
    total = 0;
  }
  return total;
}