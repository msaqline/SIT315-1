// C++ code

// set up the pins to be used
const int button_pin = 2;
const int LED_pin = 7;

// set up global distance variable
int LED = 0;
int button = 0;

// function to output data to serial
void output(int LED)
{  
  // output the switch status
  Serial.println("Button pressed");
  // output the status of LED
  Serial.print("LED: ");
  Serial.println(LED);
  Serial.println();
}

// setup function ran before anything else
void setup()
{
  // start the serial
  Serial.begin(9600);
  // set the pot pin to an input
  pinMode(button_pin, INPUT);
  // set LED pins to outputs
  pinMode(LED_pin, OUTPUT);
  
  attachInterrupt(digitalPinToInterrupt(button_pin), button_ISR, RISING);
}

// main loop
void loop()
{
  delay(5000);
  // doign work
}

void button_ISR()
{ 
  LED = not LED;
  digitalWrite(LED_pin, LED);
  output(LED);
}
