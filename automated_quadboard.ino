int E1 = 6;
int E2 = 5;
int IN1 = 4;
int IN2 = 7;
int IN3 = 8;
int IN4 = 3;
int LS = 11;
int RS = 12;
int alarmled = 13;
int okled = 14;
const int trigPin = 10;
const int echoPin = 9;
long duration;
int distance;
char val;





void setup() {
  Serial.begin(9600); // Starts the serial communication
  pinMode(E1, OUTPUT);
  pinMode(E2, OUTPUT);

  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(alarmled, OUTPUT);
  pinMode(okled, OUTPUT);
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin, INPUT); // Sets the echoPin as an Input


}

void loop() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);
  // Calculating the distance
  distance = duration * 0.034 / 2;
  // Prints the distance on the Serial Monitor
  Serial.print("Distance: ");
  Serial.println(distance);

  /*----------------LINE FOLLOWING CODE START------------------*/

  if (digitalRead(LS) && digitalRead(RS))  {
    forward(); // Move Forward
  }
  if ((digitalRead(LS)) && !(digitalRead(RS)))  {
    right(); // Turn right
  }
  if (!(digitalRead(LS)) && (digitalRead(RS))) {
    left(); // turn left
  }
  if (!(digitalRead(LS)) && !(digitalRead(RS))) {
    finish(); // finish
  }

  /*----------------LINE FOLLOWING CODE END------------------*/


  /*----------------OBSTACLE AVOIDING CODE START------------------*/

  if (distance >= 50)  {
    forward(); // Move Forward
  }
  if (distance < 50)  {
    right();
    delay(1000);
if ( distance < 50 ){
  alarm();
}
else {
  ok();
}
  }
  /*----------------OBSTACLE AVOIDING CODE END------------------*/


  /*----------------BT CONTROL CODE START------------------*/

  if (Serial.available() > 0) {
    val = Serial.read();
  }

  switch (val) {
    case 'F':
      forward();
      break;
    case 'D':
      reverse();
      break;
    case 'L':
      left();
      break;
    case 'R':
      right();
      break;
    case 'S':
      finish();
      break;

  }




}


void forward() {
  digitalWrite(E1, HIGH);
  digitalWrite(E2, HIGH);
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN4, HIGH);
  digitalWrite(IN3, LOW);
}


void reverse() {
  digitalWrite(E1, HIGH);
  digitalWrite(E2, HIGH);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN4, LOW);
  digitalWrite(IN3, HIGH);

}

void left() {
  digitalWrite(E1, HIGH);
  digitalWrite(E2, HIGH);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN4, HIGH);
  digitalWrite(IN3, LOW);

}

void right() {
  digitalWrite(E1, HIGH);
  digitalWrite(E2, HIGH);
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN4, LOW);
  digitalWrite(IN3, HIGH);

}

void finish() {
  digitalWrite(E1, LOW);
  digitalWrite(E2, LOW);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN4, LOW);
  digitalWrite(IN3, LOW);

}

void alarm() {
  digitalWrite(alarmled, HIGH);
  digitalWrite(okled, LOW);
  delay (100);
  digitalWrite(alarmled, HIGH);
  digitalWrite(okled, LOW);
  delay (100);
}

void ok() {
  digitalWrite(okled, HIGH);
  digitalWrite(alarmled, LOW);

}
