// Define variables and pins for the Arduino
int echoPin = 8;   // Attach pin D8 to pin Echo of HC-SR04 for distance measurement
int trigPin = 7;    // Attach pin D7 to pin Trig of HC-SR04 for triggering the ultrasonic sensor
int in1 = 4;        // Variable names for the L298N motor driver
int in2 = 5;        // Variable names for the L298N motor driver
int in3 = 9;        // Variable names for the L298N motor driver
int in4 = 10;       // Variable names for the L298N motor driver

int LCDprev = 99;   // Variable to help update the LCD state; tracks previous state
int LCDcurr = 100;  // Variable to help update the LCD state; tracks current state

int ledpin = 13;    // Specify the LED pin to pin 13

long duration;      // Variable to store the duration of sound wave travel
int distance;       // Variable for distance measurement

void setup() {
  pinMode(trigPin, OUTPUT);   // Set sonar digital pin mode for trig
  pinMode(echoPin, INPUT);    // Set sonar digital pin mode for echo

  pinMode(in1, OUTPUT);       // Set L298N digital pins as outputs
  pinMode(in2, OUTPUT);       // Set L298N digital pins as outputs
  pinMode(in3, OUTPUT);       // Set L298N digital pins as outputs
  pinMode(in4, OUTPUT);       // Set L298N digital pins as outputs
  pinMode(ledpin, OUTPUT);    // Configure LED pin as an output

  Serial.begin(9600);         // Use the default of 9600 baud rate for serial communication
}

void loop() {
  // Clears the trigPin condition
  digitalWrite(trigPin, LOW);         // Starts trig pin low
  delayMicroseconds(2);                // Waits for hardware to respond
  digitalWrite(trigPin, HIGH);        // Makes trig pin high
  delayMicroseconds(10);               // Continues high trig pin state for 10 microseconds
  digitalWrite(trigPin, LOW);         // After 10 microseconds, trig pin is brought low
  duration = pulseIn(echoPin, HIGH);   // Reads echo as it receives the pulse and stores duration
  distance = duration * 0.034 / 2;     // Converts the time of flight to distance to object

  if (distance <= 15) {   
    digitalWrite(in1, HIGH);          // This block makes the robot move away from the object as it is at a distance of less than 15
    digitalWrite(in2, LOW);           // It makes it move backward.
    digitalWrite(in3, HIGH);          // It makes it move forward.
    digitalWrite(in4, LOW);           // It makes it move backward.
    digitalWrite(ledpin, HIGH);       // It makes it move forward.
  } 
  else if (distance <= 30) {
    digitalWrite(in1, LOW);            // This block makes the robot stop as there is an obstacle present between 15 and 30 cm.
    digitalWrite(in2, LOW);            // It makes it move backward.
    digitalWrite(in3, HIGH);           // It makes it move forward.
    digitalWrite(in4, HIGH);           // It makes it move forward.
    digitalWrite(ledpin, LOW);         // It makes it move backward.
  } 
  else if (distance <= 45) {
    digitalWrite(in1, HIGH);           // Makes the robot move forward as there is an obstacle present between 30 and 45 cm.
    digitalWrite(in2, LOW);            // It makes it move backward.
    digitalWrite(in3, LOW);            // It makes it move backward.
    digitalWrite(in4, HIGH);           // It makes it move forward.
    digitalWrite(ledpin, HIGH);        // It makes it move forward.
  } 
  else {
    digitalWrite(in1, LOW);            // This block makes the robot stop as there is no object present till 45 cm.
    digitalWrite(in2, LOW);            // It makes it move backward.
    digitalWrite(in3, HIGH);           // It makes it move forward.
    digitalWrite(in4, HIGH);           // It makes it move forward.
    digitalWrite(ledpin, LOW);         // It makes it move backward.
  }
}

