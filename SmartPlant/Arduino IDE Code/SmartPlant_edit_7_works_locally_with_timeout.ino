#include <Arduino_MKRIoTCarrier.h>
#include <Arduino.h>

MKRIoTCarrier carrier;

// Moisture Sensor Pin
int moistPin;

// Variables to hold moisture sensor readings
int moisture;

// Variable to hold the moisture threshold --> if the moisture goes under this threshold, the watering starts if automatic watering is on.
int moistureLevel = 50;

//Variable to hold the state of the mainScreen() --> The Main Menu of the device. Set to be true, since it should be the starting screen of the device.
bool isMainScreen = true;

//Variable to hold the state of the buttonZeroScreen() --> The interface after pressing TOUCH0 while on the Main Menu. From here, the user can change the moistureLevel (Threshold).
bool isZeroScreen = false;

//Variable to hold the state of the buttonFourScreen() --> The interface after pressing TOUCH4 while on the Main Menu. From here, the user can toggle between automatic watering to be on or off.
bool isFourScreen = false;

//Variable to hold the state of the automatic watering. By default, it is set to be true.
bool autoWatering = true;

//Variable to store the last interaction time
unsigned long lastInteractionTime = 0;

//5 Seconds timeout
const unsigned long idleTimeout = 5000;

// Define LED colors for lights on and off
uint32_t lightsOn = carrier.leds.Color(1, 1, 1);
uint32_t lightsOff = carrier.leds.Color(0, 0, 0);
uint32_t buttonLedGreen = carrier.leds.Color(0, 1, 0);  // Green color for button LEDs
uint32_t buttonLedRed = carrier.leds.Color(1, 0, 0);    // Red color for button LEDs
uint32_t buttonLedBlue = carrier.leds.Color(0, 0, 1);   // Blue color for manual watering



void setup() {

  // Initialize serial communication
  Serial.begin(9600);
  delay(1500);

  // Initialize the MKR IoT Carrier
  CARRIER_CASE = false;
  carrier.begin();
  moistPin = carrier.getBoardRevision() == 1 ? A5 : A0;  // Assign A0 or A5 based on HW revision
  carrier.display.setRotation(0);
  delay(1500);

  // Show the main screen on startup
  mainScreen();
}

void loop() {

  // Read raw moisture value
  int raw_moisture = analogRead(moistPin);

  // Map raw moisture to a scale of 0 - 100
  moisture = map(raw_moisture, 0, 1023, 100, 0);

  // Print sensor readings to the Serial Monitor for debugging
  Serial.print("Moisture: ");
  Serial.print(moisture);
  Serial.println(" %");

  // Display main screen if the flag is set
  if (isMainScreen) {
    mainScreen();
  }

  // Update LED color and relay state based on moisture level and autoWatering status
  if (autoWatering && isMainScreen) {
    if (moisture < moistureLevel) {
      carrier.leds.fill(buttonLedRed, 0, 5);  // Set LEDs to red if moisture is below threshold
      carrier.Relay2.open();
    } else {
      carrier.leds.fill(buttonLedGreen, 0, 5);  // Set LEDs to green if moisture is at or above threshold
      carrier.Relay2.close();
    }
  } else if (!autoWatering && isMainScreen) {
    carrier.leds.fill(buttonLedBlue, 0, 5);  // Indicate auto-watering is off
    carrier.Relay2.close();
  }

  carrier.leds.show();


  // Check for button presses
  checkButtons();

  delay(250);  // Short delay to prevent rapid loop execution
}
