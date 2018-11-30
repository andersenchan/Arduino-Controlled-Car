
/* Program Name: Calculator
   Author: Andy Chan
   Date Started: 1/5/15
   Date of Last Modification: 1/8/15
   Purpose: input two values and an operator and outputs the solution
   
   Materials:
    -Arduino Mega 2560 Microcontroller
	-Arduino LCM1602 LCD Screen
	-15 PTM buttons
	-Power supply (any power supply such as a battery will be sufficient)
	-Optional: a casing for the device that will protect and support the components
	-Wires, solder, etc
*/

//LCD
#include <FastIO.h>
#include <I2CIO.h>
#include <LCD.h>
#include <LiquidCrystal.h>
#include <LiquidCrystal_I2C.h>
#include <LiquidCrystal_SR.h>
#include <LiquidCrystal_SR2W.h>
#include <LiquidCrystal_SR3W.h>

//wire
#include <Wire.h>

//myLibrary
#include <Button.h>
//#include  "Button.cpp"
   
   //random pins for now
   int inputPins[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14};
   //int inputPins[] = {22, 24, 26, 28, 30, 32, 34, 36, 38, 40, 42, 44, 46, 48, 50, 52};
   //int screen = 22;

   String userInput;
   String result;
   
   LiquidCrystal_I2C lcd(0x27, 2,1,0,4,5,6,7,3,POSITIVE);
   
   Button buttons[sizeof(inputPins)];
   
   void setup(){
      
     Serial.begin(9600);
     
     lcd.begin(16, 2);// set up the LCD's number of columns and rows: 
     
     for(int i = 0; i < sizeof(inputPins); i++)
       pinMode(inputPins[i], INPUT);
       
     //pinMode(screen, OUTPUT);
     
     //initialize variables
     userInput = "";
     result = "";
     
     /* initialize buttons */
     
     //the first 10 buttons are the numbers 0-9
     for(int i = 0; i < 10; i++){
       buttons[i].init(inputPins[i], "" + i, false);
     }
     
     //operations
     buttons[10].init(inputPins[10], "+", true);
     buttons[11].init(inputPins[11], "-", true);
     buttons[12].init(inputPins[12], "*", true);
     buttons[13].init(inputPins[13], "/", true);
     buttons[14].init(inputPins[14], "=", true);
   }
   
   void loop(){
   
     //scroll through to check each button if it is being pressed
     for(int i = 0; i < sizeof(buttons); i++){
         
       //if user presses buttons[i], or the current button
       //if(digitalRead(buttons[i].getPin()) == HIGH)
         if(analogRead(buttons[i].getPin()) >= 1023){

         //testing
         Serial.println("This button has been pressed: " + buttons[i].getSymbol() + buttons[i].getPin());
         
         //add user input to userInput variable
         userInput += buttons[i].getSymbol();// + " ";

         //wait until user lets go
         //while(digitalRead(buttons[i].getPin()) == HIGH)
           while(analogRead(buttons[i].getPin()) >= 1023){
           
           //JUST do this if youre still pressing the button, not anything else
           draw(userInput);
           
           Serial.println("Stop pressing the button");
         }
       }

       //equals sign = evaluate
       if(buttons[i].getSymbol() == "="){
         result = evaluate(userInput);
         userInput = "";//reset the userInput
       }
       
       //once user lets go, do everything else as well
       
       //if userLength exists, draw it
       if(userInput.length() > 0){
         draw(userInput);
         Serial.println("User inputn is: " + userInput); 
       }
       else 
         draw(result);

     }
   }
   
   void draw(String userInput){
     
     lcd.clear();
     lcd.setCursor(0, 0);
     lcd.print(userInput);
     
   }
   
   String evaluate(String userInput){
      
     String value[2];// = {"", ""};//the two values that will be evaluated
     int opType;//operation type
     boolean noOperationYet = true;//only one operation is allowed for now
     int count = 0;//the current value position
     int result;
     
      //get the userInput one character at a time
      for(int i = 0; i < userInput.length(); i++){
        
        //the current character stored in a string
        String curr = userInput.substring(i, i+1);
        
        /* separate from two types of inputs, number and operations */
        
        //if it is a number
        if(curr.indexOf("0123456789") > -1){
          
          //consider the case where there are numbers with multiple digits
          value[count] += curr;//add the current character to the value
        }
        
        //if it is an operation
        else{ 
          //only one operation is allowed for now
          if(noOperationYet)
          count++;//the operation signals that the first number has ended
          
          //determine the type of operation
            if(curr.equals("+")) opType = 0;
            else if(curr.equals("-")) opType = 1;
            else if(curr.equals("*")) opType = 2;
            else if(curr.equals("/")) opType = 3;

          noOperationYet = false;
        }
      }

      //evaluate depending on the operation type
      switch(opType){
        case 0: result = value[0].toInt() + value[1].toInt(); break;
        case 1: result = value[0].toInt() - value[1].toInt(); break;
        case 2: result = value[0].toInt() * value[1].toInt(); break;
        case 3: result = value[0].toInt() / value[1].toInt(); break;
      }
      return String(result);
   }
   
   
   
