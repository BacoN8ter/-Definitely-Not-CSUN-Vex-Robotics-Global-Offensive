
#include <Encoder.h>

Encoder test(2, 3);

//process variance
#define Q 0.01
//measurement variance
#define R 0.001

float xhat;      //a posteri estimate of x
float P;         //a posteri error estimate
float xhatMinus; //a priori estimate of x
float PMinus;    //a priori error estimate
float K;         //gain of blending factor
float z;         //measurement

void setup()
{
  Serial.begin(9600);
  
  xhat = 0;
  P = 1;
}

void loop()
{
   //Sensor Reading
   z = test.read();
   
   //time update
   xhatMinus = xhat;
   PMinus = P + Q;
   
   //measurement
   K = PMinus / (PMinus + R);
   xhat = xhatMinus + K * (z - xhatMinus);
   P = (1 - K) * PMinus;
   
   Serial.println(xhat);
   delay(25);
}



