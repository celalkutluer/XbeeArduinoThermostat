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
  //  xBeeSerial.begin(9600);
  //  xBeeSerial.println("Hello, world?");
  sensors.begin();
}

void loop() {
  sensors.requestTemperatures(); // Send the command to get temperatures
  float tempC = sensors.getTempCByIndex(0);
//  xBeeSerial.print("Temp: ");
//  delay(1);
  xBeeSerial.print(tempC);
  delay(6000);

  //  xBeeSerial.write("Celal");
  //  delay(600);
  //    String f_str=String(tempC);
  //  xBeeSerial.write((float)tempC);
  //    Serial.println(f_str);
  //
  //     //float temp = -11.7;
  //     byte * b = (byte *) &tempC;
  //     xBeeSerial.write(b[4]);
  //            Serial.println(b[4]);
  //     xBeeSerial.write(b[3]);
  //          Serial.println(b[3]);
  //     xBeeSerial.write(b[2]);
  //          Serial.println(b[2]);
  //     xBeeSerial.write(b[1]);
  //          Serial.println(b[1]);
  //     xBeeSerial.write(b[0]);
  //          Serial.println(b[0]);
  //
  //byte * b = (byte *) &tempC;
  //
  // xBeeSerial.write(b,5);
  //  union floatByte_t {
  //    float f;
  //    byte b[5];
  //  };
  //
  //  floatByte_t xmitTemp;
  //
  //  xmitTemp.f = sensors.getTempCByIndex(0);     //get the temperature
  //
  //  //send the four bytes that make up the float value
  //  for (int i = 0; i < 5; i++) {
  //    xBeeSerial.write( xmitTemp.b[i] );
  //  }
  //  Serial.println(xmitTemp.f);
  //
  // delay(5000);
  //
  /////a union between a float and a four-byte array
  //union floatByte_t {
  //   float f;
  //   byte b[4];
  //};
  //
  //   floatByte_t xmitTemp;
  //
  //   xmitTemp.f = sensors.getTempCByIndex(0);     //get the temperature
  //
  //   //send the four bytes that make up the float value
  //   for (int i = 0; i < 4; i++) xBeeSerial.write( xmitTemp.b[i] );

}
