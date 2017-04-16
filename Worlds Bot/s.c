

/* This module is for the pixy routine for the 2016-2017 VEX Robotic
   Autonomous. The algorithm is
*/

#include <SPI.h>
#include <Pixy.h>
#include <SoftwareSerial.h>

#define BUFFER_SIZE 32
#define FRAME_SKIP 10
#define MAX_PORTS 9
#define DELAY_MS 1000
#define SHORT_DELAY 100
#define S1_LOWER_HEIGHT 35
#define S1_HIGHER_HEIGHT 199
#define S2_LOWER_HEIGHT 79
#define S2_HIGHER_HEIGHT 199
Pixy pixy;

//serial variable for transmitting data
SoftwareSerial mySerial(0,1); //Rx Tx
char buf[BUFFER_SIZE];
int send_enable;
int sent_flag;
/*========================================================
  Function Status:

  ArduinoSendRoutine() - Simulation Passed, need to test Hardware
  sendDelemiter() - Need to test Hardware

  /*========================================================*/

void setup() {

  //Set Baud Rate for data transfering over serial port
  mySerial.begin(9600);
 // mySerial.begin(9600);

  while (!mySerial) {
    ;//Wait until communications are open
  }
  
  
  //Serial.print("Beginning Pixy Routine:\n");
  //pinMode(1,OUTPUT);
  //pinMode(0,INPUT);

  //Initialize pixy cam interface
  pixy.init();

  send_enable = 0;
  sent_flag = 0;
}

/********************************************************************
  Function Description: The algorithm for this function is simple.

  1) Get the blocks of data from the pixy cam
  2) Ensure the object detected by the pixy cam is valid (integrity check)
  3) If the object is valid send its information to the Arduino
*********************************************************************/
void clearBuffer(){
  int i;
 for(i = 0; i < BUFFER_SIZE; i++){
    buf[i] = ' ';
 } 
  
}

void loop() {

  //Find a way detect the an object, whether its a star or a cube
  
  static int i = 0;
  int j;

  int k = 0;
  uint16_t blocks;
  blocks = pixy.getBlocks();
    sent_flag = 0;
    //Check if any block was detected
    if (blocks) {
      i++;

      //Limit to 50 frames to prevent causing a serial issue for the pixy cam
      if (i % FRAME_SKIP == 0) {

          clearBuffer();
           //===============================================================================================
           //OLD WAY
           //===============================================================================================
         /*   if(pixy.blocks[j].height >= S1_LOWER_HEIGHT && pixy.blocks[j].height <= S1_HIGHER_HEIGHT){

              
               sprintf(buf,"XC %d ",pixy.blocks[j].x);
               //sprintf(buf,"%d",pixy.blocks[j].x);
               mySerial.write(buf);
            }*/
          //===============================================================================================
         
           //===============================================================================================
           //NEW WAY
           //===============================================================================================
           /*  if(pixy.blocks[j].height >= S1_LOWER_HEIGHT && pixy.blocks[j].height <= S1_HIGHER_HEIGHT){
               
              //0 Range
              if(pixy.blocks[j].x >= 0 && pixy.blocks[j].x <= 60){
                sprintf(buf,"XC %d ",0);
                mySerial.write(buf);
              }
              
              //1 Range
              else if(pixy.blocks[j].x > 60 && pixy.blocks[j].x <= 120){
                sprintf(buf,"XC %d ",1);
                mySerial.write(buf);
              }
              
              //2 Range
              else if(pixy.blocks[j].x > 120 && pixy.blocks[j].x <= 190){
                sprintf(buf,"XC %d ",2);
                mySerial.write(buf);
              }
              
              //3 Range
              else if(pixy.blocks[j].x > 190 && pixy.blocks[j].x <= 250){
                sprintf(buf,"XC %d ",3);
                mySerial.write(buf);
              }
              
             //4 Range
              else if(pixy.blocks[j].x > 250){
                sprintf(buf,"XC %d ",4);
                mySerial.write(buf);
              }*/
          //===============================================================================================
          
              //===============================================================================================
           //NEW WAY 2.0
           //===============================================================================================
             if(pixy.blocks[j].height >= S1_LOWER_HEIGHT && pixy.blocks[j].height <= S1_HIGHER_HEIGHT){
               
              //0 Range
              if(pixy.blocks[j].x >= 0 && pixy.blocks[j].x <= 60){
                sprintf(buf,"0");
                mySerial.write(buf);
              }
              
              //1 Range
              else if(pixy.blocks[j].x > 60 && pixy.blocks[j].x <= 120){
                sprintf(buf,"1");
                mySerial.write(buf);
              }
              
              //2 Range
              else if(pixy.blocks[j].x > 120 && pixy.blocks[j].x <= 190){
                sprintf(buf,"2");
                mySerial.write(buf);
              }
              
              //3 Range
              else if(pixy.blocks[j].x > 190 && pixy.blocks[j].x <= 250){
                sprintf(buf,"3");
                mySerial.write(buf);
              }
              
             //4 Range
              else if(pixy.blocks[j].x > 250){
                sprintf(buf,"4");
                mySerial.write(buf);
              }
          //===============================================================================================
      }
    }

 }

}




