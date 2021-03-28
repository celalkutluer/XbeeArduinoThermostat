//#include <SoftwareSerial.h>
//#define xBeeRxPin 1
//#define xBeeTxPin 0
//SoftwareSerial xBeeSerial(xBeeRxPin, xBeeTxPin);


#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
// Include Wire Library for I2C
#include <Wire.h>
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
#define OLED_RESET     4 // Reset pin # (or -1 if sharing Arduino reset pin)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

#define ledPin 13
#define artiButon 12
#define eksiButon 11
#define rolePin 10

///XBEE FLOAT DATA
char str[8];
char data[5];
int i = 0;
///
///+- BUTON
int artiButonDurum = 0;
int eksiButonDurum = 0;
float sicaklik = 20;
///
int roleDurum = 0;
float device_1 = 0.00;//defaulf value
float device_2 = 0.00;//defaulf value
float ort_sic = 0.00;

void setup() {
  Serial.begin(57600);
  pinMode(ledPin, OUTPUT);
  pinMode(artiButon, INPUT);
  pinMode(eksiButon, INPUT);
  pinMode(rolePin, OUTPUT);

  ///
  // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Address 0x3D for 128x64
    Serial.println(F("SSD1306 allocation failed"));
    for (;;); // Don't proceed, loop forever
  }

  // Draw a single pixel in white
  display.drawPixel(10, 10, WHITE);

  display.display();
  delay(1000);

  display.clearDisplay();

  display.setTextSize(2); // Draw 2X-scale text
  display.setTextColor(WHITE);
  display.setCursor(0, 0);
  display.println(F("THERMOSTAT"));
  display.display();      // Show initial text
  delay(100);
  ///
}


void loop() {
  artiButonDurum = digitalRead(artiButon);
  eksiButonDurum = digitalRead(eksiButon);
  if (artiButonDurum == 1) {
    sicaklik += 0.5;
    delay(400);
  }
  if (eksiButonDurum == 1) {
    sicaklik -= 0.5;
    delay(400);

  }

  if (Serial.available() > 0) {
    str[i] = Serial.read();
    //Serial.println(str[i]);
    if (i > 2) {
      data[i - 3] = str[i];
    }
    i++;
  }
  if (i == 8) {
    i = 0;
    if (str[2] == '1') {
      device_1  = atof(data);
    }
    else if (str[2] == '2') {
      device_2 = atof(data);
    }
    if (device_1 == 0) {
      ort_sic = (device_2 + device_2) / 2;
    }
    else if (device_2 == 0) {
      ort_sic = (device_1 + device_1) / 2;
    }
    else {
      ort_sic = (device_1 + device_2) / 2;
    }
    Serial.print("1. Xbee sıcaklık: ");
    Serial.println(device_1);
    Serial.print("2. Xbee sıcaklık: ");
    Serial.println(device_2);
    Serial.print("Ortalama oda sıcaklığı: ");
    Serial.println(ort_sic);
    Serial.print("ayarlanan sicaklık : ");
    Serial.println(sicaklik);
    Serial.print("kombi durumu : ");
    Serial.println(roleDurum);

  }
  ///
  //clear display
  display.clearDisplay();

  // display ortam sıcaklığı
  display.setTextSize(1);
  display.setCursor(0, 0);
  display.print("Ort. Sicaklik: ");
  display.setTextSize(2);
  display.setCursor(0, 10);
  display.print(ort_sic);
  display.print(" ");
  display.setTextSize(1);
  display.cp437(true);
  display.write(167);
  display.setTextSize(2);
  display.print("C");

  // display istenilen sıcaklık
  display.setTextSize(1);
  display.setCursor(0, 28);
  display.print("Istenilen: ");
  display.setTextSize(2);
  display.setCursor(0, 38);
  display.print(sicaklik);
  display.print(" ");
  display.setTextSize(1);
  display.cp437(true);
  display.write(167);
  display.setTextSize(2);
  display.print("C");

  // display istenilen sıcaklık
  display.setTextSize(1);
  display.setCursor(0, 54);
  if (roleDurum == 1) {
    display.print("Kombi CALISIYOR");
  }
  else {
    display.print("Kombi DURDU");
  }

  display.display();
  ///LED YAKMA ve Röle Tetikleme
  if (ort_sic <= sicaklik) {
    roleDurum = 1;
  }

  if (ort_sic <= sicaklik + 1 && roleDurum == 1) {
    digitalWrite(ledPin, HIGH);
    digitalWrite(rolePin, LOW);
  }
  else {
    digitalWrite(ledPin, LOW);
    digitalWrite(rolePin, HIGH);
    roleDurum = 0;
  }
  ///
}
