#include <Servo.h>   //載入函式庫，這是內建的，不用安裝

Servo myservo;

const int BUZZER_PIN = 13;
const int LIGHT_SENSOR_PIN = A2;
const int BUTTON_1_PIN = 7;
const int BUTTON_2_PIN = 8;
const int MOTOR_PIN = 3;
const int R_PIN = 9;
const int G_PIN = 10;
const int B_PIN = 11;

int button1State = 0;
int button1StateLast = 0;
int button2State = 0;
int button2StateLast = 0;
int lightValue = 0;
int lightState = LOW;
int lightStateLast = LOW;
const int LightThreshold = 550;

const int InitState = 1;
const int ReadyState = 2;
const int LockState = 3;
const int LockOpenedState = 4;
const int FinishState = 5;
int state = InitState;

bool isCounting = false;
unsigned long beginTime = 0;
unsigned long pauseBeginTime = 0;

unsigned long TIMES[] = {5000, 15000, 30000}; // sec, simulate 1mon, 2mon, 3mon)
int selectedTimeIndex = 0;
unsigned long selectedTime = TIMES[selectedTimeIndex];

void showColor(int red, int green, int blue) {
  analogWrite(R_PIN, red);
  analogWrite(G_PIN, green);
  analogWrite(B_PIN, blue);
}

void setup() {
  Serial.begin(9600);
//  while (!Serial);
  pinMode(BUZZER_PIN,OUTPUT);
  pinMode(BUTTON_1_PIN,INPUT);
  pinMode(BUTTON_2_PIN,INPUT);
  pinMode(LIGHT_SENSOR_PIN,INPUT);
  pinMode(R_PIN, OUTPUT);
  pinMode(G_PIN, OUTPUT);
  pinMode(B_PIN, OUTPUT);
  myservo.attach(MOTOR_PIN);
  myservo.write(35);
  // init values
  button1State = digitalRead(BUTTON_1_PIN);
  button2State = digitalRead(BUTTON_2_PIN);
  button1StateLast = button1State;
  button2StateLast = button2State;
  showColor(0, 255, 0);
  Serial.println("Chicken start!!!!");
}

void processInitState() {
  // **init state**
  // init start select time
  // cont read 2 button
  // default 1month
  button1State = digitalRead(BUTTON_1_PIN);
  button2State = digitalRead(BUTTON_2_PIN);
  if (button1State != button1StateLast) {
    if (button1State == HIGH) {
      Serial.println("Toggle time");
      // if read button 1, switch between times
      if (selectedTimeIndex >= 2) selectedTimeIndex = 0;
      else ++selectedTimeIndex;
      selectedTime = TIMES[selectedTimeIndex];
      // buzz
      Serial.println("buzz1 change time");
      Serial.print("interval: ");
      Serial.println(selectedTime);
      // 3 type of buzz based on selected time
      switch(selectedTimeIndex) {
        case 0:
          showColor(0, 255, 0);
          playMelodyTime0();
          break;
        case 1:
          showColor(0, 0, 255);
          playMelodyTime1();
          break;
        case 2:
          showColor(255, 0, 0);
          playMelodyTime2();
          break;
      }
    }
    button1StateLast = button1State;
  }

  if (button2State != button2StateLast) {
    if (button2State == HIGH) {
      Serial.println("Go to ReadyState");
      // else if read button 2, start count down (into **ready state**)
      state = ReadyState;
      // buzz2
      playMelodyRestart();
      Serial.println("buzz2 count down config set");
      // servo close egg;
      myservo.write(120);

      // default value
      lightValue = analogRead(LIGHT_SENSOR_PIN);
      lightState = lightValue > LightThreshold;
      lightStateLast = lightState;
    }
    button2StateLast = button2State;
  }
}

void processReadyState() {
  // cont read light sensor
  //  lightValue = analogRead(LIGHT_SENSOR_PIN);
  lightValue = lightValue * 0.7 + analogRead(LIGHT_SENSOR_PIN) * 0.3;
  //Serial.println(lightValue);
  lightState = lightValue > LightThreshold;
  
  if (lightState != lightStateLast) {
    // if from light to dark
    
    if (lightState == LOW) {
    // buzz3
      playMelodyFinish();
      Serial.println("buzz3 user close box");
    //   trans to **lock state** 
      Serial.println("Go to LockState");
      state = LockState;
      // start counting
      isCounting = true;
      beginTime = millis();
      Serial.println("Start counting");
      Serial.print("interval: ");
      Serial.println(selectedTime);
      Serial.print("beginTime: ");
      Serial.println(beginTime);
    }
    lightStateLast = lightState;
  }
}

void processLockState() {
//  lightValue = analogRead(LIGHT_SENSOR_PIN);
  lightValue = lightValue * 0.7 + analogRead(LIGHT_SENSOR_PIN) * 0.3;
  lightState = lightValue > LightThreshold;
  
  if (lightState != lightStateLast) {
    // if get light and in closing state
    if (lightState == HIGH) {
      Serial.println("buzz4 user want to take out things");
      //   buzz4 user want to take out things
      playMelodyFate();
      //   go to **middle state**
      Serial.println("Go to LockOpenedState");
      state = LockOpenedState;
      pauseBeginTime = millis();
      isCounting = false;
    }
    lightStateLast = lightState;
  } 
}

void processLockOpenedState() {
//  lightValue = analogRead(LIGHT_SENSOR_PIN);
  lightValue = lightValue * 0.7 + analogRead(LIGHT_SENSOR_PIN) * 0.3;
  lightState = lightValue > LightThreshold;
  
  if (lightState != lightStateLast) {
    // if get dark again
    if (lightState == LOW) {
      //   buzz5 close again
      Serial.println("buzz5 close again");
      playMelodyMario();
      //   ??go to **Lock state**
      Serial.println("Go to LockState");
      state = LockState;
      beginTime += millis() - pauseBeginTime;
      isCounting = true;
    }
    lightStateLast = lightState;
  }  
}

void timeIsUp() {
  // if time out
  //   beeeeeeep
  playMelodyStop();
  //   go to **timeout state**
  Serial.println("Go to FinishState");
  state = FinishState;
  isCounting = false;
  
}

void processFinishState() {
//  lightValue = analogRead(LIGHT_SENSOR_PIN);
  lightValue = lightValue * 0.7 + analogRead(LIGHT_SENSOR_PIN) * 0.3;
  lightState = lightValue > LightThreshold;
  
  if (lightState != lightStateLast) {
    // if light after timeout
    if (lightState == HIGH) {
      //   buzz6 welcome to throw
      Serial.println("buzz6 welcome to throw");
      playMelodyElize();
      //   servo open egg
      myservo.write(35);
      //   goto first step, choose time
      Serial.println("Go to InitState");
      state = InitState;
      
    }
    lightStateLast = lightState;
  }
}


void loop() {
  // state logics
  if (state == InitState) {
    processInitState();
  } else if (state == ReadyState) {
    processReadyState();
  } else if (state == LockState) {
    processLockState();
  } else if (state == LockOpenedState) {
    processLockOpenedState();
  } else if (state == FinishState) {
    processFinishState();
  }

  // counting timeout logics
  if (isCounting) {
    if (millis() - beginTime > selectedTime) {
      Serial.println("Time IS UP");
      timeIsUp();
    }
  }

  
  delay(100);
}
