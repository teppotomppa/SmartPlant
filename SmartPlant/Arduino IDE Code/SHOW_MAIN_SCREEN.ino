void showMainScreen() {
  isMainScreen = true;
  carrier.display.fillScreen(ST77XX_BLACK);  // Clear the screen before showing the main menu
  mainScreen();
  lastInteractionTime = millis();  //Reset the timer
}