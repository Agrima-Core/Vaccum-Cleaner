#include <Servo.h>

// === Pins ===
// Distance sensor (4-pin)
#define trigPin 2
#define echoPin 3

// L298N #1 (M1 & M4)
#define IN1_A 4
#define IN2_A 5
#define IN3_A 6
#define IN4_A 7

// L298N #2 (M3 & M2)
#define IN1_B 11
#define IN2_B 12
#define IN3_B 13
#define IN4_B 14

// ESC & Servo
#define ESC_PIN 8
#define SERVO_PIN 9

// === Objects ===
Servo ESC;
Servo myServo;

// === Variables ===
long duration;
int distance;

bool isTurning = false;
unsigned long turnStart = 0;
const unsigned long turnDuration = 1200;  // adjust experimentally

int servoPos = 0;
int servoIncrement = 1;
unsigned long lastServoUpdate = 0;
const unsigned long servoInterval = 20;  // 20ms for servo update

// Obstacle detection
const int obstacleDist = 15; // cm
bool obstacleDetected = false;

void setup() {
  // Distance sensor
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  // L298N Motors
  pinMode(IN1_A, OUTPUT);
  pinMode(IN2_A, OUTPUT);
  pinMode(IN3_A, OUTPUT);
  pinMode(IN4_A, OUTPUT);
  pinMode(IN1_B, OUTPUT);
  pinMode(IN2_B, OUTPUT);
  pinMode(IN3_B, OUTPUT);
  pinMode(IN4_B, OUTPUT);

  // ESC & Servo
  ESC.attach(ESC_PIN);
  myServo.attach(SERVO_PIN);

  Serial.begin(9600);
  Serial.println("Robot Starting...");

  // ESC Initialization
  ESC.writeMicroseconds(1000); // stop
  delay(2000);                  // arming delay
  ESC.writeMicroseconds(1500);  // idle forward speed

  moveForward();
}

void loop() {
  unsigned long currentMillis = millis();

  // --- Distance Sensor ---
  distance = getDistance();
  Serial.print("Distance: "); Serial.println(distance);

  // --- Obstacle Detection ---
  if (!isTurning && distance <= obstacleDist && !obstacleDetected) {
    Serial.println("Obstacle Detected! Starting U-turn...");
    isTurning = true;
    turnStart = currentMillis;
    obstacleDetected = true;
    turnU();
  }
  else if (distance > obstacleDist) {
    obstacleDetected = false; // reset for next obstacle
  }

  // --- U-turn timing ---
  if (isTurning && currentMillis - turnStart >= turnDuration) {
    isTurning = false;
    stopMotors();
    delay(200);        // short pause
    moveForward();
    Serial.println("U-turn complete. Moving forward...");
  }

  // --- Servo scanning (non-blocking) ---
  if (currentMillis - lastServoUpdate >= servoInterval) {
    servoPos += servoIncrement;
    if (servoPos >= 180 || servoPos <= 0) servoIncrement = -servoIncrement;
    myServo.write(servoPos);
    lastServoUpdate = currentMillis;
  }
}

// === Functions ===

void moveForward() {
  // L298N #1 → forward
  digitalWrite(IN1_A, HIGH);
  digitalWrite(IN2_A, LOW);
  digitalWrite(IN3_A, HIGH);
  digitalWrite(IN4_A, LOW);

  // L298N #2 → forward
  digitalWrite(IN1_B, HIGH);
  digitalWrite(IN2_B, LOW);
  digitalWrite(IN3_B, HIGH);
  digitalWrite(IN4_B, LOW);

  // ESC forward
  ESC.writeMicroseconds(1600); // moderate forward speed
}

void moveBackward() {
  digitalWrite(IN1_A, LOW);
  digitalWrite(IN2_A, HIGH);
  digitalWrite(IN3_A, LOW);
  digitalWrite(IN4_A, HIGH);

  digitalWrite(IN1_B, LOW);
  digitalWrite(IN2_B, HIGH);
  digitalWrite(IN3_B, LOW);
  digitalWrite(IN4_B, HIGH);

  ESC.writeMicroseconds(1400); // if ESC supports reverse
}

void stopMotors() {
  digitalWrite(IN1_A, LOW);
  digitalWrite(IN2_A, LOW);
  digitalWrite(IN3_A, LOW);
  digitalWrite(IN4_A, LOW);
  digitalWrite(IN1_B, LOW);
  digitalWrite(IN2_B, LOW);
  digitalWrite(IN3_B, LOW);
  digitalWrite(IN4_B, LOW);

  ESC.writeMicroseconds(1500); // idle stop
}

void turnU() {
  // Diagonal motors for smooth U-turn
  digitalWrite(IN1_A, HIGH);
  digitalWrite(IN2_A, LOW);
  digitalWrite(IN3_A, LOW);
  digitalWrite(IN4_A, HIGH);

  digitalWrite(IN1_B, LOW);
  digitalWrite(IN2_B, HIGH);
  digitalWrite(IN3_B, HIGH);
  digitalWrite(IN4_B, LOW);

  ESC.writeMicroseconds(1600); // moderate speed during turn
}

int getDistance() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH, 20000); // 20ms timeout
  if (duration == 0) return 999;

  int dist = duration * 0.034 / 2;
  return dist;
}