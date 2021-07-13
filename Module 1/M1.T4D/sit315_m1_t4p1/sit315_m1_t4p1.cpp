// C++ code

// set up the pins to be used
const int switch1_pin = 12;
const int switch2_pin = 11;
const int button_pin = 2;
const int motion_pin = 3;
const int LED1_pin = 8;
const int LED2_pin = 9;
const int LED3_pin = 10;
const int LED4_pin = 7;
const int TI_LED_pin = 13;

// set up timer constants
const uint16_t timer1_start = 0; // start at zero
const uint16_t timer1_comp = 18750; // 1.2 seconds

// set up global variables
int LED1 = 0;
int LED2 = 0;
int LED3 = 0;
int LED4 = 0;
int TI_LED = 0;
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

// function to output switch data to serial
void switched_output(int LED)
{  
  // output the switch status
  Serial.println("Switch moved");
  // output the status of LED
  Serial.print("LED: ");
  Serial.println(LED);
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
  Serial.println(LED4);
  Serial.println();
}

// setup function ran before anything else
void setup()
{
  // start the serial
  Serial.begin(9600);
  
  // set the button, switch and motion sensor pins to inputs
  pinMode(button_pin, INPUT);
  pinMode(switch1_pin, INPUT);
  pinMode(switch2_pin, INPUT);
  pinMode(motion_pin, INPUT);
  
  // set LED pins to outputs
  pinMode(LED1_pin, OUTPUT);
  pinMode(LED2_pin, OUTPUT);
  pinMode(LED3_pin, OUTPUT);
  pinMode(LED4_pin, OUTPUT);
  pinMode(TI_LED_pin, OUTPUT);
  
  // reset timer 1
  TCCR1A = 0;
  
  // setting prescalar to 1024  
  TCCR1B &= ~(1 << WGM13);
  TCCR1B |= (1 << WGM12);
  
  // setting prescalar to 1024  
  TCCR1B |= (1 << CS12);
  TCCR1B &= ~(1 << CS11);
  TCCR1B |= (1 << CS10);
  
  // reset timer and assign compare value
  TCNT1 = timer1_start;
  OCR1A = timer1_comp;
  // enable compare interupt
  TIMSK1 = (1 << OCIE1A);
  
  // enable global interupts
  sei();
  
  // enable a third interupt pin
  PCICR |= 0b00000001; // enable PCMSK0 to interupt (pins 8-13)
  PCMSK0 |= 0b00011000;// enable pin 11 and 12 to interupt
  
  // set up external interrupts for button and motion sensor input
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
  delay(200);
}



// timer interrupt service routine
ISR(TIMER1_COMPA_vect)
{ 
  // reset timer
  TCNT1 = timer1_start;
  // show the main loop has been interruped
  Serial.println("\n Timer Interrupt");
  // change led status and write to ti_led pin
  TI_LED = not TI_LED;
  digitalWrite(TI_LED_pin, TI_LED);
}

// switch interrupt service routine for PORT B (pins 8-13)
ISR(PCINT0_vect)
{ 
  // show the main loop has been interruped
  Serial.println("\nInterrupted");
  
  if (digitalRead(switch1_pin) != LED2)
  {
    // change led2 status and write to led 2 pin
  	LED2 = not LED2;
  	digitalWrite(LED2_pin, LED2);
  	// output switch information
  	switched_output(LED2);
  } else if (digitalRead(switch2_pin) != LED3)
  {
    // change led3 status and write to led 3 pin
  	LED3 = not LED3;
  	digitalWrite(LED3_pin, LED3);
  	// output switch information
  	switched_output(LED3);
  }
  
  
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
  // change led3 status and write to led3 pin
  LED4 = not LED4;
  digitalWrite(LED4_pin, LED4);
  // output motion detection information
  motion_output();
}