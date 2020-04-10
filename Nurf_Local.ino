#include "ServoTimer2.h"

char *msg;
byte a = 0;
int randNumber;
String rawCode;

//Mechanical Component Variables
int triggerPin = 8;
int tranSignal = 12;
ServoTimer2 trigger;

// Servo pulling trigger Mechanism
void pullTrigger() {
  trigger.write(500);
  delay(500);
  trigger.write(1500);
}

bool  russianRoulette() {
  Serial.println("");
  Serial.println("Initializing Russian Roulette, Good Luck!");
  Serial.println("Loading Results...");
  Serial.println("");

  delay(3000);

  randNumber = random(1, 11);
  if (randNumber > 9) {
    return true;
  }
  else {
    return false;
  }
}

void rainFire() {
  digitalWrite(tranSignal, HIGH);
  delay(250);
  for (int i = 0; i < 10; i++){
    pullTrigger();
    delay(500);
  }
  delay(250);
  digitalWrite(tranSignal, LOW);
}

// This function turns the strings into actions
void translate(String raw) {
  if (raw == "48") {
    digitalWrite(tranSignal, LOW);
    Serial.println("Motor OFF");
  }
  else if (raw == "49") {
    digitalWrite(tranSignal, HIGH);
    Serial.println("Motor ON");
  }
  else if (raw == "50") {
    pullTrigger();
  }
  else if (raw == "51") {
    rainFire();
  }
  else {
    return;
  }
}

void setup()
{
  randomSeed(analogRead(0));
  
  //Begin Serial Monitor
  Serial.begin(9600);

  //Begin Mechanical Components
  pinMode(tranSignal, OUTPUT);
  trigger.attach(triggerPin);
  trigger.write(1500);
}

void loop()
{
  while (Serial.available() == 0) {}
  a = Serial.read();

  switch (a) {
    case 48:
      msg = "48";
      break;

    case 49:
      msg = "49";
      break;

    case 50:
      msg = "50";
      break;

    case 51:
      msg = "51";
      Serial.println("");
      Serial.println("Rain of Fire");
      Serial.println("Take Cover...");
      Serial.println("");
      break;

    case 52:
      bool rouletteResults = russianRoulette();
      if (rouletteResults == true) {
        msg = "50";
        Serial.println("Uh Oh.. .");
        delay(1000);
      }
      else {
        msg = "48";
        Serial.println("You pass, till next time ;)");
      }
      break;
  }
  
  translate(msg);
}
