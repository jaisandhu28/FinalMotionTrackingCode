#include <Pixy2.h> // include the Pixy2 library
#include <Servo.h> // include the Servo library

Pixy2 pixy; // create a Pixy2 object
Servo myservo; // create a Servo object

int pos = 0; // global variable to store the current position of the servo motor

void setup()
{
  myservo.attach(9); // attach the servo to pin 9
  Serial.begin(115200); // start serial communication
  Serial.print("Starting...\n"); // print a message to the serial monitor
  pixy.init(); // initialize the Pixy2 camera
}

void loop()
{ 
  int i; 
  pixy.ccc.getBlocks(); // get the number of detected blocks

  if (pixy.ccc.numBlocks) // if there are detected blocks
  {
    Serial.print("Detected "); // print the number of detected blocks to the serial monitor
    Serial.println(pixy.ccc.numBlocks);
    for (i=0; i<pixy.ccc.numBlocks; i++) // loop through all detected blocks
    {
      Serial.print("  block "); // print block index to the serial monitor
      Serial.print(i);
      Serial.print(": ");
      pixy.ccc.blocks[i].print(); // print the details of the detected block to the serial monitor
      delay(100); // wait for a short time

      if (pos == 0){ // if the current position is 0 degrees
        if (pixy.ccc.blocks[i].m_x < 150) { // if the block is to the left of the camera
          myservo.write(45); // move the servo motor to 45 degrees
          pos = 45; // update the current position
          delay(750); // wait for the servo motor to move
        }
        else {} // do nothing
      }
      else if (pos == 45){ // if the current position is 45 degrees
        if (pixy.ccc.blocks[i].m_x < 100) { // if the block is further to the left
          myservo.write(90); // move the servo motor to 90 degrees
          pos = 90; // update the current position
          delay(750); // wait for the servo motor to move
        }
        else if (pixy.ccc.blocks[i].m_x > 200 ) { // if the block is further to the right
          myservo.write (0); // move the servo motor to 0 degrees
          pos = 0; // update the current position
          delay(750); // wait for the servo motor to move
        }
        else {} // do nothing
      }
      else if (pos == 90){ // if the current position is 90 degrees
        if (pixy.ccc.blocks[i].m_x > 150) { // if the block is to the right
          myservo.write(45); // move the servo motor to 45 degrees
          pos = 45; // update the current position
          delay(750); // wait for the servo motor to move
        } 
        else {} // do nothing
      }
    }
  }
  else { // if there are no detected blocks
    Serial.print("Right Side of the screen"); // print a message to the serial monitor
    if (pos == 90) { // if the current position is 90 degrees
      myservo.write(0); // move the servo motor to 0 degrees
      pos = 0; // update the current position
      delay (750); // wait for the servo motor to move
    }
  }
