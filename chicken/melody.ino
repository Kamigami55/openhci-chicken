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


int numNotesStop = 9;
int melodyStop[] = {
  NOTE_C5, NOTE_C5, 0, NOTE_C5, NOTE_C5, 0, NOTE_C5, NOTE_C5, 0
};
int noteDurationsStop[] = {
  4, 4, 4, 4, 4, 4, 4, 4, 4
};
void playMelodyStop() {
  for (int thisNote = 0; thisNote < numNotesStop; thisNote++) {
    int noteDuration = 1000 / noteDurationsStop[thisNote];
    tone(BUZZER_PIN, melodyStop[thisNote], noteDuration);
    int pauseBetweenNotes = noteDuration * 1.30;
    delay(pauseBetweenNotes);
    noTone(BUZZER_PIN);
  }
}

int numNotesFinish = 8;
// notes in the melody:
int melodyFinish[] = {
  NOTE_C4, NOTE_G3, NOTE_G3, NOTE_A3, NOTE_G3, 0, NOTE_B3, NOTE_C4
};
// note durations: 4 = quarter note, 8 = eighth note, etc.:
int noteDurationsFinish[] = {
  4, 8, 8, 4, 4, 4, 4, 4
};
void playMelodyFinish() {
  for (int thisNote = 0; thisNote < numNotesFinish; thisNote++) {
    int noteDuration = 1000 / noteDurationsFinish[thisNote];
    tone(BUZZER_PIN, melodyFinish[thisNote], noteDuration);
    // to distinguish the notes, set a minimum time between them.
    // the note's duration + 30% seems to work well:
    int pauseBetweenNotes = noteDuration * 1.30;
    delay(pauseBetweenNotes);
    // stop the tone playing:
    noTone(BUZZER_PIN);
  }
}

int numNotesRestart = 5;
int melodyRestart[] = {
  NOTE_C4, NOTE_G3, NOTE_A3, NOTE_B3, NOTE_C4
};
int noteDurationsRestart[] = {
  4, 2, 2, 4, 4
};
void playMelodyRestart() {
  for (int thisNote = 0; thisNote < numNotesRestart; thisNote++) {
    int noteDuration = 1000 / noteDurationsRestart[thisNote];
    tone(BUZZER_PIN, melodyRestart[thisNote], noteDuration);
    int pauseBetweenNotes = noteDuration * 1.30;
    delay(pauseBetweenNotes);
    noTone(BUZZER_PIN);
  }
}
