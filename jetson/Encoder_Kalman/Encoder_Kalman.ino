
#include <Encoder.h>

class Encoder_Kalman
{
  public:
    Encoder *enc;
    //process variance
    float Q = 0.01;
    //measurement variance
    float R = 0.001;

    float xhat;      //a posteri estimate of x
    float P;         //a posteri error estimate
    float xhatMinus; //a priori estimate of x
    float PMinus;    //a priori error estimate
    float K;         //gain of blending factor
    float z;         //measurement
    
    Encoder_Kalman(int,int);
    
  
  void Update()
  {
   //Sensor Reading
   z = enc->read();
   
   //time update
   xhatMinus = xhat;
   PMinus = P + Q;
   
   //measurement
   K = PMinus / (PMinus + R);
   xhat = xhatMinus + K * (z - xhatMinus);
   P = (1 - K) * PMinus;
    
  }
  
};

Encoder_Kalman::Encoder_Kalman(int A, int B)
{
  enc = new Encoder(A, B);
  xhat = 0;
  P = 1;
}

Encoder_Kalman encoder(2, 3);

void setup()
{
  
  
  Serial.begin(9600);
  
  
}

void loop()
{
   encoder.Update();
   
   Serial.println(encoder.xhat);
   delay(25);
}



