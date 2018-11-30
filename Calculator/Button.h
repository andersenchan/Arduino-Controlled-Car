/* Button.h
   by Andy Chan
*/

#ifndef Button_h 
#define Button_h 

#include "Arduino.h"

class Button{
  public:
    Button();
    void init(int _pin, String _symbol, boolean _operation);
    String getSymbol();
    boolean isAnOperation();
    int getPin();
  private:
    int pin;
    String symbol;
    boolean operation;
};

#endif
