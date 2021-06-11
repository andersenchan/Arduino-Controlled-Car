# Arduino-Controlled-Car

A car that uses infrared sensors to follow a pre-determined path.

This project was part of my Gr. 11 High School Robotics class

## Detection

The path consists of a black tape, taped onto a white floor. We use 2 infrared sensors, one attached onto the left of the car and one attached onto the right of the car, and change the direction of the car depending on what the two sensors sees. For example, if both sensors sees white, then we keep going forward. If the left sensor sees black but the right sensor sees white, then the car must turn left. 

## Movement

Two motors which control plastic wheels are attached to the car. To go forward, our program sends a HIGH signal to both motors to cause them to rotate the wheels. If we want to turn, then we only send a HIGH signal to one of the motors
