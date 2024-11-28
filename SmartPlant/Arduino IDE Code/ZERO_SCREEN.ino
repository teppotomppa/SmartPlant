void buttonZeroScreen() {

  isMainScreen = false;
  isFourScreen = false;
  isZeroScreen = true;

  // Reset LED colors (not necessary for moisture level functionality)
  for (int i = 0; i < 5; i++) {
    carrier.leds.setPixelColor(i, carrier.leds.Color(0, 0, 0));
  }

  carrier.leds.setPixelColor(1, carrier.leds.Color(1, 0, 0));
  carrier.leds.show();

  carrier.leds.setPixelColor(3, carrier.leds.Color(0, 1, 0));
  carrier.leds.show();

  // Clear screen and display only Moisture Level
  carrier.display.fillScreen(ST77XX_BLACK);
  carrier.display.setTextColor(ST77XX_WHITE);
  carrier.display.setTextSize(2);

  // Display Moisture Level label
  carrier.display.setCursor(35, 80);
  carrier.display.println("Moisture Level:");

  // Display current moisture level (initial value 50)
  carrier.display.setCursor(100, 120);
  carrier.display.setTextColor(ST77XX_GREEN);
  carrier.display.print(moistureLevel);  // Display initial moisture level
  lastInteractionTime = millis();        //Reset the timer
}
