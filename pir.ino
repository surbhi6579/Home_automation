//pir

//#define timeSeconds 10
//
//// Set GPIOs for LED and PIR Motion Sensor
//const int led = 26;
//const int motionSensor = 27;
//
//// Timer: Auxiliary variables
//unsigned long now = millis();
//unsigned long lastTrigger = 0;
//boolean startTimer = false;
//
//// Checks if motion was detected, sets LED HIGH and starts a timer
//void IRAM_ATTR detectsMovement() {
//  Serial.println("MOTION DETECTED!!!");
//  digitalWrite(led, HIGH);
//  startTimer = true;
//  lastTrigger = millis();
//}
//
//void setup() {
//  // Serial port for debugging purposes
//  Serial.begin(115200);
//  
//  // PIR Motion Sensor mode INPUT_PULLUP
//  pinMode(motionSensor, INPUT_PULLUP);
//  // Set motionSensor pin as interrupt, assign interrupt function and set RISING mode
//  attachInterrupt(digitalPinToInterrupt(motionSensor), detectsMovement, RISING);
//
//  // Set LED to LOW
//  pinMode(led, OUTPUT);
//  digitalWrite(led, LOW);
//}
//
//void loop() {
//  // Current time
//  now = millis();
//  // Turn off the LED after the number of seconds defined in the timeSeconds variable
//  if(startTimer && (now - lastTrigger > (timeSeconds*1000))) {
//    Serial.println("Motion stopped...");
//    digitalWrite(led, LOW);
//    startTimer = false;
//  }
//}

int in1 = 12;
int sensor = 27;
int led = 26;
unsigned long t=0;

void setup() 
{
  Serial.begin(9600);
  pinMode(in1, OUTPUT);
  pinMode(sensor, INPUT);
  pinMode(led, OUTPUT);
  
  digitalWrite(in1,HIGH);
  digitalWrite(led,LOW);

  while(millis()<13000)
  {
    digitalWrite(led,HIGH);
    delay(50);
    digitalWrite(led,LOW);
    delay(50);
  }
  digitalWrite(led,LOW);
  
}


void loop() 
{
  digitalWrite(in1,HIGH);
  digitalWrite(led,LOW);
  if(digitalRead(sensor)==HIGH)
  {
   t=millis();
   while(millis()<(t+5000))
   {
   digitalWrite(in1,LOW);
   digitalWrite(led,HIGH);
     if((millis()>(t+2300))&&(digitalRead(sensor)==HIGH))
      {
       t=millis();
      }
   }
  }
}
