#include <SPI.h>
#include <Ethernet.h>
#include <PubSubClient.h>
#include "DHT.h"

// Update these with values suitable for your network.
byte mac[]    = {  0xDE, 0xED, 0xBA, 0xFE, 0xFE, 0xED };
byte server[] = { 192, 168, 0, 104 };
byte ip[]     = { 192, 168, 0, 105 };

DHT dht;

void callback(char* topic, byte* payload, unsigned int length) {
  // handle message arrived
}

EthernetClient ethClient;
PubSubClient client(server, 1883, callback, ethClient);

void setup()
{
  // setup DHT22 at pin 7
  dht.setup(7);
}

void loop()
{
  delay(dht.getMinimumSamplingPeriod());
  float humidity = dht.getHumidity();
  float temperature = dht.getTemperature();
  
  static float f_val = 123.6794;
  static char outstr1[15];
  static char outstr2[15];

  dtostrf(temperature,3, 2, outstr1);
  dtostrf(humidity,3, 2, outstr2);
  
  Ethernet.begin(mac, ip);
  delay(1000);
  if (client.connect("arduinoClient")) {
    client.publish("arduinoClient/Temperature",outstr1);
    client.publish("arduinoClient/Humidity",outstr2);
  }
  delay(2000);
}
