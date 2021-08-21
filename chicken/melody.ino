#include "pitches.h"

void playMelodyTime0() {
  int noteDuration = 1000 / 4;
  tone(BUZZER_PIN, NOTE_C4, noteDuration);
  int pauseBetweenNotes = noteDuration * 1.30;
  delay(pauseBetweenNotes);
  noTone(BUZZER_PIN);
}
void playMelodyTime1() {
  int noteDuration = 1000 / 4;
  tone(BUZZER_PIN, NOTE_F4, noteDuration);
  int pauseBetweenNotes = noteDuration * 1.30;
  delay(pauseBetweenNotes);
  noTone(BUZZER_PIN);
}
void playMelodyTime2() {
  int noteDuration = 1000 / 4;
  tone(BUZZER_PIN, NOTE_B5, noteDuration);
  int pauseBetweenNotes = noteDuration * 1.30;
  delay(pauseBetweenNotes);
  noTone(BUZZER_PIN);
}


int numNotes1 = 8;
// notes in the melody:
int melody1[] = {
  NOTE_C4, NOTE_G3, NOTE_G3, NOTE_A3, NOTE_G3, 0, NOTE_B3, NOTE_C4
};
// note durations: 4 = quarter note, 8 = eighth note, etc.:
int noteDurations1[] = {
  4, 8, 8, 4, 4, 4, 4, 4
};
void playMelody1() {
  for (int thisNote = 0; thisNote < numNotes1; thisNote++) {
    int noteDuration = 1000 / noteDurations1[thisNote];
    tone(BUZZER_PIN, melody1[thisNote], noteDuration);
    // to distinguish the notes, set a minimum time between them.
    // the note's duration + 30% seems to work well:
    int pauseBetweenNotes = noteDuration * 1.30;
    delay(pauseBetweenNotes);
    // stop the tone playing:
    noTone(BUZZER_PIN);
  }
}
