
// Assign the button and LED pins as constants
const uint8_t BTN_PIN = 2;
const uint8_t LED_PIN = 13;

// set button and LED initial states to low
uint8_t buttonState = LOW;
uint8_t ledState = LOW;

// Setup function ran once at start up
void setup()
{
  // Set the button pin as an input
  pinMode(BTN_PIN, INPUT_PULLUP);
  // Set the LED pin as an output
  pinMode(LED_PIN, OUTPUT);
  // Start the serial connection at 9600 baud rate
  Serial.begin(9600);
  // Set up an interupt on the button pin when it changes
  attachInterrupt(digitalPinToInterrupt(BTN_PIN), button_ISR, CHANGE);
}

// Ran after the setup and loops forever
void loop()
{
  // Read the value of the button pin and store in the 
  // button state
  buttonState = digitalRead(BTN_PIN);
  
  // Print to the serial the button state and LED state
  Serial.print(buttonState);
  Serial.print(ledState);
  Serial.println("");
    
  // Pause the loop for 500 milli seconds
  delay(500);
}

// Button Interupt Service Routine
void button_ISR()
{ 
  // change the LED state as the button state has changed
  ledState = !ledState;
  // Output the LEDs new state to the LED pin
  digitalWrite(LED_PIN, ledState);
}