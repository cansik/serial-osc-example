#define BUTTON_PIN 0

boolean buttonPressed = false;

void setup() {
  Serial.begin(9600);

  pinMode(BUTTON_PIN, INPUT);
}

void loop() {

  // check if button pressed
  if (digitalRead(BUTTON_PIN) == LOW && !buttonPressed)
  {
    // pressed
    Serial.println("button pressed!");

    buttonPressed = true;
  }

  if (digitalRead(BUTTON_PIN) == HIGH && buttonPressed)
  {
    // release
    Serial.println("button released!");

    buttonPressed = false;
  }

  delay(30);
}
