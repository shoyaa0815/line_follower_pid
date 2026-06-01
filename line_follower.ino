#define sensor_midpoint 300
#define base_speed 200
#define target_position 30 
#define white_threshold 2.5

#define KP 15
#define KD 25
#define KI 30000

float error = 0;
int last_error = 0;
int motor_speed_offset = 0;
int integral = 0;

float alpha = 0.07;
float last_filtered_value[6] = {0, 0, 0, 0, 0, 0};
float sensor_min[6] = {1023, 1023, 1023, 1023, 1023, 1023};
float sensor_max[6] = {0, 0, 0, 0, 0, 0};
int line_detect_level = 2;

void setup()
{
  Serial.begin(9600);
  
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(10, OUTPUT);
  
  pinMode(9, INPUT);
  
  pinMode(A0, INPUT);
  pinMode(A1, INPUT);
  pinMode(A2, INPUT);
  pinMode(A3, INPUT);
  pinMode(A4, INPUT);
  pinMode(A5, INPUT);

  for (int i = 0; i < 5; i++)
  {
    calibrateBlack();
    calibrateWhite();
  }  
}

void loop()
{
  while (digitalRead(9) == 1);   
  track_line();
}