#define BUTTON_PIN 0

boolean buttonPressed = false;
boolean ledLightOn = false;

int counter = 0;

void setup() {
  Serial.begin(9600);

  pinMode(BUTTON_PIN, INPUT);
  pinMode(LED_BUILTIN, OUTPUT);
}

void loop() {

  // light up led
  lightLED();

  // check if button pressed
  if (digitalRead(BUTTON_PIN) == LOW && !buttonPressed)
  {
    // pressed
    Serial.println("button pressed!");

    buttonPressed = true;
    ledLightOn = true;
  }

  if (digitalRead(BUTTON_PIN) == HIGH && buttonPressed)
  {
    // release
    Serial.println("button released!");

    buttonPressed = false;
    ledLightOn = false;
  }

  delay(30);
}

void lightLED()
{
  counter = (counter + 1) % 10;

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
}

