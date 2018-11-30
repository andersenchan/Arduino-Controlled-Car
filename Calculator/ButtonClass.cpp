class Button{

  int pin;
  //String id;
  String symbol;
  boolean operation;
  
  //constructor
  Button(int pin, String symbol, boolean operation){
    this.pin = pin;
    this.symbol = symbol;
    this.operation = operation;
  }
  
  //
  String getSymbol(){
    return symbol;
  }
  
  //
  boolean isAnOperation(){
    return operation;
  }
  
  int getPin(){
    return pin;
  }
}