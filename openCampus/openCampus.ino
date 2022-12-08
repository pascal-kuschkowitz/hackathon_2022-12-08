#include <WiFi.h>
#include <HTTPClient.h>

// The HTTP-Client
HTTPClient http;

// starts wifi
void setupWifi(const char* ssid,const char *password, const char *host) {
  // Connect to Wi-Fi network with SSID and password
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  //
  http.begin(host);
}

int sendData(int timestamp, int value) {
  String payload = "time="+String(timestamp)+"&value="+String(value);
  //const String payload_request = "time=1670500909\r\nvalue=7";  //Combine the name and value
  http.addHeader("Content-Type", "application/x-www-form-urlencoded");
  int response_code = http.sendRequest("POST", payload);
  return response_code;
}

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
  const char *ssid = "starterkitchen.de";
  const char *password = "starterkitchen2012";  
  const char *host = "https://wehkamp.de/energyhackathon22/data.php";
  setupWifi(ssid, password, host);
  
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
        sendData(time, box_total);
        box_total = 0;
      }
  }

  // Set new_box_total to the old total
  new_box_total = box_total;
}


void increse_pin() {
  box_total++;
}