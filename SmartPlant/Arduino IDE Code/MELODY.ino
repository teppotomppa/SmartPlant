// Define note frequencies in Hz
#define NOTE_C5 523
#define NOTE_E5 659
#define NOTE_G5 784
#define NOTE_C6 1047
#define NOTE_G4 392



// Play the melody (note, duration)
void playMelody() {
  carrier.Buzzer.beep(NOTE_C5, 200);
  carrier.Buzzer.beep(NOTE_E5, 200);
  carrier.Buzzer.beep(NOTE_G5, 200);
  carrier.Buzzer.beep(NOTE_C6, 100);
  delay(350);
  carrier.Buzzer.beep(NOTE_G5, 200);
  carrier.Buzzer.beep(NOTE_C6, 900);
}