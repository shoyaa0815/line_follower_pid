int mid = 2;  // Sensor threshold for line detection

void motor(int B, int A)  // Control left motor (B) and right motor (A)
{
  if (A >= 0)  // Right motor forward
  {
    analogWrite(5, A);
    analogWrite(6, 0);
  }
  else  // Right motor backward
  {
    analogWrite(5, 0);
    analogWrite(6, abs(A));
  }
  if (B >= 0)  // Left motor forward
  {
    analogWrite(9, B);
    analogWrite(10, 0);
  }
  else  // Left motor backward
  {
    analogWrite(9, 0);
    analogWrite(10, abs(B));
  }
}

void black(){  // Move forward until black line is detected
  motor(100,100);
  delay(20);
  while(sensor_read(0) > mid && sensor_read(5) > mid);
    motor(0,0);
}

void turn_left(){  // Turn left until center sensor finds line
  motor(-100,100);
  delay(50);
  while(sensor_read(2)>mid){
      motor(-100,100);
  }
   while(sensor_read(2)<mid){
      motor(-100,100);
  }
    motor(0,0);
}

void turn_right(){  // Turn right until center sensor finds line
  motor(100,-100);
  delay(150);
  while(sensor_read(3)>mid){
      motor(100,-100);
  }
   while(sensor_read(3)<mid){
      motor(100,-100);
  }
  motor(0,0);
}
