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
  tone(BUZZER_PIN, NOTE_G5, noteDuration);
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
  4, 8, 8, 4, 4
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

int numNotesMario = 16;
int melodyMario[] = {
  NOTE_E7, NOTE_E7, 0, NOTE_E7,
  0, NOTE_C7, NOTE_E7, 0,
  NOTE_G7, 0, 0, 0,
  NOTE_G6, 0, 0, 0,
};
int noteDurationsMario[] = {
  12, 12, 12, 12,
  12, 12, 12, 12,
  12, 12, 12, 12,
  12, 12, 12, 12,
};
void playMelodyMario() {
  for (int thisNote = 0; thisNote < numNotesMario; thisNote++) {
    int noteDuration = 1000 / noteDurationsMario[thisNote];
    tone(BUZZER_PIN, melodyMario[thisNote], noteDuration);
    int pauseBetweenNotes = noteDuration * 1.30;
    delay(pauseBetweenNotes);
    noTone(BUZZER_PIN);
  }
}


int numNotesElize = 17;
int melodyElize[] = {
  NOTE_E5, NOTE_DS5,  //1
  NOTE_E5, NOTE_DS5,  NOTE_E5, NOTE_B4, NOTE_D5, NOTE_C5,
  NOTE_A4, NOTE_C4,  NOTE_E4, NOTE_A4,
  NOTE_B4, NOTE_E4,  NOTE_GS4,  NOTE_B4,
  NOTE_C5
};
int noteDurationsElize[] = {
  8,8,
  8,8,8,8,8,8,
  4,8,8,8,
  4,8,8,8,
  4
};
void playMelodyElize() {
  for (int thisNote = 0; thisNote < numNotesElize; thisNote++) {
    int noteDuration = 1000 / noteDurationsElize[thisNote];
    tone(BUZZER_PIN, melodyElize[thisNote], noteDuration);
    int pauseBetweenNotes = noteDuration * 1.30;
    delay(pauseBetweenNotes);
    noTone(BUZZER_PIN);
  }
}

int numNotesFate = 4;
int melodyFate[] = {
  NOTE_E5, NOTE_E5, NOTE_E5, NOTE_C5
};
int noteDurationsFate[] = {
  8,8,8,2
};
void playMelodyFate() {
  for (int thisNote = 0; thisNote < numNotesFate; thisNote++) {
    int noteDuration = 1000 / noteDurationsFate[thisNote];
    tone(BUZZER_PIN, melodyFate[thisNote], noteDuration);
    int pauseBetweenNotes = noteDuration * 1.30;
    delay(pauseBetweenNotes);
    noTone(BUZZER_PIN);
  }
}
