#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_ADXL345_U.h>
#include <BleMouse.h>

BleMouse bleMouse;

Adafruit_ADXL345_Unified accel = Adafruit_ADXL345_Unified(12345);

void setup() {
  Serial.begin(115200);

  pinMode(15, INPUT_PULLUP);
  pinMode(4, INPUT_PULLUP);
  pinMode(23, INPUT_PULLUP);
  
  bleMouse.begin();

  if(!accel.begin()) {
    Serial.println("No ADXL345 Module Detected!");
    while(1);
  }
  
  accel.setRange(ADXL345_RANGE_2_G);
}

void loop() {
  sensors_event_t event;
  accel.getEvent(&event);

  int yAxis = event.acceleration.y - (event.acceleration.y*2);
  int xAxis = event.acceleration.x;
/*
  if (bleMouse.isConnected()) {
    bleMouse.move(yAxis, xAxis);
    delay(10);
  }
*/
  if (digitalRead(15) == LOW) {
    bleMouse.press(MOUSE_LEFT);
  } else {
    bleMouse.release(MOUSE_LEFT);
  }

  if (digitalRead(4) == LOW) {
    bleMouse.press(MOUSE_RIGHT);
  } else {
    bleMouse.release(MOUSE_RIGHT);
  }
  
  if (digitalRead(23) == LOW) {
    bleMouse.move(0, 0, -xAxis, yAxis);
    delay(10);
  } else {
    bleMouse.move(yAxis, xAxis);
    delay(10);
  }
}
