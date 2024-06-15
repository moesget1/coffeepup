#include <CapacitiveSensor.h> // https://github.com/PaulStoffregen/CapacitiveSensor
#include <Servo.h> // Include the Servo library

// Parameters
bool autocal = 0;
const int numReadings = 10;
long readings[numReadings];
int readIndex = 0;
long total = 0;
const int sensitivity = 500;
const int thresh = 200;
const int csStep = 10000;
CapacitiveSensor cs = CapacitiveSensor(6, 7);

int ledgreen = 3;
Servo myservo; // Create servo object to control a servo
int servoPin = 9; // Pin where the servo is connected

/*// Variables for tap detection
const int thresholdValue = 100; // Threshold for smoothed value
int counter = 0; // Counter for detecting taps
const int counterLimit = 2; // Limit at which the servo moves
bool tapDetected = false; // State to keep track of tap detection*/

// Variables for tap detection
const int thresholdValue = 100; // Threshold for smoothed value
bool tapDetected = false; // State to keep track of tap detection

// Variables for detecting consecutive taps
unsigned long firstTapTime = 0;
const unsigned long tapTimeout = 500; // Time window for detecting the second tap (in milliseconds)
bool firstTapDetected = false;

// Variables for LED blinking
bool ledState = false; // Current state of the LED
unsigned long previousMillis = 0; // Last time the LED state was updated
const long interval = 1000; // Interval at which to blink (milliseconds)

// Variables for motor idle state
bool motorIdle = true;
unsigned long motorPreviousMillis = 0;
const long motorInterval = 2000; // Interval at which to move the motor (milliseconds)
int motorPosition = 0;
int motorDirection = 1; // 1 for forward, -1 for backward

void setup() {
  // Init Serial USB
  Serial.begin(9600);
  Serial.println(F("Initialize System"));

  // Init cs
  if (autocal == 0) {
    cs.set_CS_AutocaL_Millis(0xFFFFFFFF);
  }

  pinMode(ledgreen, OUTPUT);
  myservo.attach(servoPin); // Attach the servo to the pin
  myservo.write(0); // Set initial position to 0 degrees
}

void loop() {
  long smoothedValue = smooth();
  Serial.println(smoothedValue);

  unsigned long currentTime = millis();

  unsigned long currentMillis = millis();

  // Blink the LED at the beginning until the motor starts
  if (!firstTapDetected) {
    if (currentMillis - previousMillis >= interval) {
      // Save the last time the LED state was updated
      previousMillis = currentMillis;
      
      // If the LED is off, turn it on, and vice-versa
      ledState = !ledState;
      digitalWrite(ledgreen, ledState);
    }

    
  }


  /*if (smoothedValue > thresholdValue) {
    start
    }*/

  // Check if the smoothed value exceeds the threshold
  if (smoothedValue > thresholdValue) {
    if (!tapDetected) {
      // If it's the first tap
      if (!firstTapDetected) {
        firstTapDetected = true;
        firstTapTime = currentTime;
        Serial.println("First tap detected");
        //digitalWrite(ledgreen, HIGH);
      }
      // If it's the second tap within the time window
      else if (currentTime - firstTapTime <= tapTimeout) {
        Serial.println("Second tap detected - Starting motor");
        startMotor();
        firstTapDetected = false; // Reset tap detection
      }
      tapDetected = true; // Mark that a tap has been detected
    }
  } else {
    tapDetected = false; // Reset tap detection state
    //digitalWrite(ledgreen, LOW);
  }

  // Reset the first tap detection if the time window has passed
  if (firstTapDetected && (currentTime - firstTapTime > tapTimeout)) {
    firstTapDetected = false;
    Serial.println("First tap timeout - Resetting tap detection");
  }

  // Check for serial command from the computer
  if (Serial.available() > 0) {
    char receivedChar = Serial.read();
    if (receivedChar == 's') {
      Serial.println("keypressed");
      startMotor();
    }
  }


  /*long smoothedValue = smooth();
  Serial.println(smoothedValue);

  // Check if the smoothed value exceeds the threshold
  if (smoothedValue > thresholdValue) {
    if (!tapDetected) {
      counter++;
      Serial.print("Counter: ");
      Serial.println(counter);
      tapDetected = true; // Mark that a tap has been detected

      // Turn on LED to indicate detection
      digitalWrite(ledgreen, HIGH);
    }
  } else {
    tapDetected = false; // Reset tap detection state
    digitalWrite(ledgreen, LOW);
  }

  // Check if the counter has reached the limit
  if (counter >= counterLimit) {
    // Move the servo back and forth
    Serial.println("PLAY_SOUND");
    myservo.write(45); // Turn the servo to 180 degrees
    delay(200); // Wait for 1 second
    myservo.write(0); // Return the servo to 0 degrees
    delay(200); // Wait for 1 second
    myservo.write(45); // Turn the servo to 180 degrees
    delay(200); // Wait for 1 second
    myservo.write(0); // Return the servo to 0 degrees
    delay(200); // Wait for 1 second
    myservo.write(45); // Turn the servo to 180 degrees
    delay(200); // Wait for 1 second
    myservo.write(0); // Return the servo to 0 degrees
    delay(200); // Wait for 1 second
    myservo.write(45); // Turn the servo to 180 degrees
    delay(200); // Wait for 1 second
    myservo.write(0); // Return the servo to 0 degrees
    delay(200); // Wait for 1 second

    // Reset the counter after the servo movement
    counter = 0;
  }

  delay(50);*/
}

long smooth() {
  // Perform average on sensor readings
  long average;

  // Subtract the last reading:
  total = total - readings[readIndex];

  // Read the sensor:
  readings[readIndex] = cs.capacitiveSensor(sensitivity);

  // Add value to total:
  total = total + readings[readIndex];

  // Handle index
  readIndex = readIndex + 1;
  if (readIndex >= numReadings) {
    readIndex = 0;
  }

  // Calculate the average:
  average = total / numReadings;

  return average;
}


void startMotor(){
  // Move the servo back and forth
    Serial.println("PLAY_SOUND");
    myservo.write(45); // Turn the servo to 180 degrees
    delay(200); // Wait for 1 second
    myservo.write(0); // Return the servo to 0 degrees
    delay(200); // Wait for 1 second
    myservo.write(45); // Turn the servo to 180 degrees
    delay(200); // Wait for 1 second
    myservo.write(0); // Return the servo to 0 degrees
    delay(200); // Wait for 1 second
    myservo.write(45); // Turn the servo to 180 degrees
    delay(200); // Wait for 1 second
    myservo.write(0); // Return the servo to 0 degrees
    delay(200); // Wait for 1 second
    myservo.write(45); // Turn the servo to 180 degrees
    delay(200); // Wait for 1 second
    myservo.write(0); // Return the servo to 0 degrees
    delay(200); // Wait for 1 second
  }
