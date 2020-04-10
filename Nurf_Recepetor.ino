#include "ServoTimer2.h"

#include <VirtualWire.h>

// Radio Wave Module Variables
const int dataPin = 7;
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
int translate(String raw) {
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
  //Begin Serial Monitor
  Serial.begin(9600);

  //Begin Mechanical Components
  pinMode(tranSignal, OUTPUT);
  trigger.attach(triggerPin);
  trigger.write(1500);

  //Begin Radio Wave Components
  vw_setup(2000);
  vw_set_rx_pin(dataPin);
  vw_rx_start();
}

void loop()
{
  uint8_t buf[VW_MAX_MESSAGE_LEN];
  uint8_t buflen = VW_MAX_MESSAGE_LEN;

  // Checks if it has recieved anything.
  //If it has, it runs the code bellow.
  if (vw_get_message(buf, &buflen))
  {
    rawCode = "";
    for (int i = 0; i < buflen; i++)
    {
      //The Virtual Wire module sends the message in
      //chuncks. Here we are combining them into a
      //single string.
      rawCode += (char)buf[i];
    }
    translate(rawCode);
  }
}
