#include <WiFiNINA.h>;
#include "DHT.h"
#include <WiFiClient.h>;
#include <ThingSpeak.h>;

const char * ssid = "xxxx";
const char * password ="xxxx";

int pin5 = A5;
int temp, humidity;

WiFiClient client;

long channelId = 2483904;
const char * myAPIKey = "MBTS66HST547BT4W";

void setup() {
  // put your setup code here, to run once:
 
  // starts the serial communication:
  Serial.begin(9600);
  Serial.println("Serial begin...");
  //dht.begin();
  delay(10);
  // connect to WiFi network
  WiFi.begin(ssid, password);
  ThingSpeak.begin(client);
}

void loop() {
  // put your main code here, to run repeatedly:
  temp = analogRead(pin5) * 0.0322265; // converting analog output to celcius degrees
  humidity = ((30.855*(analogRead(pin5)/204.6)) - 11.504);

  //DHT_data();
  //temp = dht.readTemperature();
  //humidity = dht.readHumidity();
  delay(1000);

  //temp = DHT.readTemperature();
  Serial.print("Temperature: ");
  Serial.print(temp);     // print on the serial monitor
  Serial.println("c");
  delay(1000);

  //humidity = dht.readHumidity();
  Serial.print("Humidity: ");
  Serial.print(humidity);     // print on the serial monitor
  Serial.println("%");
  delay(1000);

  // update the view in ThingSpeak
  //ThingSpeak.writeField(channelId, 2, humidity, myAPIKey);
  //delay(100);
  updateThingspeak();

}

void updateThingspeak()
{
  String postInfo = myAPIKey;
  postInfo += "&field1=";
  postInfo += String(temp);
  postInfo += "&field2=";
  postInfo += String(humidity);
  postInfo += "\r\n\r\n";

  client.print("POST /update HTTP/1.1\n");
  client.print("Host: api.thingspeak.com\n");
  client.print("Connection: close\n");
  client.print("X-THINGSPEAKAPIKEY: ")+myAPIKey+String("\n");
  client.print("Content-Type: application/x-www-form-urlencoded\n");
  client.print("Content-Lenght: ");
  client.print(postInfo.length());
  client.print("\n\n");
  client.print(postInfo);

  //Serial.print("Content-Lenght: ");
  //Serial.print(postInfo.length());
  Serial.print("Temperature: ");
  Serial.print(temp);     // print on the serial monitor
  Serial.println("c");
  Serial.print("Humidity: ");
  Serial.print(humidity);     // print on the serial monitor
  Serial.println("%");
  delay(1000);
}