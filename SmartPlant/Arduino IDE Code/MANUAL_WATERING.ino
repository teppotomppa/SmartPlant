void manualWatering() {
  // Start manual watering: turn on relay, blink blue LEDs, and show text at the same time
  carrier.Relay2.open();
  carrier.display.fillScreen(ST77XX_BLACK);
  carrier.display.setTextColor(ST77XX_WHITE);
  carrier.display.setTextSize(2);
  carrier.display.setCursor(82, 60);
  carrier.display.println("Manual");
  carrier.display.setCursor(75, 80);
  carrier.display.println("Watering");
  carrier.display.setCursor(84, 100);

  for (int i = 0; i < 5; i++) {

    // Blink blue LEDs
    carrier.leds.fill(buttonLedBlue, 0, 5);
    carrier.leds.show();
    delay(500);
    carrier.leds.fill(lightsOff, 0, 5);
    carrier.leds.show();
    // Update loading dots without refreshing the entire screen
    carrier.display.print(".");
    delay(500);
  }
  carrier.Relay2.close();

  // Watering complete text in the center of the screen
  carrier.display.fillScreen(ST77XX_BLACK);
  carrier.display.setTextColor(ST77XX_WHITE);
  carrier.display.setTextSize(2);
  carrier.display.setCursor(65, 75);
  carrier.display.println("Watering");
  carrier.display.setCursor(62, 100);
  carrier.display.println("Successful!");
  playMelody();
  delay(1500);
  carrier.display.fillScreen(ST77XX_BLACK);

  // Return LEDs to normal state
  if (moisture < moistureLevel) {
    carrier.leds.fill(buttonLedRed, 0, 5);  // Set LEDs to red if moisture is below 50
    carrier.Relay2.open();
  } else {
    carrier.leds.fill(buttonLedGreen, 0, 5);  // Set LEDs to green if moisture is 50 or above
    carrier.Relay2.close();
  }
  carrier.leds.show();

  isMainScreen = true;  //DONT CHANGE THIS

  isZeroScreen = false;

  // Update screen back to normal
  mainScreen();
}
