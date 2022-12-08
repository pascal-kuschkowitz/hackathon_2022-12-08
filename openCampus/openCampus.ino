# include "time.h"


int box_pin         = 8; // Box connected to digital pin 8
int interrupt_pin   = 2; // Box connected to interrupt pin 2
int box_total       = 0;
int new_box_total   = 0;

// unsigned long time = millis();
unsigned long time_delta;


void setup() {
  // Init serial communication at 9600 bits/s
  Serial.begin(9600);
  //pinMode(box_pin, INPUT);
  pinMode(interrupt_pin, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(interrupt_pin), increse_pin, RISING);
}

void loop() {
  unsigned long time = millis();
  delay(1);

  // Only get value every second
  if (time % 1000 == 0) {
      // Only get value if value is < than 0
      if (box_total > 0) {
        Serial.println(box_total);
        box_total = 0;
      }
  }

  // Set new_box_total to the old total
  new_box_total = box_total;
}


void increse_pin() {
  box_total++;
}
