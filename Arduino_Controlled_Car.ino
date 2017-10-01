/* Name: Andy Chan
 * Date Started: 6/27/14
 * Program Name: Arduino_Controlled_Car
 * Purpose: robot will follow black line
 * Type of Chip: Atmega328
 */
 
 //declare variables
 
 //rightfor, rightback, leftback, leftfor
 int logicPin[4] = {8, 7, 10, 9};

 //left, right
 int sensor[2] = {A4, A2}; 
 int leftSensor;
 int rightSensor;

 int delayTime = 250;

 
 
 void setup(){
 
   Serial.begin(9600);
   
   //sensors as input
   for (int i = 0; i < 2; i++)
     pinMode(sensor[i], INPUT);
     
   //output
   for (int i = 0; i < 4; i++)
     pinMode(logicPin[i],OUTPUT); 
 }
 
 void loop(){
   
   leftSensor = analogRead(sensor[0]);
   rightSensor = analogRead(sensor[1]);
   Serial.println(leftSensor);
   Serial.println(rightSensor);
    
 
    
    //   if (analogRead(sensor[0]) > 1000)//black
    //   if (analogRead(sensor[0]) < 1000)//white
 
   // white and white = move forward
   if (leftSensor < 1000 && rightSensor < 1000)
     moveForward();
     
   //white black = turn right
   if (leftSensor < 1000 && rightSensor > 1000)
     turnRight();
     
   //black white = turn left
   if (leftSensor > 1000 && rightSensor < 1000)
     turnLeft();
     
   //black black = stop, then move through int
   if (leftSensor > 1000 && rightSensor > 1000)
     StopThenMove();

 }
 
 void moveForward(){
   
   digitalWrite(logicPin[0], HIGH);
   digitalWrite(logicPin[3], HIGH);
 }
 
 void turnRight(){
   digitalWrite(logicPin[0], HIGH);
   digitalWrite(logicPin[3], LOW);
 }
 
  void turnLeft(){
   digitalWrite(logicPin[0], LOW);
   digitalWrite(logicPin[3], HIGH);
 }
 
 void StopThenMove(){
   digitalWrite(logicPin[0], LOW);
   digitalWrite(logicPin[3], LOW);
   
//   delay(delayTime);
//   
//   while (leftSensor > 1000 && rightSensor > 1000)
//   moveForward();
 }
 
