void buttonFourScreen() {

  isMainScreen = false;
  isZeroScreen = false;
  isFourScreen = true;
  autoWatering = true;

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
  carrier.display.println("Auto Watering:");

  // Display
  carrier.display.setCursor(70, 120);
  carrier.display.setTextColor(ST77XX_RED);
  carrier.display.print("OFF");
  carrier.display.setTextColor(ST77XX_WHITE);
  carrier.display.print(" / ");
  carrier.display.setTextColor(ST77XX_GREEN);
  carrier.display.print("ON");
  lastInteractionTime = millis();  //Reset the timer
}
