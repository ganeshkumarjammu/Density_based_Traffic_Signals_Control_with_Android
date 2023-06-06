#include <SoftwareSerial.h>

// Define IR sensor pins
const int sensor1APin = 2;  // IR sensor 1, side A
const int sensor1BPin = 3;  // IR sensor 2, side A
const int sensor2APin = 4;  // IR sensor 1, side B
const int sensor2BPin = 5;  // IR sensor 2, side B
const int sensor3APin = 6;  // IR sensor 1, side C
const int sensor3BPin = 7;  // IR sensor 2, side C
const int sensor4APin = 8;  // IR sensor 1, side D
const int sensor4BPin = 9;  // IR sensor 2, side D

// Define LED pins
const int greenLED1Pin = 10;   // Green LED for side A
const int yellowLED1Pin = 11;  // Yellow LED for side A
const int redLED1Pin = 12;     // Red LED for side A

const int greenLED2Pin = 14;   // Green LED for side B
const int yellowLED2Pin = 15;  // Yellow LED for side B
const int redLED2Pin = 16;     // Red LED for side B

const int greenLED3Pin = 17;   // Green LED for side C
const int yellowLED3Pin = 18;  // Yellow LED for side C
const int redLED3Pin = 19;     // Red LED for side C

const int greenLED4Pin = 22;   // Green LED for side D
const int yellowLED4Pin = 24;  // Yellow LED for side D
const int redLED4Pin = 26;     // Red LED for side D

// Define threshold values
const int densityThreshold = 1; // Density threshold to determine traffic density

// Define Bluetooth communication pins
const int bluetoothTxPin = 22;  // Bluetooth TX pin
const int bluetoothRxPin = 23;  // Bluetooth RX pin

SoftwareSerial bluetoothSerial(bluetoothRxPin, bluetoothTxPin);  // Create a software serial port for Bluetooth communication

bool isAutomaticMode = true;  // Flag to indicate if the system is in automatic mode
int normalDelay = 1000;
int yellowDelay = 500;

void setup() {
  // Initialize sensor pins as input
  pinMode(sensor1APin, INPUT);
  pinMode(sensor1BPin, INPUT);
  pinMode(sensor2APin, INPUT);
  pinMode(sensor2BPin, INPUT);
  pinMode(sensor3APin, INPUT);
  pinMode(sensor3BPin, INPUT);
  pinMode(sensor4APin, INPUT);
  pinMode(sensor4BPin, INPUT);

  // Initialize LED pins as output
  pinMode(greenLED1Pin, OUTPUT);
  pinMode(yellowLED1Pin, OUTPUT);
  pinMode(redLED1Pin, OUTPUT);
  pinMode(greenLED2Pin, OUTPUT);
  pinMode(yellowLED2Pin, OUTPUT);
  pinMode(redLED2Pin, OUTPUT);
  pinMode(greenLED3Pin, OUTPUT);
  pinMode(yellowLED3Pin, OUTPUT);
  pinMode(redLED3Pin, OUTPUT);
  pinMode(greenLED4Pin, OUTPUT);
  pinMode(yellowLED4Pin, OUTPUT);
  pinMode(redLED4Pin, OUTPUT);

  Serial.begin(9600);
  // Initialize Bluetooth serial communication
  bluetoothSerial.begin(9600);
}

void loop() {
  Serial.println("Traffic Control System");
  if (isAutomaticMode) {
    // Automatic mode, read sensor values and adjust traffic lights accordingly
    int sensor1AValue = !digitalRead(sensor1APin);
    int sensor1BValue = !digitalRead(sensor1BPin);
    int sensor2AValue = !digitalRead(sensor2APin);
    int sensor2BValue = !digitalRead(sensor2BPin);
    int sensor3AValue = !digitalRead(sensor3APin);
    int sensor3BValue = !digitalRead(sensor3BPin);
    int sensor4AValue = !digitalRead(sensor4APin);
    int sensor4BValue = !digitalRead(sensor4BPin);

    // Calculate density for each side
    int densitySideA = sensor1AValue + sensor1BValue;
    int densitySideB = sensor2AValue + sensor2BValue;
    int densitySideC = sensor3AValue + sensor3BValue;
    int densitySideD = sensor4AValue + sensor4BValue;

    // Adjust traffic lights based on density for each side
    controlTrafficLights(densitySideA, greenLED1Pin, yellowLED1Pin, redLED1Pin);
    controlTrafficLights(densitySideB, greenLED2Pin, yellowLED2Pin, redLED2Pin);
    controlTrafficLights(densitySideC, greenLED3Pin, yellowLED3Pin, redLED3Pin);
    controlTrafficLights(densitySideD, greenLED4Pin, yellowLED4Pin, redLED4Pin);
  } 
  if(1) {
    // Manual mode, control lights based on Bluetooth commands
    while (bluetoothSerial.available()) {
      char command = bluetoothSerial.read();

      switch (command) {
        case 'A':
          // Side A traffic lights
          digitalWrite(greenLED1Pin, HIGH);
          digitalWrite(yellowLED1Pin, LOW);
          digitalWrite(redLED1Pin, LOW);
          digitalWrite(greenLED2Pin, LOW);
          digitalWrite(yellowLED2Pin, LOW);
          digitalWrite(redLED2Pin, HIGH);
          digitalWrite(greenLED3Pin, LOW);
          digitalWrite(yellowLED3Pin, LOW);
          digitalWrite(redLED3Pin, HIGH);
          digitalWrite(greenLED4Pin, LOW);
          digitalWrite(yellowLED4Pin, LOW);
          digitalWrite(redLED4Pin, HIGH);
          delay(1000);
          digitalWrite(greenLED1Pin, LOW);
          digitalWrite(yellowLED1Pin, HIGH);
          delay(yellowDelay);
          digitalWrite(yellowLED1Pin, LOW);
          digitalWrite(redLED1Pin, HIGH);
          break;

        case 'B':
          // Side B traffic lights
          digitalWrite(greenLED1Pin, LOW);
          digitalWrite(yellowLED1Pin, LOW);
          digitalWrite(redLED1Pin, HIGH);
          digitalWrite(greenLED2Pin, HIGH);
          digitalWrite(yellowLED2Pin, LOW);
          digitalWrite(redLED2Pin, LOW);
          digitalWrite(greenLED3Pin, LOW);
          digitalWrite(yellowLED3Pin, LOW);
          digitalWrite(redLED3Pin, HIGH);
          digitalWrite(greenLED4Pin, LOW);
          digitalWrite(yellowLED4Pin, LOW);
          digitalWrite(redLED4Pin, HIGH);
          delay(1000);
          digitalWrite(greenLED2Pin, LOW);
          digitalWrite(yellowLED2Pin, HIGH);
          delay(yellowDelay);
          digitalWrite(yellowLED2Pin, LOW);
          digitalWrite(redLED2Pin, HIGH);
          break;

        case 'C':
          // Side C traffic lights
          digitalWrite(greenLED1Pin, LOW);
          digitalWrite(yellowLED1Pin, LOW);
          digitalWrite(redLED1Pin, HIGH);
          digitalWrite(greenLED2Pin, LOW);
          digitalWrite(yellowLED2Pin, LOW);
          digitalWrite(redLED2Pin, HIGH);
          digitalWrite(greenLED3Pin, HIGH);
          digitalWrite(yellowLED3Pin, LOW);
          digitalWrite(redLED3Pin, LOW);
          digitalWrite(greenLED4Pin, LOW);
          digitalWrite(yellowLED4Pin, LOW);
          digitalWrite(redLED4Pin, HIGH);
          delay(1000);
          digitalWrite(greenLED3Pin, LOW);
          digitalWrite(yellowLED3Pin, HIGH);
          delay(yellowDelay);
          digitalWrite(yellowLED3Pin, LOW);
          digitalWrite(redLED3Pin, HIGH);
          break;

        case 'D':
          // Side D traffic lights
          digitalWrite(greenLED1Pin, LOW);
          digitalWrite(yellowLED1Pin, LOW);
          digitalWrite(redLED1Pin, HIGH);
          digitalWrite(greenLED2Pin, LOW);
          digitalWrite(yellowLED2Pin, LOW);
          digitalWrite(redLED2Pin, HIGH);
          digitalWrite(greenLED3Pin, LOW);
          digitalWrite(yellowLED3Pin, LOW);
          digitalWrite(redLED3Pin, HIGH);
          digitalWrite(greenLED4Pin, HIGH);
          digitalWrite(yellowLED4Pin, LOW);
          digitalWrite(redLED4Pin, LOW);
          delay(1000);
          digitalWrite(greenLED4Pin, LOW);
          digitalWrite(yellowLED4Pin, HIGH);
          delay(yellowDelay);
          digitalWrite(yellowLED4Pin, LOW);
          digitalWrite(redLED4Pin, HIGH);
          break;

        case 'E':
          isAutomaticMode != isAutomaticMode;
          break ;
           
        default:
          // Invalid command, turn off all lights
          //turnOffAllLights();
          break;
      }
    }
  }
}

void controlTrafficLights(int density, int greenPin, int yellowPin, int redPin) {
  if (density >= densityThreshold) {
    Serial.print("Heavy Traffic at:");
    Serial.println(((greenPin-10)/3)+1);
    Serial.print("Density: ");
    Serial.println(density);
    // High density, stop traffic
    digitalWrite(greenPin, LOW);
    digitalWrite(yellowPin, LOW);
    digitalWrite(redPin, HIGH);
    delay(density*1000);
  } else {

    Serial.print("Low Traffic at:");
    Serial.println(((greenPin-10)/3)+1);
    Serial.print("Density:");
    Serial.println(density);
    // Low density, allow traffic
    digitalWrite(greenPin, HIGH);
    digitalWrite(yellowPin, LOW);
    digitalWrite(redPin, LOW);
    delay(1000);
  }
}

void turnOffAllLights() {
  digitalWrite(greenLED1Pin, LOW);
  digitalWrite(yellowLED1Pin, LOW);
  digitalWrite(redLED1Pin, LOW);
  digitalWrite(greenLED2Pin, LOW);
  digitalWrite(yellowLED2Pin, LOW);
  digitalWrite(redLED2Pin, LOW);
  digitalWrite(greenLED3Pin, LOW);
  digitalWrite(yellowLED3Pin, LOW);
  digitalWrite(redLED3Pin, LOW);
  digitalWrite(greenLED4Pin, LOW);
  digitalWrite(yellowLED4Pin, LOW);
  digitalWrite(redLED4Pin, LOW);
}
