// #define speed 160  // Base motor speed for line following
// float white = 2.5;  // Threshold for detecting white surface
// #define kp 12  // Proportional gain for PID control
// #define kd 15    // Derivative gain for PID control  
// #define ki 3000 // Integral gain for PID control   

// #define speed 200  // Base motor speed for line following
// float white = 2.5;  // Threshold for detecting white surface
// #define kp 13  // Proportional gain for PID control
// #define kd 18    // Derivative gain for PID control  
// #define ki 3200 // Integral gain for PID control   

#define speed 200  // Base motor speed for line following
float white = 2.5;  // Threshold for detecting white surface
#define kp 15  // Proportional gain for PID control
#define kd 25    // Derivative gain for PID control  
#define ki 30000 // Integral gain for PID control   



void track() {  // Main line following function using PID control
  while (1) {
    error = positional() - 30;  // Calculate position error from center
    if (sensor_read(2) > white && sensor_read(3) > white && sensor_read(4) > white
        && sensor_read(0) > white 
        && sensor_read(1) > white ) {  // All sensors see black
      motor(0, 0);
      break;
    }
    else if (0) {
      
    } 
    else {
      integrel = error + integrel;  // Accumulate error for integral term
      motorspeed = (error * kp) + ((error - last_error) * kd) + (integrel / ki);  // PID calculation
      last_error = error;  // Store error for next derivative calculation
      Serial.println(positional());
      motor(constrain(speed - motorspeed, -255, 255), constrain(speed + motorspeed, -255, 255));
    }
  }
}
