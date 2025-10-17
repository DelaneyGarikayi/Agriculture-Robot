#include <Servo.h>
#include <DHT.h>
#define DHTPIN 2
#define DHTTYPE DHT11
// Motor driver pins (4 DC motors)
#define LEFT_MOTOR1 3
#define LEFT_MOTOR2 4
#define RIGHT_MOTOR1 5
#define RIGHT_MOTOR2 6
// Pump and Sensors
#define PUMP_IN1 7
#define PUMP_IN2 8
#define SOIL_SENSOR A0
#define TRIG_PIN 9
#define ECHO_PIN 10
#define SERVO_PIN 11
Servo servo;
DHT dht(DHTPIN, DHTTYPE);
void setup() {
Serial.begin(9600);
pinMode(LEFT_MOTOR1, OUTPUT);
pinMode(LEFT_MOTOR2, OUTPUT);
pinMode(RIGHT_MOTOR1, OUTPUT);
pinMode(RIGHT_MOTOR2, OUTPUT);
pinMode(PUMP_IN1, OUTPUT);
pinMode(PUMP_IN2, OUTPUT);
pinMode(TRIG_PIN, OUTPUT);
pinMode(ECHO_PIN, INPUT);
dht.begin();
servo.attach(SERVO_PIN);
servo.write(0);
stopAllMotors();
}
void loop() {
int moisture = analogRead(SOIL_SENSOR);
float temp = dht.readTemperature();
float hum = dht.readHumidity();
Serial.print("Soil Moisture: "); Serial.println(moisture);
Serial.print("Temperature: "); Serial.println(temp);
Serial.print("Humidity: "); Serial.println(hum);
if (moisture < 400) {
activatePump();
} else {
stopPump();
}
delay(2000);
}
void motorForward(int in1, int in2) {
digitalWrite(in1, HIGH);
digitalWrite(in2, LOW);
}
void motorBackward(int in1, int in2) {
digitalWrite(in1, LOW);
digitalWrite(in2, HIGH);
}
void stopAllMotors() {
digitalWrite(LEFT_MOTOR1, LOW);
digitalWrite(LEFT_MOTOR2, LOW);
digitalWrite(RIGHT_MOTOR1, LOW);
digitalWrite(RIGHT_MOTOR2, LOW);
}
void activatePump() {
digitalWrite(PUMP_IN1, HIGH);
digitalWrite(PUMP_IN2, LOW);
}
void stopPump() {
digitalWrite(PUMP_IN1, LOW);
digitalWrite(PUMP_IN2, LOW);
}