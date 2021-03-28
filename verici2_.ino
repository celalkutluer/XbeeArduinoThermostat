#include <SoftwareSerial.h>
#include <OneWire.h>
#include <DallasTemperature.h>

#define ONE_WIRE_BUS 2 //sıcaklık data
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);

#define xBeeRxPin 11
#define xBeeTxPin 10
SoftwareSerial xBeeSerial(xBeeRxPin, xBeeTxPin);


void setup() {
  xBeeSerial.begin(57600);
  sensors.begin();
}

void loop() {
  sensors.requestTemperatures(); // Send the command to get temperatures
  float tempC = sensors.getTempCByIndex(0);
  xBeeSerial.print("d:2");
  xBeeSerial.print(tempC);
  delay(2000);
}
