// C++ code

// set up distance variable
int dist = 0;

// function to read ultrasonic and convert to cms
long ultrasonic_read(int trigPin, int echoPin)
{
  // set the trigger pin to low and wait 2 microseconds
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  // set trigger high for 10 microseconds then set to low
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // read the echo pin, and convert to cms before returning
  return 0.01723 * pulseIn(echoPin, HIGH);
}

// function to control LEDs
void LED_control(bool LED_1, bool LED_2, bool LED_3, bool LED_4)
{
  digitalWrite(2, LED_1);
  digitalWrite(3, LED_2);
  digitalWrite(4, LED_3);
  digitalWrite(5, LED_4);
}

// function to output data to serial
void output(int dist, bool LED_1, bool LED_2, bool LED_3, bool LED_4)
{
  // output the distance recorded
  Serial.print(dist);
  Serial.println("cm");
  // output the ststus of each LED
  Serial.print("LED 1: ");
  Serial.println(LED_1);
  Serial.print("LED 2: ");
  Serial.println(LED_2);
  Serial.print("LED 3: ");
  Serial.println(LED_3);
  Serial.print("LED 4: ");
  Serial.println(LED_4);
  Serial.println();
}

// setup function ran before anything else
void setup()
{
  // start the serial
  Serial.begin(9600);
  // set the ultrasonics echo pin to an input
  pinMode(6, INPUT);
  // set LED pins to outputs and ultrasonic trigger pin
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(7, OUTPUT);
}

// main loop
void loop()
{
  // read in the ultrasonic distance
  int dist = ultrasonic_read(7, 6);

  // show how far the object is detected between 0 and 150 and output the data to the serial monitor
  if (dist <= 20) 
  {
    LED_control(0, 0, 0, 1);
    output(dist, 1, 0, 0, 0);
  }
  else if (dist <= 50) 
  {
    LED_control(0, 0, 1, 1);
    output(dist, 1, 1, 0, 0);
  }
  else if (dist <= 100) 
  {
    LED_control(0, 1, 1, 1);
    output(dist, 1, 1, 1, 0);
  }
  else if (dist <= 150) 
  {
    LED_control(1, 1, 1, 1);
    output(dist, 1, 1, 1, 1);
  }
  else 
  {
    LED_control(0, 0, 0, 0);
    output(dist, 0, 0, 0, 0);
  }
  delay(500); // wait half a second
}