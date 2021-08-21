//#include <Servo.h>   //載入函式庫，這是內建的，不用安裝

//Servo myservo;

int sensorValue = 0;  // variable to store the value coming from the sensor
//#define LIGHT_SENSOR_PIN A2;
//const int BUZZER_PIN = 2;
const int LIGHT_SENSOR_PIN = A2;
const int BUTTON_1_PIN = 2;
const int BUTTON_2_PIN = 13;
const int LIGHT_SENSOR_PIN = 12;
//const int BUTTON_2_PIN = 13;
//#define MOTOR_PIN D12;

int button1State = 0;
int button1StateLast = 0;
int button2State = 0;
int button2StateLast = 0;
int lightValue = 0;
int lightState = LOW;
int lightStateLast = LOW;
const int LightThreshold = 800;

const int InitState = 1;
const int ReadyState = 2;
const int LockState = 3;
const int LockOpenedState = 4;
const int FinishState = 5;
int state = InitState;

bool isCounting = false;
int beginTime = 0;

const int TIMES = [5000, 15000, 30000]; // sec, simulate 1mon, 2mon, 3mon)
int selectedTimeIndex = 0;
int selectedTime = TIMES[selectedTimeIndex];

void setup() {
  Serial.begin(9600);
  Serial.print("Chicken start!!!!");
  //pinMode(BUZZER_PIN,OUTPUT);
  pinMode(BUTTON_1_PIN,INPUT);
  pinMode(BUTTON_2_PIN,INPUT);
  //pinMode(LIGHT_SENSOR_PIN,INPUT);
  //myservo.attach(MOTOR_PIN)
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
        Serial.print("Toggle time");
        // if read button 1, switch between times
        if (selectedTimeIndex >= 2) selectedTimeIndex = 0;
        else ++selectedTimeIndex;
        selectedTime = TIMES[selectedTimeIndex];
        // buzz
        // TODO
      }
      button1StateLast = button1State;
    }
  
    if (button2State != button2StateLast) {
      if (button1State == HIGH) {
        Serial.print("Go to counting state");
        // else if read button 2, start count down (into **ready state**)
        state = ReadyState;
        // TODO counting
        // buzz2
        // TODO
      }
      button2StateLast = button2State;
    }
}

void processReadyState() {
  // cont read light sensor
  
  lightValue = analogRead(LIGHT_SENSOR_PIN);
  lightState = lightValue > LightThreshold;
  
  if (lightState != lightStateLast) {
    // if from light to dark
    
    if (lightState == LOW) {
    //   TODO buzz3
    //   trans to **lock state**  
      state = LockState;
      // start counting
      isCounting = true;
      beginTIme = millis();
    }
    lightStateLast = lightState;
  }
}

void processLockState() {
  lightValue = analogRead(LIGHT_SENSOR_PIN);
  lightState = lightValue > LightThreshold;
  
  if (lightState != lightStateLast) {
    // if get light and in closing state
    if (lightState == HIGH) {
      //   buzz4 user want to take out things
      //   ??go to **middle state**
      state = LockOpenedState;
    }
    lightStateLast = lightState;
  } 
}

void processLockOpenedState() {
  lightValue = analogRead(LIGHT_SENSOR_PIN);
  lightState = lightValue > LightThreshold;
  
  if (lightState != lightStateLast) {
    // if get dark again
    if (lightState == LOW) {
      //   buzz5 close again
      //   ??go to **Lock state**
      state = LockState;
    }
    lightStateLast = lightState;
  }  
}

void timeIsUp() {
  // if time out
  //   beeeeeeep TODO
  //   servo open egg TODO
  //   go to **timeout state**
  state = FinishState;
  isCounting = false;
}

void processFinishState() {
  lightValue = analogRead(LIGHT_SENSOR_PIN);
  lightState = lightValue > LightThreshold;
  
  if (lightState != lightStateLast) {
    // if light after timeout
    if (lightState == HIGH) {
      //   buzz6 welcome to throw TODO
      //   goto first step, choose time
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
      timeIsUp();
    }
  }

  
  
  //myservo.write(180);
  // read the value from the sensor:
  //sensorValue = analogRead(LIGHT_SENSOR_PIN);
  //sensorValue = digitalRead(BUTTON_1_PIN);
  // turn the ledPin on
  
  //delay(500);

  // stop the program for <sensorValue> milliseconds:
  //delay(sensorValue);
  // turn the ledPin off:
  //digitalWrite(ledPin, LOW);
  // stop the program for for <sensorValue> milliseconds:
  //delay(sensorValue);
}
