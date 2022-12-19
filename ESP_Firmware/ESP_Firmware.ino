//This code is modified from
//https://tttapa.github.io/ESP8266/Chap07%20-%20Wi-Fi%20Connections.html

#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WiFiMulti.h> 
#include <ESP8266mDNS.h>
#include <ESP8266WebServer.h>

ESP8266WiFiMulti wifiMulti;     // Create an instance of the ESP8266WiFiMulti class, called 'wifiMulti'

ESP8266WebServer server(80);    // Create a webserver object that listens for HTTP request on port 80

const int led = 2;

void handleMessage();
void handleNotFound();
void sendControllerCommand(String left_speed, String right_speed);

void setup(void){
  Serial.begin(9600);         // Start the Serial communication to send messages to the computer
  delay(10);
  //Serial.println('\n');

  pinMode(led, OUTPUT);
  digitalWrite(led,1);

  wifiMulti.addAP("jfrhome", "6108045996");   // add Wi-Fi networks you want to connect to

  //Serial.println("Connecting ...");
  int i = 0;
  while (wifiMulti.run() != WL_CONNECTED) { // Wait for the Wi-Fi to connect: scan for Wi-Fi networks, and connect to the strongest of the networks above
    delay(250);
    //Serial.print('.');
  }
  /*Serial.println('\n');
  Serial.print("Connected to ");
  Serial.println(WiFi.SSID());              // Tell us what network we're connected to
  Serial.print("IP address:\t");
  */
  Serial.println(WiFi.localIP());           // Send the IP address of the ESP8266 to the computer

  
  if (MDNS.begin("esp8266")) {              // Start the mDNS responder for esp8266.local
    //Serial.println("mDNS responder started");
  } else {
    //Serial.println("Error setting up MDNS responder!");
  }

  server.on("/", HTTP_GET, handleMessage);
  server.onNotFound(handleNotFound);

  server.begin();                           // Actually start the server
  //Serial.println("HTTP server started");
  digitalWrite(led,0);
}

void loop(void){
  server.handleClient();                    // Listen for HTTP requests from clients
}

void handleMessage() {
  String left_speed="0";
  String right_speed="0";
  String left_servo="127";
  String right_servo="127";
  if(server.hasArg("left_speed")){
    left_speed = server.arg("left_speed");
  }
  if(server.hasArg("right_speed")){
    right_speed = server.arg("right_speed");
  }
  if(server.hasArg("yaw_servo")){
    left_servo = server.arg("yaw_servo");
  }
  if(server.hasArg("pitch_servo")){
    right_servo = server.arg("pitch_servo");
  }
  server.send(200);
  sendControllerCommand(left_speed, right_speed, left_servo, right_servo);
}

void sendControllerCommand(String left_speed_s, String right_speed_s, String left_servo_s, String right_servo_s){
  int left_speed_i = left_speed_s.toInt();
  int right_speed_i = right_speed_s.toInt();

  uint8_t left_servo = left_servo_s.toInt();
  uint8_t right_servo = right_servo_s.toInt();

  uint8_t left_speed  = abs(left_speed_i);
  uint8_t right_speed = abs(right_speed_i);

  Serial.write(0xFF);
  Serial.write(((left_speed_i >= 0) << 1) | ((right_speed_i >= 0) << 0));
  Serial.write(left_speed);
  Serial.write(right_speed);
  Serial.write(left_servo);
  Serial.write(right_servo);

  
}

void handleNotFound(){
  server.send(404); // Send HTTP status 404 (Not Found) when there's no handler for the URI in the request
}
