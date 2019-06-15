#include<SPI.h>
#include <Wire.h>
#include <ESP8266WiFi.h>
#include <PubSubClient.h>

char buff[]="";
const char* ssid = // your ssid;
const char* password = // your password";
const char* mqtt_server = "iot.eclipse.org";
volatile bool receivedone; 
int index1 = 0;
volatile bool published=1;
char *msg="No message";

WiFiClient espClient;
PubSubClient client(espClient);
long lastMsg = 0;
//char msg[50];
int value = 0;
//int led=16;

void setup_wifi() {

  delay(10);
  // We start by connecting to a WiFi network
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  randomSeed(micros());

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
  }
  Serial.println();
  Wire.beginTransmission(8); 
  for(int i=0; i<1; i++){  /* transfer buff data per second */
      Serial.println("Start Payload");
      Serial.println(sizeof payload);
      Serial.println((char)payload[i]);
      /* begin with device address 8 */
      Wire.write((char)payload[i]);  /* sends hello string */
      Serial.println("End Payload");
      }
  Wire.write('\n');
  Wire.endTransmission();
  delay(1000); 
}

void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Create a random client ID
    String clientId = "ESP8266Client-";
    clientId += String(random(0xffff), HEX);
    // Attempt to connect
    if (client.connect(clientId.c_str())) {
      Serial.println("connected");
      // Once connected, publish an announcement...
      /*if(!published){
       
      client.publish("outTopic007", msg);
      published =1; }*/
      //index1=0;}
      // ... and resubscribe
 //     client.subscribe("inTopic007");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}
void setup() {
 Serial.begin(115200);
 Wire.begin(D1, D2);
 setup_wifi();
 client.setServer(mqtt_server, 1883);
 client.setCallback(callback);
}

/*
 It connects to an MQTT server then:
  - publishes "hello world" to the topic "outTopic" every two seconds
  - subscribes to the topic "inTopic", printing out any messages
    it receives. NB - it assumes the received payloads are strings not binary
  - If the first character of the topic "inTopic" is an 1, switch ON the ESP Led,
    else switch it off

 It will reconnect to the server if the connection is lost using a blocking
 reconnect function. See the 'mqtt_reconnect_nonblocking' example for how to
 achieve the same result without blocking the main loop.

 To install the ESP8266 board, (using Arduino 1.6.4+):
  - Add the following 3rd party board manager under "File -> Preferences -> Additional Boards Manager URLs":
       http://arduino.esp8266.com/stable/package_esp8266com_index.json
  - Open the "Tools -> Board -> Board Manager" and click install for the ESP8266"
  - Select your ESP8266 in "Tools -> Board"

*/



// Update these with values suitable for your network.

void loop() {
  if (!client.connected()) {
    reconnect();
  }
  client.loop();
 Wire.requestFrom(8,1);
 published = 0;
 Serial.println("Request Data");
while(Wire.available()){
    char c = Wire.read();
    Serial.write(c);
    if(c=='0')
     msg = "No Intrusion Detected";
 else if (c=='1')
     msg = "Intrusion Detected";
 if(!published){
       client.publish("outTopic008", msg);
      published =1; 
      }
    
    
 }
 
 delay(1000);

}
