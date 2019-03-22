#include<ESP8266HTTPClient.h>


#include <DHT.h>
#include <DHT_U.h>
#include<ESP8266WiFi.h>

char* ssid="ssid";
char* password="password";
char* host="www.dweet.io";

/*
  Blink

  Turns an LED on for one second, then off for one second, repeatedly.

  Most Arduinos have an on-board LED you can control. On the UNO, MEGA and ZERO
  it is attached to digital pin 13, on MKR1000 on pin 6. LED_BUILTIN is set to
  the correct LED pin independent of which board is used.
  If you want to know what pin the on-board LED is connected to on your Arduino
  model, check the Technical Specs of your board at:
  https://www.arduino.cc/en/Main/Products

  modified 8 May 2014
  by Scott Fitzgerald
  modified 2 Sep 2016
  by Arturo Guadalupi
  modified 8 Sep 2016
  by Colby Newman

  This example code is in the public domain.

  http://www.arduino.cc/en/Tutorial/Blink
*/
#include<DHT.h>
#define DHT_pin D4
DHT dht(DHT_pin,DHT11);
// the setup function runs once when you press reset or power the board
void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  dht.begin();

  Serial.begin(115200);
  pinMode(LED_BUILTIN, OUTPUT);
  WiFi.begin(ssid,password);
  while(WiFi.status() !=WL_CONNECTED){
 Serial.println("trying");
 delay(2000);
  }
  Serial.println("conected?ip=");
Serial.print(WiFi.localIP());
}

// the loop function runs over and over again forever
void loop() {
  
  float t=dht.readTemperature();
  float h=dht.readHumidity();
  Serial.println("temperature");
  Serial.println(t);
  Serial.println("Humidity");
  Serial.println(h);
  digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(1000);                       // wait for a second
  digitalWrite(LED_BUILTIN, LOW);    // turn the LED off by making the voltage LOW
  delay(1000);  
  // wait for a second
  //WiFiClient client;
  //const int httpPort = 80;
  //if (!client.connect(host, httpPort)) {
  //Serial.println("connection failed");
  //return;
//  a.get("https://dweet.io/for/dweet/killerlock1215?temperature"+String(t)+"&"+"Humidity"+String(h));
//  while (a.available()) {
//    char c = a.read();
//    SerialUSB.print(c);
//  }
//  SerialUSB.flush();

//  delay(5000);
//
HTTPClient http;
http.begin("http://dweet.io/dweet/for/ajaybingi?temperature="+String(t)+"&Humidity="+String(h));
int httpcode=http.GET();
while(httpcode==0)
{
  int httpcode=http.GET();
}
if(httpcode>0){
String payload=http.getString();
Serial.println(payload);}
http.end();
delay(500);



}
