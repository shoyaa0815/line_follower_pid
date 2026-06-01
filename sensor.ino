void calibrateBlack()
{
  while (1)
  {
    if (analogRead(0) > sensor_midpoint)
    {
      break;
    }
    for (int i = 0; i < 6; i++)
    {
      sensor_max[i] = max(sensor_max[i], analogRead(i));
      sensor_min[i] = min(sensor_min[i], analogRead(i));
    }
  }
}

void calibrateWhite()
{
  while (1)
  {
    if (analogRead(0) < sensor_midpoint)
    {
      break;
    }
    for (int i = 0; i < 6; i++)
    {
      sensor_min[i] = min(sensor_min[i], analogRead(i));
      sensor_max[i] = max(sensor_max[i], analogRead(i));
    }
  }
}

float sensor_read(int i)
{
  float filtered = (analogRead(i) * alpha) + ((1 - alpha) * last_filtered_value[i]);
  last_filtered_value[i] = filtered;
  
  float normalized = constrain(((((analogRead(i) - sensor_min[i]) * 10) / sensor_max[i]) - 2.7), 0, 3);
  return (normalized - 3) * -1;
}

void test_processed_sensor()
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

void test_raw_sensor()
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

int get_positional_error()
{
  float sum_weighted_products = (sensor_read(0) * 10) + (sensor_read(1) * 20) + (sensor_read(2) * 30) + (sensor_read(3) * 40) + (sensor_read(4) * 50);
  float sum_sensor_values = sensor_read(0) + sensor_read(1) + sensor_read(2) + sensor_read(3) + sensor_read(4);
  
  if (sum_sensor_values == 0)
  {
    return 0;
  }
  
  return sum_weighted_products / sum_sensor_values;
}