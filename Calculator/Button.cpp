/* Button.cpp
   by Andy Chan
*/

#include "Arduino.h" 
#include "Button.h"
  
  void Button::init(int _pin, String _symbol, boolean _operation){
    pin = _pin;
    symbol = _symbol;
    operation = _operation;
  }

  Button::Button(){
  }
  
  String Button::getSymbol(){
    return symbol;
  }
  
  boolean Button::isAnOperation(){
    return operation;
  }
  
  int Button::getPin(){
    return pin;
  }

