#define echoPin 2  // Attach pin D2 Arduino to pin Echo of HC-SR04
#define trigPin 3  // Attach pin D3 Arduino to pin Trig of HC-SR04

long duration; // Duration of Sound Wave travel in Microseconds
int distance;  // Distance Measurement

void setup() {
  // put your setup code here, to run once:
  pinMode(trigPin, OUTPUT); //Sets the trigPin as an OUTPUT
  pinMode(echoPin, INPUT);  //Sets the echoPin as an INPUT
  Serial.begin(9600);
  Serial.println("Ultrasonic Sensor HC-SR04 Test");
  Serial.println("with Arduino UNO R3");
}

void loop() {
  // Clear the trigPin Condition :
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  
  //Set the triPin HIGH(Active) for 10 microseconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);

  //The pulseIn function times the signal return after bouncing off the object
  duration = pulseIn(echoPin, HIGH);

  distance = duration * 0.034 / 2;  //Speed of sound wave divided by 2(wave goes and comes back)

  Serial.print("Distance : ");
  Serial.print(distance);
  Serial.println(" cm");
  delay(10);
}
