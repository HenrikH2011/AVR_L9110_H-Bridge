
/* STARTUP TEST
 * Blink
 * Turns on an LED on for n second,
 * then off for n second, repeatedly.
*/

// ---------------------- L9110 H-Bridge START ---------------
/*
  L9110H motor-Driver-Module
  made on nov 2022
  by Henrik Hansen
  
*/

#include <Arduino.h>

const byte straight_pin = 5;  // #1 L9110 PIN 7 / Arduino PIN 5 / AVR IC-PIN 11, AVR Code PIN PD5 - Switch Turnout Straight
const byte turn_pin = 6;  // #1 L9110 PIN 6 / Arduino PIN 6 / AVR IC-PIN 12, AVR Code PIN PD6 - Switch Turnout Turn

const byte straight_LED = 12; // LED for turnout position = straight
const byte turn_LED = 11;  // LED for turnout position = turn

const byte push_buttom_pin = 2; // INT0 / switching motor direction / AVR IC-PIN 18, AVR Code PIN PB4
const byte blink_LED_pin = 13; // LED test blink / Arduino PIN 13 / AVR IC-PIN 19, AVR Code PIN PB5

volatile bool toggle_state = false; // toogle_state: true = turnout position straight / false = turnout position turn

// ------ Define Function ------
void stop() //function of stop
{              
   for (int i = 0; i <= 7; i++) 
   {
    delayMicroseconds(16383); // Only dealyMicroseconds will work with ISR call
   }

  digitalWrite(straight_pin, LOW);
  digitalWrite(turn_pin, LOW);
}

void turnout_straight() //function of forward 
{          
  digitalWrite(turn_pin, LOW);
  digitalWrite(straight_pin, HIGH);
  digitalWrite(turn_LED, LOW);
  digitalWrite(straight_LED, HIGH);
  
  stop(); // Stop motor
}

void turnout_turn() //function of backward
{         
  digitalWrite(straight_pin, LOW);
  digitalWrite(turn_pin, HIGH);
  digitalWrite(straight_LED, LOW);
  digitalWrite(turn_LED, HIGH);
  
  stop(); // Stop motor
}

void check_turnout() // function interrupt call
{
  if (digitalRead(push_buttom_pin) == LOW)
  {
    if (toggle_state == true)
    {
      turnout_turn();
      toggle_state = !toggle_state; 
    }

    else
    {
      turnout_straight();
      toggle_state = !toggle_state;
    }

    // delayMicroseconds(50000);
  }
  
}

// ------- Define Function END ---------------

void setup() 
{

  pinMode(blink_LED_pin, OUTPUT); // Arduino PIN 13 / AVR IC-PIN 19, AVR Code PIN PB5
  pinMode(straight_pin, OUTPUT);
  pinMode(straight_LED, OUTPUT);
  pinMode(turn_pin, OUTPUT);
  pinMode(turn_LED, OUTPUT);
  pinMode(push_buttom_pin, INPUT);
  
  digitalWrite(blink_LED_pin, LOW);

  turnout_straight(); // initalisere turnout to straight position
  toggle_state = true;

  attachInterrupt(digitalPinToInterrupt(push_buttom_pin), check_turnout, FALLING);

  Serial.begin(9600); // opens serial port, sets data rate to 9600 bps

  Serial.println("select direction of movement");
  Serial.println("Push Buttom to toggle direction");
  Serial.println("Motor run for n_msek.");

   // Blink LED Arduino PIN 13 ---------------------------
    // turn the LED on (HIGH is the voltage level)
  digitalWrite(blink_LED_pin, HIGH); // ÆNDRE TIL STRAIGHT_LED OG TURN_LED FOR HELE TEST SEKVENSEN NEDEFTER
  // wait for a second
  delay(500);
  // turn the LED off by making the voltage LOW
  digitalWrite(blink_LED_pin, LOW);
   // wait for a second
  delay(500);
    // turn the LED on (HIGH is the voltage level)
  digitalWrite(blink_LED_pin, HIGH);
  // wait for a second
  delay(500);
  // turn the LED off by making the voltage LOW
  digitalWrite(blink_LED_pin, LOW);
   // wait for a second
  delay(500);

  // END BLINK TEST -------------------------------------

}


void loop() // *****************************
{

  // Blink LED Arduino PIN 13 ---------------------------
    // turn the LED on (HIGH is the voltage level)
  digitalWrite(blink_LED_pin, HIGH);
  // wait for a second
  delay(1000);
  // turn the LED off by making the voltage LOW
  digitalWrite(blink_LED_pin, LOW);
   // wait for a second
  delay(1000);
    // turn the LED on (HIGH is the voltage level)
  digitalWrite(blink_LED_pin, HIGH);
  // wait for a second
  delay(1000);
  // turn the LED off by making the voltage LOW
  digitalWrite(blink_LED_pin, LOW);
   // wait for a second
  delay(1000);

  // END BLINK TEST -------------------------------------
 

  // serial print ---------------------------------------
  Serial.println("select direction of movement");
  Serial.println("Push Button to change direction");
  Serial.println("Motor run for 20msek.");
  Serial.println("******");
  Serial.println(" ");

  if (toggle_state == false)
  {
    Serial.println("Turnout status: trun ");
  }

  if (toggle_state == true)
  {
    Serial.println("Turnout status: straight ");
  }
  Serial.println(" ");
  Serial.println(" ");

  // END serial print -------------
  delay(1000);
  
}