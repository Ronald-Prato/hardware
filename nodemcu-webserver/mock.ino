#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <Servo.h>

const char* ssid = "Rejewski";
const char* password = "Nigga1234";

int ledPin = D7;
int redPin = D6;
int servoPin = D5;
int minPulse = 1000;
int maxPulse = 2000;

Servo servo;
ESP8266WebServer server;

void setup() {
  // put your setup code here, to run once:
  servo.attach(servoPin, minPulse, maxPulse);
  pinMode(ledPin, OUTPUT);
  pinMode(redPin, OUTPUT);
  digitalWrite(ledPin, LOW);

  setupServer();
  
  serverRouting();
  server.begin();
}

void loop() {
  // put your main code here, to run repeatedly:
  server.handleClient();
}

// ==================================================================================

void setupServer () {
  Serial.begin(115200);
  Serial.println();
  Serial.print("Wifi connecting to... ");
  Serial.print(ssid);

  WiFi.begin(ssid, password);
  
  Serial.println();
  Serial.print("Connecting");

  while ( WiFi.status() != WL_CONNECTED ) {
    delay (500);
    Serial.print(".");
  }

  digitalWrite(ledPin, HIGH);
  Serial.println();
  Serial.print("Wifi Connected");
  Serial.print("Node IP Adress: ");
  Serial.print(WiFi.localIP());
}

void serverRouting () {
  server.on("/turn-red-on", turnOnRedLed);
  server.on("/turn-red-off", turnOffRedLed);
  server.on("/servo-180", moveServo180);
  server.on("/servo-0", moveServo0);
}

void turnOnRedLed () {
  digitalWrite(redPin, HIGH);
  server.send(200, "text/html", "<h1> Red Led Turned On </h1>");
}

void turnOffRedLed () {
  digitalWrite(redPin, LOW);
  server.send(200, "text/html", "<h1> Red Led Turned Off </h1>");
}

void moveServo180() {
  servo.write(180);
  server.send(200, "text/html", "<h1> Servo moved to 180 deg </h1>");
}

void moveServo0() {
  servo.write(0);
  server.send(200, "text/html", "<h1> Servo moved to 0 deg </h1>");
}
