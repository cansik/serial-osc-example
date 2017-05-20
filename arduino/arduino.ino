#include <OscSerial.h>

#define BUTTON_PIN 2
#define LED_PIN 13

boolean buttonPressed = false;
boolean ledLightOn = false;

OscSerial oscSerial;

int counter = 0;

void setup() {
  Serial.begin(9600);

  pinMode(BUTTON_PIN, INPUT);
  digitalWrite(BUTTON_PIN, HIGH);

  //pinMode(LED_PIN, OUTPUT);

  oscSerial.begin(Serial);
}

void loop() {
  // light up led
  lightLED();

  // check if button pressed
  int btnValue = digitalRead(BUTTON_PIN);
  if (btnValue == LOW && !buttonPressed)
  {
    // pressed
    //Serial.println("button pressed!");
    //sendButtonState();
    buttonPressed = true;
    sendButtonState();
  }

  if (btnValue == HIGH && buttonPressed)
  {
    // release
    //Serial.println("button released!");
    buttonPressed = false;
    sendButtonState();
  }

  oscSerial.listen();
}

void sendButtonState()
{
  OscMessage msg("/button");
  msg.add(buttonPressed ? 1 : 0);
  oscSerial.send(msg);
}

void lightLED()
{
  counter = (counter + 1) % 10;

  if (ledLightOn)
  {
    digitalWrite(LED_PIN, HIGH);
  }
  else
  {
    digitalWrite(LED_PIN, LOW);
  }

  /*
    if (ledLightOn && counter < 5)
    {
    digitalWrite(LED_BUILTIN, HIGH);
    }
    else if (ledLightOn && counter >= 5)
    {
    digitalWrite(LED_BUILTIN, LOW);
    }
    else
    {
    digitalWrite(LED_BUILTIN, LOW);
    }
  */
}

void oscEvent(OscMessage &m) {
  // receive a message
  m.plug("/led", setLEDState);
}

void setLEDState(OscMessage &m) {
  // getting to the message data
  int value = m.getInt(0);
  ledLightOn = value == 1;
}

