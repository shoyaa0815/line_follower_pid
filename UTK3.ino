float error, alpha = 0.07;  // Current line position error and sensor smoothing factor
int last_error = 0, diff = 0, motorspeed, integrel;  // PID control variables
float lastalpha[6] = {0, 0, 0, 0, 0, 0};  // Previous sensor readings for filtering
float smin[6] = {1023, 1023, 1023, 1023, 1023, 1023};  // Minimum sensor values (black line)
float smax[6] = {0, 0, 0, 0, 0, 0};  // Maximum sensor values (white surface)
#define smid 300  // Calibration threshold
void setup()
{
  Serial.begin(9600);
  pinMode(5, OUTPUT);   // Right motor pin 1
  pinMode(6, OUTPUT);   // Right motor pin 2
  pinMode(9, OUTPUT);   // Left motor pin 1
  pinMode(10, OUTPUT);  // Left motor pin 2
  pinMode(13, OUTPUT);  // LED indicator
  pinMode(7, INPUT);    // Start button
  
  pinMode(A0, INPUT);   // IR sensor 0
  pinMode(A1, INPUT);   // IR sensor 1
  pinMode(A2, INPUT);   // IR sensor 2
  pinMode(A3, INPUT);   // IR sensor 3
  pinMode(A4, INPUT);   // IR sensor 4
  pinMode(A5, INPUT);   // IR sensor 5

  // test_rawSensor();

  for (int i = 0; i < 5; i++)
  {
    calibrateOnBlack();  // Place robot on black line and move it around
    calibrateOnWhite();  // Place robot on white surface and move it around
  }
  digitalWrite(13, HIGH);
}

void loop()
{
  while (digitalRead(7) == 0)
    ;
  // do something here  
  track();
  // do something here
}
