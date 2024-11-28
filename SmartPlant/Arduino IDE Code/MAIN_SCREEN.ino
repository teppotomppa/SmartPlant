void mainScreen() {

  isMainScreen = true;
  carrier.display.setTextColor(ST77XX_WHITE);
  carrier.display.setTextSize(2);
  carrier.display.setCursor(35, 60);
  carrier.display.print("Moisture: ");

  // Update only the moisture percentage to avoid blinking the entire label
  carrier.display.setCursor(155, 60);
  carrier.display.fillRect(155, 60, 50, 20, ST77XX_BLACK);  // Clear the previous percentage value

  if (moisture > moistureLevel) {
    carrier.display.setTextColor(ST77XX_GREEN);
    carrier.display.print(moisture);
    carrier.display.print(" %");
  } else {
    carrier.display.setTextColor(ST77XX_RED);
    carrier.display.print(moisture);
    carrier.display.print(" %");
  }

  if (autoWatering) {
    carrier.display.setCursor(35, 105);
    carrier.display.setTextColor(ST77XX_WHITE);
    carrier.display.println("Automatic");
    carrier.display.setCursor(35, 125);
    carrier.display.print("Watering: ");
    carrier.display.setTextColor(ST77XX_GREEN);
    carrier.display.print("ON");
  }
  if (!autoWatering) {
    carrier.display.setCursor(35, 105);
    carrier.display.setTextColor(ST77XX_WHITE);
    carrier.display.println("Automatic");
    carrier.display.setCursor(35, 125);
    carrier.display.print("Watering: ");
    carrier.display.setTextColor(ST77XX_RED);
    carrier.display.print("OFF");
  }
}
