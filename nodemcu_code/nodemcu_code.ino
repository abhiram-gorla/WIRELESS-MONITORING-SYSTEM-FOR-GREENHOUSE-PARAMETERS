#include<ESP8266HTTPClient.h>


#include <DHT.h>
#include <DHT_U.h>
#include<ESP8266WiFi.h>

char* ssid="killerlock";
char* password="12345678";
char* host="www.dweet.io";


#include<DHT.h>
#define DHT_pin D1
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
pinMode(A0,INPUT);
}

// the loop function runs over and over again forever
void loop() {
  int m;
  m=analogRead(A0);
  m=(m/1024)*100;
  float t=dht.readTemperature();
  float h=dht.readHumidity();
  Serial.println("temperature");
  Serial.println(t);
  Serial.println("Humidity");
  Serial.println(h);
  Serial.println("soil moisture");
  Serial.println(m);
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
