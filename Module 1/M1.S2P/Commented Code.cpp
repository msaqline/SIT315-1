// Assign the button and LED pins as constants
const uint8_t BTN_PIN = 2;
const uint8_t LED_PIN = 13;

// set button and LED initial states to low
uint8_t buttonPrevState = LOW;
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
}

// Ran after the setup and loops forever
void loop()
{
  // Read the value of the button pin and store in the 
  // button state
  uint8_t buttonState = digitalRead(BTN_PIN);
  
  // Print to the serial the button state, previous state
  // and LED state
  Serial.print(buttonState);
  Serial.print(buttonPrevState);
  Serial.print(ledState);
  Serial.println("");
  
  
  // If the button state has changed, change the LED state
  // and output the changed state to the LED pin
  if(buttonState != buttonPrevState)
  {
    ledState = !ledState;
    digitalWrite(LED_PIN, ledState);
  }
  
  // Set the current button state to previous button state 
  // for next loop
  buttonPrevState = buttonState;
    
  // Pause the loop for 500 milli seconds
  delay(500);
}
