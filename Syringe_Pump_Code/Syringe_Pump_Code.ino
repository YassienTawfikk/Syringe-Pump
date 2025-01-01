#include <Wire.h>
#include <LiquidCrystal_I2C.h>  // Library for I2C LCD
#include <OneWire.h>
#include <DallasTemperature.h> // Library for DS18B20 temperature sensor

#define STEP_PIN 3       // Step pin connected to driver STEP
#define DIR_PIN 2        // Direction pin connected to driver DIR
#define ENABLE_PIN 4     // Enable pin connected to driver EN
#define LED_PIN 5        // LED connected to D5
#define FLOW_SENSOR_PIN 6 // Flow sensor signal connected to D6
#define ONE_WIRE_BUS 7   // DS18B20 data pin connected to pin 7 on Arduino

const int stepsPerRevolution = 200; // Steps for one full rotation (1.8° step motor)
int rotations = 50;                 // Global variable: number of rotations
volatile int flowPulseCount = 0;    // Counter for the number of pulses from the flow sensor
float flowRate = 0.0;               // Flow rate in mL/min
unsigned long lastFlowTime = 0;     // Timestamp for flow rate calculation
bool isMotorRunning = false;        // Tracks whether the motor is running

// Calibration factor (pulses per liter)
const float calibrationFactor = 7.5 * 22;

// Initialize the LCD (Address: 0x27, 16 columns and 2 rows)
LiquidCrystal_I2C lcd(0x27, 16, 2);

// Temperature Sensor Setup
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);

void setup() {
  // Set up pins
  pinMode(STEP_PIN, OUTPUT);
  pinMode(DIR_PIN, OUTPUT);
  pinMode(ENABLE_PIN, OUTPUT);
  pinMode(LED_PIN, OUTPUT);
  pinMode(FLOW_SENSOR_PIN, INPUT_PULLUP); // Set the flow sensor pin as input with pull-up

  // Initialize motor and LED states
  digitalWrite(ENABLE_PIN, LOW);  // Enable motor driver
  digitalWrite(LED_PIN, LOW);     // Turn off LED

  // Initialize LCD
  lcd.init();        // Initialize the LCD
  lcd.backlight();   // Turn on the backlight
  lcd.setCursor(0, 0);
  lcd.print("Initializing...");
  delay(2000);       // Display message for 2 seconds

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Ready to Start");

  // Initialize Serial Monitor
  Serial.begin(9600);

  // Initialize Temperature Sensor
  sensors.begin();
}

void loop() {
  // Calculate flow rate
  calculateFlowRate();

  // Update LCD display when motor is idle
  if (!isMotorRunning) {
    float temperature = getTemperature();
    updateLCD(temperature);
  }

  // Start motor operation
  performRotations(rotations);
}

void performRotations(int numRotations) {
  int steps = numRotations * stepsPerRevolution;  // Total steps for the given rotations

  digitalWrite(DIR_PIN, LOW); // Set direction (anti-clockwise)
  Serial.print("Performing ");
  Serial.print(numRotations);
  Serial.println(" rotations.");

  isMotorRunning = true; // Motor is now running

  for (int i = 0; i < steps; i++) {
    float temperature = getTemperature();

    // Check for high temperature and pause motor if necessary
    if (temperature > 38) {
      pauseMotor();
      isMotorRunning = false;
      return; // Exit motor operation
    }

    digitalWrite(STEP_PIN, HIGH);
    delayMicroseconds(2000);  // Adjust speed
    digitalWrite(STEP_PIN, LOW);
    delayMicroseconds(2000);
  }

  isMotorRunning = false; // Motor is no longer running
}

void pauseMotor() {
  // Disable the motor and alert user
  digitalWrite(ENABLE_PIN, HIGH);  // Disable motor driver
  digitalWrite(LED_PIN, HIGH);     // Turn on warning LED

  // Display a warning message on the LCD
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Motor Paused");
  lcd.setCursor(0, 1);
  lcd.print("High Temp!");

  Serial.println("Motor paused due to high temperature.");
  delay(5000); // Wait for 5 seconds before rechecking
}

void calculateFlowRate() {
  // Calculate flow rate every second
  unsigned long currentTime = millis();

  if (currentTime - lastFlowTime >= 1000) {
    // Calculate flow rate in mL/min
    flowRate = (flowPulseCount / calibrationFactor);
    lastFlowTime = currentTime;

    // Reset the pulse count for the next calculation
    flowPulseCount = 0;

    // Debugging: Print flow rate to Serial Monitor
    Serial.print("Flow Rate: ");
    Serial.print(flowRate);
    Serial.println(" mL/min");
  }
}

float getTemperature() {
  sensors.requestTemperatures();  // Request temperature from the sensor
  float temp = sensors.getTempCByIndex(0);

  // Handle disconnected sensor
  if (temp == DEVICE_DISCONNECTED_C) {
    Serial.println("Error: Sensor not connected!");
    return -999;  // Return an invalid value to indicate error
  }

  Serial.print("Temperature: ");
  Serial.println(temp);
  return temp;
}

void updateLCD(float temperature) {
  lcd.clear(); // Clear the screen to prevent overlap

  // First line: Display temperature
  lcd.setCursor(0, 0);
  if (temperature == -999) {
    lcd.print("Temp Error!");
  } else {
    lcd.print("Temp: ");
    lcd.print(temperature, 1); // Display temperature with 1 decimal place
    lcd.print(" C");
  }

  // Second line: Real-time flow rate
  lcd.setCursor(0, 1);
  lcd.print("Rate: ");
  lcd.print(flowRate, 1); // Display flow rate with 1 decimal point
  lcd.print(" mL/min");
}
