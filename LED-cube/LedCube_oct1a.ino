/* Program Name: LedCube
   Author: Andy Chan
   Date Started: Sep 192014
   Purpose: to flash an LED Cube
   Chip: ATMega 2560
*/

int led[] = {22,24,26,28,30,32,34,36,38};
int order[] = {1,2,3,4,5,6};
int gnd[] = {49, 51, 53}; //gnd is the wire attatched to each layer, size is 3 since there are 3 layers in a 3^3 cube
int delayTime = 250;

int repetition = 10;//the amount of times routine 5 (the lighting of random leds) will repeat

void setup(){
  
for (int i =0; i < sizeof(led); i++)
 pinMode(led[i], OUTPUT);
 
 for (int i =0; i < sizeof(gnd); i++)
 pinMode(gnd[i], OUTPUT);
}

void loop(){

  //insert desired routines
  
  //example routine order
 
  routine1();
  routine2();
  routine3();
  routine4();
  routine5();
  routine6();
}

//sets the grounds as high and all the LEDs as low so you can start prevent unwatned things to happen, such as unwanted lighting of LEDS
void breakCircuit(){
  for (int i =0; i < 3;i++){
    digitalWrite(gnd[i], HIGH);
  }
  for (int i =0; i< 9;i++)
   digitalWrite(led[i], LOW);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//light up horizontal layer
void routine1(){
  
 //to prevent completing the circuit before we start the routine, set thegrounds as HIGH
  breakCircuit();
  
  //set all the ledsof a layer as high,since lightingup each layer at a time
  for (int i =0; i < 9;i++)
   digitalWrite(led[i], HIGH);
  
 //light layers upward
  for (int i =0; i < 3;i++){
    digitalWrite(gnd[i], LOW); //complete the circiut in this layer
    delay(delayTime);
    digitalWrite(gnd[i], HIGH);// then turn the layer off
}

 //light layers downward
  for (int i = 2; i > -1; i--){
    digitalWrite(gnd[i], LOW); 
    delay(delayTime);
    digitalWrite(gnd[i], HIGH);
}

  breakCircuit();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//light up vertical wall
void routine2(){

  breakCircuit();
  
  //set the gnd as low so it can complete the circuit at every layer
  for (int i = 0; i < 3;i++)
    digitalWrite(gnd[i], LOW);
  
  //set first 'wall' as on and all others as gnd {
  for (int i = 0; i < 3; i++)
   digitalWrite(led[i], HIGH);//set the first three leds on for the first wall
   
   //set all the other leds os off so that onlythe first wall lights up
  for (int i = 3; i < 9; i++)
   digitalWrite(led[i], LOW); 

  delay(delayTime);
    
  //}
  
  //dset second wall as on{
    
    
  //set first wall as off
  for (int i = 0; i < 3; i++)
   digitalWrite(led[i],LOW);
   
   //set second wall ashigh
  for (int i = 3; i < 6; i++)
   digitalWrite(led[i], HIGH);
   
   //set third wall as off
     for (int i = 6; i < 9; i++)
   digitalWrite(led[i], LOW);
   
   delay(delayTime);
   
   //}
   
   //set others as low, turning on only the third wall
  for (int i = 0; i < 6; i++)
   digitalWrite(led[i], LOW);
   
   //set third 'wall' as on and all others as gnd {
  for (int i = 6; i < 9; i++)
   digitalWrite(led[i], HIGH);

  delay(delayTime);
    
  
  //}
  
  //dset second wall as on{
    
    
  //set first wall as off
  for (int i = 0; i < 3; i++)
   digitalWrite(led[i],LOW);
   
   //set second wall ashigh
  for (int i = 3; i < 6; i++)
   digitalWrite(led[i], HIGH);
   
   //set third wall as off
     for (int i = 6; i < 9; i++)
   digitalWrite(led[i], LOW);
   
   delay(delayTime);
   
   //}
   
   //set first 'wall' as on and all others as gnd {
  for (int i = 0; i < 3; i++)
   digitalWrite(led[i], HIGH);//set the first three leds on for the first wall
   
   //set all the other leds os off so that onlythe first wall lights up
  for (int i = 3; i < 9; i++)
   digitalWrite(led[i], LOW); 

  delay(delayTime);
    
  //}
  
  breakCircuit();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//starburst
void routine3(){

  //declare local variables, that are only used in this subroutine
  int flickerLength = 250; //the length that the leds will flicker from one state to another
  
  //turn all the grounds as high so that nothing turns on yet that i dont want to
  breakCircuit();
  
  //first stage: turn the middle pin on
  digitalWrite(led[4], HIGH);
  digitalWrite(gnd[1], LOW);
  
  delay(delayTime);
  
//  //turn middle pin off
//  digitalWrite(led[4], LOW);
//  digitalWrite(gnd[1], HIGH);

  //2nd stage: turn on the outside layer, flicker between two states: 
  
  //for loop{turn 1 on; turn 1 off; turn 2 on; turn 2 off;}
  for(int i = 0; i < flickerLength; i++){
    
  //turning on first state{
  
  //all the gnd are low to complete the circuit
  for (int i = 0; i < 3; i++){
    digitalWrite(gnd[i], LOW);
  }
  
  //turn on all leds
  for (int i = 0; i < 9; i++){
   digitalWrite(led[i], HIGH);
  }
  
   //except for the middle pin
  digitalWrite(led[4], LOW);

  //delay for 1 millisecond, flickering between 2 states
  delay(1);
  
  //}
  
  //turning off first state
  breakCircuit();
  
  //turning on 2nd state{
    
  //gnd = low to complete the circuit;
  for (int i = 0; i < 3; i++){
    digitalWrite(gnd[i], LOW);
  }
  //turn on the middle pins for each layer, since thats what was left out in the first stage
  digitalWrite(led[4], HIGH);
  
  //make sure the middlest pin isnnt turned on at all, only the top and bottom middle pins are on
  digitalWrite(gnd[1], HIGH); 
  
  delay(1);
  
  //}
  
  //turn off at end of each routine so that nothing gets carried over
  breakCircuit();
  }
  
}//end routine 3
  
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//rotating wall routine
void routine4(){

  //turn all the grounds as grounds
  for (int i = 0; i < sizeof(gnd); i++){
    digitalWrite(gnd[i], LOW);
  }

  for (int i = 0; i < 2; i++){
  //light the rorating wall
  lightWall(1,4,7); //light on leds at position 1, 4, and 7, which are the leds that make up the centre wasll
  lightWall(0,4,8); //diagonal wall
  lightWall(3,4,5); //horizontal wall
  lightWall(2,4,6);
  //lightWall(1,4,7); //back to the start

  
  }
  breakCircuit();
}

  //light a wall on and off
  void lightWall(int x, int y, int z){
    digitalWrite(led[x], HIGH);
    digitalWrite(led[y], HIGH);
    digitalWrite(led[z], HIGH);
    delay(delayTime);
    digitalWrite(led[x], LOW);
    digitalWrite(led[y], LOW);
    digitalWrite(led[z], LOW);
  }
 
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////// 

//starTwinkle
void routine5(){//parameters for rand num so that u know how many times you want to repeat it

  for (int i = 0; i < repetition; i++){
    
    //generate a randLed, generate 2 randNums
    int randLed = random(0,9);
    int randGnd = random(0,3);

      //turn it on
      
      //lightLed(led, gnd, randLed, randGnd);
      
        //turn off the grounds
        for (int i = 0; i < 3; i++){
          digitalWrite(gnd[i], HIGH);
        }
        
        //turn off all the LEDs
        for (int i = 0; i < 9; i++){
          digitalWrite(led[i], LOW);
        }
        
        //light the LED
        digitalWrite(led[randLed], HIGH);
        digitalWrite(gnd[randGnd], LOW);
      
        delay(delayTime);
  
    }
  }

////light only a single LED, position is determined in the parameters, turning all others off
//void lightLed(int[] led, int[] gnd, int ledPos, int gndPos){
//  
//  //turn off the grounds
//  for (int i = 0; i < sizeof(gnd); i++){
//    digitalWrite(gnd[i], HIGH);
//  }
//  
//  //turn off all the LEDs
//  for (int i = 0; i < sizeof(led); i++){
//    digitalWrite(led[i], LOW);
//  }
//  
//  //light the LED
//  digitalWrite(ledPos, HIGH);
//  digitalWrite(gndPos, LOW);
//
//  delay(delayTime);
//  
//}
  
 /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////// 
 
 //count up and down
 void routine6(){
   
   //light form 0-2
   for (int i = 0; i < 3; i++){
     for (int x = 0; x < 9; x++){
       
        //lightLed(led,gnd, led[i], gnd[i]);
        
          //turn off the grounds
          for (int y = 0; y < 3; y++){
            digitalWrite(gnd[y], HIGH);
          }
          
          //turn off all the LEDs
          for (int y = 0; y < 9; y++){
            digitalWrite(led[y], LOW);
          }
          
          //light the LED
          digitalWrite(led[x], HIGH);
          digitalWrite(gnd[i], LOW);
        
          delay(delayTime);
      }
   }
   
   //light from 2-0
   for (int i = 2; i > -1; i--){
     for (int x = 8; x > -1; x--){
       
        //lightLed(led,gnd, led[i], gnd[i]);
        
          //turn off the grounds
          for (int y = 0; y < 3; y++){
            digitalWrite(gnd[y], HIGH);
          }
          
          //turn off all the LEDs
          for (int y = 0; y < 9; y++){
            digitalWrite(led[y], LOW);
          }
          
          //light the LED
          digitalWrite(led[x], HIGH);
          digitalWrite(gnd[i], LOW);
        
          delay(delayTime);
      }
   }
 }
