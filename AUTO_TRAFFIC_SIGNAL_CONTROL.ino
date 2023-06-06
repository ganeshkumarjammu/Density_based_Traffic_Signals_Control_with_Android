#include <SoftwareSerial.h>

// Define IR sensor pins
const int sensor1APin = 42;  // IR sensor 1, side A
const int sensor1BPin = 43;  // IR sensor 2, side A
const int sensor2APin = 44;  // IR sensor 1, side B
const int sensor2BPin = 45;  // IR sensor 2, side B
const int sensor3APin = 50;  // IR sensor 1, side C
const int sensor3BPin = 51;  // IR sensor 2, side C
const int sensor4APin = 52;  // IR sensor 1, side D
const int sensor4BPin = 53;  // IR sensor 2, side D

// Define LED pins
const int greenLED1Pin = 22;   // Green LED for side A
const int yellowLED1Pin = 23;  // Yellow LED for side A
const int redLED1Pin = 24;     // Red LED for side A

const int greenLED2Pin = 26;   // Green LED for side B
const int yellowLED2Pin = 27;  // Yellow LED for side B
const int redLED2Pin = 28;     // Red LED for side B

const int greenLED3Pin = 30;   // Green LED for side C
const int yellowLED3Pin = 31;  // Yellow LED for side C
const int redLED3Pin = 32;     // Red LED for side C

const int greenLED4Pin = 34;   // Green LED for side D
const int yellowLED4Pin = 35;  // Yellow LED for side D
const int redLED4Pin = 36;     // Red LED for side D

// Define threshold values
const int densityThreshold = 1; // Density threshold to determine traffic density

// Define Bluetooth communication pins
const int bluetoothTxPin = 0;  // Bluetooth TX pin
const int bluetoothRxPin = 1;  // Bluetooth RX pin

SoftwareSerial BT(bluetoothRxPin, bluetoothTxPin);  // Create a software serial port for Bluetooth communication

bool isAutomaticMode = true;  // Flag to indicate if the system is in automatic mode
int normalDelay = 2000;
int yellowDelay = 500;
int redDelay = 500;
int count = 1;

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
  BT.begin(9600);
}

void loop() {
  Serial.println("Traffic Control System");
  String command = "";
  delay(10);
  if (BT.available())
  {
    //Check if there is an available byte to read
    Serial.println("BT Available - Command");
    delay(10);                              //Delay added to make thing stable
    //char command[] = "";
    char c = BT.read();                     //Conduct a serial read
    command += c;                           //build the string.
    Serial.println(command);
  }

  else if (command == "1")
  {
    Serial.println("Executing 1 command");
    // Side A traffic lights
    Serial.println("Side A Green");
    greenA(1000);
  }
  else if (command == "2")
  {
    // Side B traffic lights
    Serial.println("Side B Green");
    greenB(1000);
  }
  else if (command == "3")
  {
    // Side C traffic lights
    Serial.println("Side C Green");
    greenC(1000);
  }
  else if ( command == "4")
  {
    Serial.println("Side D Green");
    greenD(1000);
  }
  else if (command == "5")
  {
    Serial.println("Lights OFF");
    turnOffAllLights();
  }
  else if (command == "6")
  {
    Serial.println("Automatic Mode Changed");
    isAutomaticMode != isAutomaticMode;
  }
//  else if(1){    
//    Serial.println("Lights OFF");
//    turnOffAllLights();
//    }
  else if(isAutomaticMode) {
    // Automatic mode, read sensor values and adjust traffic lights accordingly
    int sensor1AValue = !digitalRead(sensor1APin);
    int sensor1BValue = !digitalRead(sensor1BPin);
    int densitySideA = sensor1AValue + sensor1BValue;
    if (densitySideA >= densityThreshold) {
      Serial.println(" Traffic at Side A ");
      Serial.print("Density: ");
      Serial.println(densitySideA);
      // High density, stop traffic
      greenA(densitySideA * 1000);
    }
    else {
      Serial.println("No Traffic at Side A");
      Serial.print("Density: ");
      Serial.println(densitySideA);
    }

    int sensor2AValue = !digitalRead(sensor2APin);
    int sensor2BValue = !digitalRead(sensor2BPin);
    int densitySideB = sensor2AValue + sensor2BValue;
    if (densitySideB >= densityThreshold) {
      Serial.println(" Traffic at Side B ");
      Serial.print("Density: ");
      Serial.println(densitySideB);
      greenB(densitySideB * 1000);
    }
    else {
      Serial.println("No Traffic at Side B");
      Serial.print("Density: ");
      Serial.println(densitySideB);
    }

    int sensor3AValue = !digitalRead(sensor3APin);
    int sensor3BValue = !digitalRead(sensor3BPin);
    int densitySideC = sensor3AValue + sensor3BValue;
    if (densitySideC >= densityThreshold) {
      Serial.println(" Traffic at Side C ");
      Serial.print("Density: ");
      Serial.println(densitySideC);
      // High density, stop traffic
      greenC(densitySideC * 1000);
    }
    else {
      Serial.println("No Traffic at Side C");
      Serial.print("Density: ");
      Serial.println(densitySideC);
    }

    int sensor4AValue = !digitalRead(sensor4APin);
    int sensor4BValue = !digitalRead(sensor4BPin);
    int densitySideD = sensor4AValue + sensor4BValue;

    if (densitySideD >= densityThreshold) {
      Serial.println(" Traffic at Side D");
      Serial.print("Density: ");
      Serial.println(densitySideD);
      greenD(densitySideD * 1000);
    }
    else {
      Serial.println("No Traffic at Side D");
      Serial.print("Density: ");
      Serial.println(densitySideD);
    }
    if (count == 1) {
      greenA(1000);
      count++;
    }
    else if (count == 2) {
      greenB(1000);
      count++;
    }
    else if (count == 3) {
      greenC(1000);
      count++;
    }
    else if (count == 4) {
      greenD(1000);
      count = 1;
    }
  }
  else{
    Serial.println("Lights OFF");
    turnOffAllLights();
  }

}


void greenA(int wait) {
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
  delay(wait);
  digitalWrite(greenLED1Pin, LOW);
  digitalWrite(yellowLED1Pin, HIGH);
  delay(yellowDelay);
  digitalWrite(yellowLED1Pin, LOW);
  digitalWrite(redLED1Pin, HIGH);
  delay(redDelay);
}

void greenB(int wait) {
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
  delay(wait);
  digitalWrite(greenLED2Pin, LOW);
  digitalWrite(yellowLED2Pin, HIGH);
  delay(yellowDelay);
  digitalWrite(yellowLED2Pin, LOW);
  digitalWrite(redLED2Pin, HIGH);
  delay(redDelay);
}
void greenC(int wait) {
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
  delay(wait);
  digitalWrite(greenLED3Pin, LOW);
  digitalWrite(yellowLED3Pin, HIGH);
  delay(yellowDelay);
  digitalWrite(yellowLED3Pin, LOW);
  digitalWrite(redLED3Pin, HIGH);
  delay(redDelay);
}
void greenD(int wait) {
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
  delay(wait);
  digitalWrite(greenLED4Pin, LOW);
  digitalWrite(yellowLED4Pin, HIGH);
  delay(yellowDelay);
  digitalWrite(yellowLED4Pin, LOW);
  digitalWrite(redLED4Pin, HIGH);
  delay(redDelay);
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
  delay(1000);
}
