#include <Servo.h>

Servo sampayan;
int servoPin = 9;

// INPUT
int modeTrigger = 2;
int toggleSampayan = 6;

int rainSensor = A0;
int lightSensor = A1;

// OUTPUT
int buzzerNotify = 3;
int autoLED = 4;  //GREEN
int manLED = 5;   // BLUE

// STATES
int isAuto = true;
bool isHidden = true;
int pos = -90;

void setup() {
  Serial.begin(9600);

  pinMode(modeTrigger, INPUT);
  pinMode(toggleSampayan, INPUT);

  pinMode(buzzerNotify, OUTPUT);
  pinMode(autoLED, OUTPUT);
  pinMode(manLED, OUTPUT);

  sampayan.attach(servoPin);
  sampayan.write(pos);
}

void loop() {

  // onclick rotate
  if (!isAuto && digitalRead(toggleSampayan)) {
    //change position
    isHidden = toggleServo(isHidden);
    pos = changePosition(isHidden, pos);
    digitalWrite(buzzerNotify, HIGH);
    delay(500);
    digitalWrite(buzzerNotify, LOW);
    sampayan.write(pos);
  }


  // Mode Changed Handler
  if (digitalRead(modeTrigger)) {
    isAuto = !isAuto;
    digitalWrite(buzzerNotify, HIGH);
    delay(500);
    digitalWrite(buzzerNotify, LOW);
  }

  // Function Handling
  if (isAuto) {
    // Serial.println("auto");
    digitalWrite(autoLED, HIGH);
    digitalWrite(manLED, LOW);
    Serial.println(analogRead(lightSensor));
    if (analogRead(rainSensor) >= 1015 && analogRead(lightSensor) <= 150) {
      pos = 90;
    } else {
      pos = -90;
    }
    sampayan.write(pos);
  } else {
    // Serial.println("manual");
    digitalWrite(autoLED, LOW);
    digitalWrite(manLED, HIGH);
  }
}

int changePosition(bool isHidden, int pos) {
  if (isHidden && pos != 0) {
    return -90;
  }

  if (!isHidden && pos != 90) {
    return 90;
  }

  return pos;
}

bool toggleServo(bool isHidden) {
  return !isHidden;
}
