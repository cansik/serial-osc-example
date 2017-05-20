import oscP5.*;
import processing.serial.*;

Serial serial;
OscSerial osc;
String serialName = "/dev/cu.usbmodem14411";

boolean buttonState = false;

void setup()
{
  size(500, 300, FX2D);

  serial = new Serial(this, serialName, 9600);
  serial.clear();

  osc = new OscSerial(this, serial);
  osc.plug(this, "buttonEvent", "/button");
}

void draw()
{
  if (buttonState)
    background(226, 106, 106);
  else
    background(89, 171, 227);

  textAlign(CENTER, CENTER);
  textSize(20);
  text("BUTTON " + (buttonState ? "PRESSED" : "RELEASED") + "!", width / 2, height / 2);
}

void buttonEvent(int value) {
  buttonState = value == 1;

  // send command to light up led!
  //sendLEDState();
}

void sendLEDState()
{
  OscMessage msg = new OscMessage("/led");
  msg.add(buttonState ? 1 : 0);
  osc.send(msg);
}

void oscEvent(OscMessage theMessage) {
  println("Message: " + theMessage + ", " + theMessage.isPlugged());
}

void mousePressed()
{
  // press
  buttonState = true;
  sendLEDState();
}

void mouseReleased()
{
  // release
  buttonState = false;
  sendLEDState();
}