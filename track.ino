void track_line() {
  while (1) {
    error = get_positional_error() - target_position;
    
    if (sensor_read(2) > white_threshold && sensor_read(3) > white_threshold && sensor_read(4) > white_threshold
        && sensor_read(0) > white_threshold && sensor_read(1) > white_threshold) {
      motor(0, 0);
      break; 
    }
    else {
      integral = error + integral;
      motor_speed_offset = (error * KP) + ((error - last_error) * KD) + (integral / KI);
      last_error = error;
      
      Serial.println(get_positional_error());
      
      motor(constrain(BASE_SPEED - motor_speed_offset, -255, 255), constrain(BASE_SPEED + motor_speed_offset, -255, 255));
    }
  }
}