//First, we identify which digital pins on the arduino have connections with the electronic components.

const int trigPin = 8;

const int echoPin = 13;

const int relay = 3;    // the number of the LED pin

const int laserPin = 11;

const int laser2Pin = 12;

#include <Servo.h>


//Here we define the base positions for the servo motors.

Servo servo2;

Servo servo1;

int pos1 = 0;

int pos2 = 0;

int count = 0;


//This line makes the following code dependent on the distance sensor.

long duration, distance;


//This section tells the arduino which pins are doing what.

void setup() {

  pinMode(trigPin, OUTPUT);

  pinMode(echoPin, INPUT);

  pinMode(relay, OUTPUT);

  pinMode(laserPin, OUTPUT);

  pinMode(laser2Pin, OUTPUT);

  servo1.attach(9);

  servo2.attach(10);

  Serial.begin(9600);

}


//This next section defines the functions of our circuit components. The first part, void sense, is for the distance sensor, //and it tells the arduino how to define distance, and how to report it back to us.


void sense(){

  digitalWrite(trigPin, LOW);

  delayMicroseconds(2);

  digitalWrite(trigPin, HIGH);

  delayMicroseconds(10);

  digitalWrite(trigPin, LOW);

 

  duration = pulseIn(echoPin, HIGH);

  distance = (duration/2)/29.1;

  Serial.print(distance);

  Serial.println(" cm");

  delay(1);

}


//void spray is the setup for the spray bottle. We attached a relay to the spray bottle to turn it on or off, so the function to //turn the sprayer on and off is actually triggering the relay.

void spray() {

  digitalWrite(relay, HIGH);

  delay(3000);

  digitalWrite(relay,LOW);

  delay (3000);

  digitalWrite(relay,HIGH);

  delay(3000);

  digitalWrite(relay, LOW);

  delay(1000);

}


//void turnFor1() defines the function for the first servo to turn, and allows us to manipulate the range that the servo turns within. 

void turnFor1(){

  for (pos1 = 10; pos1 <= 50; ) { // goes from 0 degrees to 180 degrees

    // in steps of 10 degree

    pos1 = pos1 + 5;

    servo1.write(pos1);              // tell servo to go to position in variable 'pos'

    delay(15);                       // waits 15ms for the servo to reach the position

  }

}


//void turnFor2() does the same thing for the second servo.

void turnFor2(){

  for (pos2 = 40; pos2 <= 80; ) { // goes from 0 degrees to 180 degrees

    // in steps of 10 degree

    pos2 = pos2 + 5;

    servo2.write(pos2);              // tell servo to go to position in variable 'pos'

    delay(15);                       // waits 15ms for the servo to reach the position

  }

}


//void turnBack1() returns servo 1 to its original position.

void turnBack1(){

  for (pos1 = 50; pos1 >= 10;) { // goes from 180 degrees to 0 degrees

    pos1 = pos1 - 5;

    servo1.write(pos1);              // tell servo to go to position in variable 'pos'

    delay(15);                       // waits 15ms for the servo to reach the position

  }

}


//void turnBack2() returns servo 2 to its original position.

void turnBack2(){

  for (pos2 = 80; pos2 >= 40;) { // goes from 180 degrees to 0 degrees

    pos2 = pos2 - 5;

    servo2.write(pos2);              // tell servo to go to position in variable 'pos'

    delay(15);                       // waits 15ms for the servo to reach the position

  }

}


//void stop() tells the servo to stop moving.

void stop(){

  pos1=pos1;

  pos2=pos2;

  servo1.write(pos1);

  servo2.write(pos2);

}


//void laserOn() tells the lasers to turn on.

void laserOn(){

digitalWrite(laserPin, HIGH);

digitalWrite(laser2Pin, HIGH);

}


//void laserOff() tells the lasers to turn off.

void laserOff(){

  digitalWrite(laserPin, LOW);

  digitalWrite(laser2Pin, LOW);

}


//This next section void loop()is the actual script that ties all the functions together. It tells each component when to //execute its function.


void loop() {

  sense();

  if (distance < 20) {

    spray();

    for (count = 0; count < 10;) {

      laserOn();

      turnFor1();

      delay(40);

      turnFor2();

      delay(40);

      stop();

      delay(500);

      turnBack1();

      delay(40);

      turnBack2();

      delay(40);

      stop();

      pos1 = 10;

      servo1.write(pos1);

      pos2 = 40;

      servo2.write(pos2);

      delay(500);

      count=count+1;

    }


    laserOff();

  }

  

//This section at the end ends the loop, and tells the arduino to wait 500 seconds before starting the loop again.

stop();

  delay (500);


}