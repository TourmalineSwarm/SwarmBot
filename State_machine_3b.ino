/*
  Phase 1A
  Question 3b

  Creates state machine with the following states: on (red), off (none), run (green), sleep (blue), diagnostic (red).
  Incorporates two push buttons.

  modified January 24 2018
  Elsa Ames, Ryan Friedman, Nate Krinsky
*/

const int RED = 10; 
const int GREEN = 11; 
const int BLUE = 12; 

const int n = 5;

// false = open, true = closed
bool switch1 = false;
bool switch2 = false;

void setup() 
{
  // initialize digital pin LED_BUILTIN as an output.
  //BLUE LED: Pin 13
  pinMode(BLUE, OUTPUT);
  //initalize to low
  digitalWrite(BLUE, LOW);
  //GREEN LED: Pin 12
  pinMode(12, OUTPUT);
  //RED LED: Pin 11
  pinMode(11, OUTPUT);
  //ON Mode: Powerup indicator
  //Flash RED lED @10Hz
  
  for(int i = 0; i < 30; i++) //does run mode for 3 seconds
  {
    digitalWrite(RED, HIGH);   // turn the LED on (HIGH is the voltage level)
    delay(100);                       // wait for a tenth of second
    digitalWrite(RED, LOW);    // turn the LED off by making the voltage LOW
    delay(100);                       // wait for a tenth of a second
  }

  //pause between states
  delay(1000);
}

// the loop function runs over and over again forever
void loop() 
{
  run(); 
}

// green led flashes twice for duty cycle of 0.5 s, then fades over 3 seconds
void run() 
{
  // enable interrupts for switches
  attachInterrupt(digitalPinToInterrupt(2), ISR_switch1, CHANGE);
  attachInterrupt(digitalPinToInterrupt(3), ISR_switch2, CHANGE);
  
  
  if (switch1 == false && switch2 == true)
  {
    //GREEN blink twice
    for(int i = 0; i < 2; i++)
    {
      digitalWrite(GREEN, HIGH);
      delay(300);
      digitalWrite(GREEN, LOW);
      delay(300);
    }
    
    // fade out from max to min in increments of 5 points:
    for (int fadeValue = 255 ; fadeValue >= 0; fadeValue -= 5) 
    {
      // sets the value (range from 0 to 255):
      analogWrite(GREEN, fadeValue);
      // wait for 30 milliseconds to see the dimming effect
      delay(30);
    }
  
    // fade in from min to max in increments of 5 points:
    for (int fadeValue = 0 ; fadeValue <= 255; fadeValue += 5) 
    {
      // sets the value (range from 0 to 255):
      analogWrite(GREEN, fadeValue);
      // wait for 30 milliseconds to see the dimming effect
      delay(30);
    }
  }

  else if (switch1 == true)
  {
    
  }
}

void diagnostic() 
{
  //blinks n times
  for(int i = 0; i < n; i++)
  {
    digitalWrite(RED, HIGH);
    delay(300);
    digitalWrite(RED, LOW);
    delay(300);
  }
  while(1);
}
  
// 
void sleep() 
{

  //blinks at 4Hz for a second
  for(int i = 0; i < 3; i++) //does run mode for 1s
  {
    digitalWrite(BLUE, HIGH);   // turn the LED on (HIGH is the voltage level)
    delay(250);                       // wait for a quarter of second
    digitalWrite(BLUE, LOW);    // turn the LED off by making the voltage LOW
    delay(250);                       // wait for a quarter of a second
  }

  //fades out
  // fade out from max to min in increments of 5 points:
  for (int fadeValue = 255 ; fadeValue >= 0; fadeValue -= 5) 
  {
    // sets the value (range from 0 to 255):
    analogWrite(BLUE, fadeValue);
    // wait for 30 milliseconds to see the dimming effect
    delay(30);
  }

  digitalWrite(BLUE, LOW);
  while(1)
  {}
  
}

// interrupt service routine when switch 1 is altered
void ISR_switch1() {
  if (digitalRead(2) == HIGH)
  {
    switch1 = true;
  }
  else if (digitalRead(2) == LOW)
  {
    switch1 = false;
  }
}

// interrupt service routine when switch 2 is altered
void ISR_switch2() {
  if (digitalRead(3) == HIGH)
  {
    switch2 = true;
  }
  else if (digitalRead(3) == LOW)
  {
    switch2 = false;
  }
  
}

