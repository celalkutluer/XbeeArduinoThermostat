//#include <SoftwareSerial.h>
//
//#define xBeeRxPin 1
//#define xBeeTxPin 0
//SoftwareSerial xBeeSerial(xBeeRxPin, xBeeTxPin);
//#define potpin A3 //Potansiyometreyi A0 pinine tanımlıyoruz
//int deger = 0; //"Değer" adlı 0 başlangıçlı bir değişken tanımlıyoruz
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

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
char str[5];
float power;
int i = 0;
///
///+- BUTON
int artiButonDurum = 0;
int eksiButonDurum = 0;
float sicaklik = 20;
///
int roleDurum = 0;
void setup() {
  //  xBeeSerial.begin(57600);
  Serial.begin(57600);
  //Serial.begin(9600); //9600 Baund bir seri haberleşme başlatıyoruz
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
  //  Serial.println(sicaklik);

  //  deger = map(analogRead(potpin), 0, 1023, 0, 50); //"Değer" değişkeni potansiyometrenin değerini okuyup buna göre değişir
  //  Serial.println(deger); //Okunan değer seri monitörde mesaj olarak gönderilir
  //  delay(600); //Bu işlem 100 milisaniye aralıklarla yapılır
  ///
  //  digitalWrite(13, HIGH);
  //  delay(1000);
  //  digitalWrite(13, LOW);
  //  delay(1000);
  ///
  //  union floatByte_t {
  //    float f;
  //    byte b[5];
  //  };
  //
  //  floatByte_t recvTemp;
  //  float myValues[10];
  //  //read four bytes that make up the float value
  //  for (int i = 0; i < 5; i++) recvTemp.b[i] = Serial.read();
  //  Serial.println(recvTemp.f);
  //  myValues[0] = recvTemp.f;       //save the value in an array
  //  //float tempC = sensors.getTempCByIndex(0);
  //  //xBeeSerial.write(tempC);
  //  //delay(5000);
  if (Serial.available() > 0) {
    //xBeeSerial.println( xBeeSerial.parseFloat());
    //      data = xBeeSerial.read(); //save data into integer variable dataByte
    //      xBeeSerial.println(data);
    //    float tempC = Serial.write(Serial.read());
    //    if (tempC > 0)Serial.print("başarılı");
    str[i] = Serial.read();
    i++;
  }
  if (i == 5) {
    i = 0;
    power = atof(str);
    Serial.print("oda sıcaklığı: ");
    Serial.println(power);
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
  display.print(power);
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
  if (power <= sicaklik) {
    roleDurum = 1;
  }

  if (power <= sicaklik + 1 && roleDurum == 1) {
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
