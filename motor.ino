void motor(int speed_B, int speed_A)
{
  if (speed_A >= 0)
  {
    analogWrite(5, speed_A);
    analogWrite(6, 0);
  }
  else
  {
    analogWrite(5, 0);
    analogWrite(6, abs(speed_A));
  }
  
  if (speed_B >= 0)
  {
    analogWrite(7, speed_B);
    analogWrite(10, 0);
  }
  else
  {
    analogWrite(7, 0);
    analogWrite(10, abs(speed_B));
  }
}

void move_over_black(){
  motor(100, 100);
  delay(20);
  while(sensor_read(0) > line_detect_level && sensor_read(5) > line_detect_level);
  motor(0, 0);
}

void turn_left(){
  motor(-100, 100);
  delay(50);
  while(sensor_read(2) > line_detect_level){
      motor(-100, 100);
  }
  while(sensor_read(2) < line_detect_level){
      motor(-100, 100);
  }
  motor(0, 0);
}

void turn_right(){
  motor(100, -100);
  delay(150);
  while(sensor_read(3) > line_detect_level){
      motor(100, -100);
  }
  while(sensor_read(3) < line_detect_level){
      motor(100, -100);
  }
  motor(0, 0);
}