
// INPUT
int modeTrigger = 2;

// OUTPUT
int buzzerNotify = 3;
int autoLED = 4;  //GREEN
int manLED = 5;   // BLUE

// STATES
int isAuto = false;

void setup() {
  Serial.begin(9600);

  pinMode(modeTrigger, INPUT);

  pinMode(buzzerNotify, OUTPUT);
  pinMode(autoLED, OUTPUT);
  pinMode(manLED, OUTPUT);
}

void loop() {
  delay(500);
  
  // Mode Changed Handler
  if (digitalRead(modeTrigger)) {
    isAuto = !isAuto;
    Serial.println("button pressed");
    digitalWrite(buzzerNotify, HIGH);
    delay(500);
    digitalWrite(buzzerNotify, LOW);
  }

  // Function Handling
  if (isAuto) {
    Serial.println("auto");
    digitalWrite(autoLED, HIGH);
    digitalWrite(manLED, LOW);

  } else {
    Serial.println("manual");
    digitalWrite(autoLED, LOW);
    digitalWrite(manLED, HIGH);
  }
}
