#include <DHT.h>
#include <NewPing.h>
#include <Servo.h>

#define DHTPIN 2
#define DHTTYPE DHT11

#define LDRPIN A0

#define RELAYPIN 3
#define LEDPIN 4
#define SMOKEPIN 5
#define BUZZERPIN 6
#define TRIGGER_PIN 7
#define ECHO_PIN 8
#define MAX_DISTANCE 200
#define RED_LED_PIN 9
#define SERVO_PIN 10

DHT dht(DHTPIN, DHTTYPE);
NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE);
Servo myservo;
void setup() {
  Serial.begin(9600);
  dht.begin();
  pinMode(LDRPIN, INPUT);
  pinMode(RELAYPIN, OUTPUT);
  pinMode(LEDPIN, OUTPUT);
  pinMode(SMOKEPIN, INPUT);
  pinMode(BUZZERPIN, OUTPUT);
  pinMode(RED_LED_PIN, OUTPUT);
  pinMode(TRIGGER_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  myservo.attach(SERVO_PIN);
}
void loop() {
  float h = dht.readHumidity();
  float t = dht.readTemperature();
  int ldrValue = analogRead(LDRPIN);
  int smokeValue = digitalRead(SMOKEPIN);
  unsigned int distance = sonar.ping_cm();
  Serial.print("Temperature: ");
  Serial.print(t);
  Serial.print("°C, Humidity: ");
  Serial.print(h);
  Serial.print("%, LDR Value: ");
  Serial.print(ldrValue);
  Serial.print(", Smoke: ");
  Serial.print(smokeValue);
  Serial.print(", Distance: ");
  Serial.print(distance);
Serial.println(" cm");

  if (t > 25) {
    myservo.writeMicroseconds(2000); // Full speed clockwise
  } else {
    myservo.writeMicroseconds(1000); // Full speed counterclockwise
  }
  if (ldrValue < 800) {
    digitalWrite(LEDPIN, HIGH);
    digitalWrite(RELAYPIN, HIGH);
  } else {
    digitalWrite(LEDPIN, LOW);
    digitalWrite(RELAYPIN, LOW);
    Serial.print("ENVIRONMENT IS BRIGHT, ");
    Serial.println("Relay is off and the lights are switched off");
  }
  if (smokeValue == HIGH) {
    digitalWrite(BUZZERPIN, HIGH);
    Serial.println("Smoke detected, ESCAPE TO YOUR NEAREST EXIT");
  } else {
    digitalWrite(BUZZERPIN, LOW);
  }

  if (distance < 20) { // You can adjust this value according to your requirement for the range
    digitalWrite(RED_LED_PIN, HIGH);
    Serial.println("SOMEONE AT THE DOOR");
  } 
else {
    digitalWrite(RED_LED_PIN, LOW);
  }
 delay(2000); // Delay between readings
}
