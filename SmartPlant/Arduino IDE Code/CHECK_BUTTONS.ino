void checkButtons() {
  carrier.Buttons.update();

  //Check if the idle timeout has passed
  if (!isMainScreen && millis() - lastInteractionTime > idleTimeout) {
    showMainScreen();
    return;  //Return to avoid processing further button checks
  }

  //Check for button 0 if on mainscreen
  if (isMainScreen && carrier.Buttons.onTouchDown(TOUCH0)) {  //BUTTON 0 ON MAINSCREEN
    carrier.Buzzer.beep(600, 200);
    buttonZeroScreen();
    lastInteractionTime = millis();  //Reset the timer
  }

  //Check for button 0 if on zeroscreen
  if (isZeroScreen && carrier.Buttons.onTouchDown(TOUCH0)) {  //BUTTON 0 ON ZEROSCREEN
    carrier.Buzzer.beep(600, 200);
    showMainScreen();
    lastInteractionTime = millis();  //Reset the timer
  }

  if (isFourScreen && carrier.Buttons.onTouchDown(TOUCH0)) {  //BUTTON 0 ON FOURSCREEN
    carrier.Buzzer.beep(600, 200);
    lastInteractionTime = millis();  //Reset the timer
  }


  //Check for button 1 on mainscreen
  if (isMainScreen && carrier.Buttons.onTouchDown(TOUCH1)) {  //BUTTON 1 ON MAINSCREEN
    carrier.Buzzer.beep(800, 200);
    lastInteractionTime = millis();  //Reset the timer
  }

  //Check for button 1 on zeroScreen
  if (isZeroScreen && carrier.Buttons.onTouchDown(TOUCH1)) {  //BUTTON 1 ON ZEROSCREEN
    carrier.Buzzer.beep(800, 200);

    moistureLevel -= 5;  // decrease moisture level by 5
    Serial.print("Moisture Level: ");
    Serial.println(moistureLevel);  // Debug: print moisture level to serial monitor

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
    carrier.display.print(moistureLevel);  // Display moisture level
    lastInteractionTime = millis();        //Reset the timer
  }

  //Check if in fourscreen, and press touch1 to turn off autowatering
  if (isFourScreen && carrier.Buttons.onTouchDown(TOUCH1)) {  //BUTTON 1 ON FOURSCREEN
    carrier.Buzzer.beep(800, 200);
    autoWatering = false;

    // Clear screen and display only Moisture Level
    carrier.display.fillScreen(ST77XX_BLACK);
    carrier.display.setTextColor(ST77XX_WHITE);
    carrier.display.setTextSize(2);

    // Display Moisture Level label
    carrier.display.setCursor(35, 80);
    carrier.display.println("Auto Watering:");

    // Display
    carrier.display.setCursor(100, 120);
    carrier.display.setTextColor(ST77XX_RED);
    carrier.display.print("OFF");
    lastInteractionTime = millis();  //Reset the timer
  }

  //Check for button 2 on main menu
  if (isMainScreen && carrier.Buttons.onTouchDown(TOUCH2)) {  //BUTTON 2 ON MAINSCREEN
    carrier.Buzzer.beep(1000, 200);
    manualWatering();
    Serial.println("Manual Watering Started");
    lastInteractionTime = millis();  //Reset the timer
  }

  //Check for button 2 while not on main menu
  if (!isMainScreen && carrier.Buttons.onTouchDown(TOUCH2)) {  //BUTTON 2 NOT ON MAINSCREEN
    carrier.Buzzer.beep(1000, 200);
    Serial.println("Not in main menu, cannot start manual watering.");
    lastInteractionTime = millis();  //Reset the timer
  }



  //Check for button 3 in main menu
  if (isMainScreen && carrier.Buttons.onTouchDown(TOUCH3)) {  //BUTTON 3 ON MAINSCREEN
    carrier.Buzzer.beep(1200, 200);
    lastInteractionTime = millis();  //Reset the timer
  }

  //Check for button 3 in zeroscreen
  if (isZeroScreen && carrier.Buttons.onTouchDown(TOUCH3)) {  //BUTTON 3 ON ZEROSCREEN
    carrier.Buzzer.beep(1200, 200);

    moistureLevel += 5;  // increase moisture level by 5
    Serial.print("Moisture Level: ");
    Serial.println(moistureLevel);  // Debug: print moisture level to serial monitor

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
    carrier.display.print(moistureLevel);  // Display moisture level
    lastInteractionTime = millis();        //Reset the timer
  }

  //Check if in fourscreen, and press touch3 to turn on autowatering
  if (isFourScreen && carrier.Buttons.onTouchDown(TOUCH3)) {  //BUTTON 3 ON FOURSCREEN
    carrier.Buzzer.beep(800, 200);
    autoWatering = true;

    // Clear screen and display only Moisture Level
    carrier.display.fillScreen(ST77XX_BLACK);
    carrier.display.setTextColor(ST77XX_WHITE);
    carrier.display.setTextSize(2);

    // Display Moisture Level label
    carrier.display.setCursor(35, 80);
    carrier.display.println("Auto Watering:");

    // Display
    carrier.display.setCursor(100, 120);
    carrier.display.setTextColor(ST77XX_GREEN);
    carrier.display.print("ON");
    lastInteractionTime = millis();  //Reset the timer
  }

  //Check for button 4 if on main screen
  if (isMainScreen && carrier.Buttons.onTouchDown(TOUCH4)) {  //BUTTON 4 ON MAINSCREEN
    carrier.Buzzer.beep(1400, 200);
    buttonFourScreen();
    lastInteractionTime = millis();  //Reset the timer
  }

  //Check for button 4 if on fourscreen
  if (isFourScreen && carrier.Buttons.onTouchDown(TOUCH4)) {  //BUTTON 4 ON FOURSCREEN
    carrier.Buzzer.beep(1400, 200);
    showMainScreen();
    lastInteractionTime = millis();  //Reset the timer
  }

  //Check for button 4 if on zeroScreen
  if (isZeroScreen && carrier.Buttons.onTouchDown(TOUCH4)) {  //BUTTON 4 ON ZEROSCREEN
    carrier.Buzzer.beep(1400, 200);
    lastInteractionTime = millis();  //Reset the timer
  }
}