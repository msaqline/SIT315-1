// C++ code

// set up the pins to be used
const int button_pin = 2;
const int motion_pin = 3;
const int LED1_pin = 7;
const int LED2_pin = 6;

// set up global variables
int LED1 = 0;
int LED2 = 0;
int button = 0;
int motion = 0;
int num = 0;

// function to output button data to serial
void button_output()
{  
  // output the switch status
  Serial.println("Button pressed");
  // output the status of LED
  Serial.print("LED: ");
  Serial.println(LED1);
  Serial.println();
}

// function to output motion sensor data to serial
void motion_output()
{  
  if (motion == 1)
  {
    // output the sensor status
  	Serial.println("Motion detected");
  }
  else
  {
    // output the sensor status
  	Serial.println("No motion");
  }
  
  // output the status of LED
  Serial.print("LED: ");
  Serial.println(LED2);
  Serial.println();
}

// setup function ran before anything else
void setup()
{
  // start the serial
  Serial.begin(9600);
  // set the button and motion sensor pin to an input
  pinMode(button_pin, INPUT);
  pinMode(motion_pin, INPUT);
  // set LED pins to outputs
  pinMode(LED1_pin, OUTPUT);
  pinMode(LED2_pin, OUTPUT);
  
  // set up interrupts for button and motion sensor input
  attachInterrupt(digitalPinToInterrupt(button_pin), button_ISR, RISING);
  attachInterrupt(digitalPinToInterrupt(motion_pin), motion_ISR, CHANGE);
}

// main loop
void loop()
{
  // print current number
  Serial.println(num);
  
  // increment number to show main loop running
  num += 1;
  
  // wait half a second
  delay(500);
}

// button interrupt service routine
void button_ISR()
{ 
  // show the main loop has been interruped
  Serial.println("\nInterrupted");
  // change led1 status and write to led 1 pin
  LED1 = not LED1;
  digitalWrite(LED1_pin, LED1);
  // output button information
  button_output();
}

// motion sensor interrupt service routine
void motion_ISR()
{ 
  // show the main loop has been interruped
  Serial.println("\nInterrupted");
  // update motion status
  motion = digitalRead(motion_pin);
  // change led2 status and write to led2 pin
  LED2 = not LED2;
  digitalWrite(LED2_pin, LED2);
  // output motion detection information
  motion_output();
}
