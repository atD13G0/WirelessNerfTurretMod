#include <VirtualWire.h>

const int dataPin = 9;
const int ledPin = 13;
char *msg;
byte a = 0;
int randNumber;

bool  russianRoulette() {
  Serial.println("");
  Serial.println("Initializing Russian Roulette, Good Luck!");
  Serial.println("Loading Results...");
  Serial.println("");

  delay(3000);

  randNumber = random(1, 11);
  if (randNumber > 6) {
    return true;
  }
  else {
    return false;
  }
}


void setup()
{
  Serial.begin(9600);
  vw_setup(2000);
  vw_set_tx_pin(dataPin);

  randomSeed(analogRead(0));
}

void loop()
{
  while (Serial.available() == 0) {}
  a = Serial.read();

  switch (a) {
    case 48:
      msg = "48";
      Serial.println("Motor OFF");
      break;

    case 49:
      msg = "49";
      Serial.println("Motor ON");
      break;

    case 50:
      msg = "50";
      Serial.println("Trigger Pulled");
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

  digitalWrite(ledPin, true);
  vw_send((uint8_t *)msg, strlen(msg));
  vw_wait_tx();
  digitalWrite(ledPin, false);
  delay(200);
}
