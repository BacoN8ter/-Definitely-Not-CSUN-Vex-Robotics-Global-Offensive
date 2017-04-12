/* www.chrisheydrick.com
     
   June 23 2012
   CanonicalArduinoRead write a byte to an Arduino, and then
   receives a serially transmitted string in response.
   The call/response Arduino sketch is here:
   https://gist.github.com/2980344
   Arduino sketch details at www.chrisheydrick.com
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdint.h>
#include <fcntl.h>
#include <termios.h>
#include <errno.h>
#include <sys/ioctl.h>
#include <string>

#define DEBUG 1
  
struct Quaternion
{
  float a, b, c, w;
};

Quaternion q;

void ParseQuaternion(char * buf, int bufLen)
{
  int index = 0;
  int count = 0;
  char number[10];
  
  for(int i = 0; i < bufLen; i++)
  {
    if(buf[i] != ',' && i != bufLen - 1)
    {
      number[index] = buf[i];
      index++;
    }
    else
    {
      number[index + 1] = '\0';
      switch(count)
      {

      case 0:
	q.a = atof(number); 
	printf("A:%f\n",q.a);
	break;
      case 1:
	q.b = atof(number); 
	printf("B:%f\n",q.b);
	break;
      case 2:
	q.c = atof(number); 
	printf("C:%f\n",q.c);
	break;
      case 3:
	q.w = atof(number); 
	printf("W:%f\n",q.w);
	break;
      }

      count++;
      i++;
      index = 0;
    }
  }

}

int main(int argc, char *argv[])
{
  int fd, n, i;
  const int bufSize = 128;

  char tarCmd [] = {':', 0x60, '0', '\n'};
  char Quatcmd[] = {':', '0','1' ,'\n'};
  char buf[bufSize];

  struct termios toptions;

  /* open serial port */
  fd = open("/dev/ttyACM0", O_RDWR | O_NOCTTY);
  printf("fd opened as %i\n", fd);
  
  /* wait for the Arduino to reboot */
  usleep(3500000);
  
  /* get current serial port settings */
  tcgetattr(fd, &toptions);
  /* set 9600 baud both ways */
  cfsetispeed(&toptions, B115200);
  cfsetospeed(&toptions, B115200);
  /* 8 bits, no parity, no stop bits */
  toptions.c_cflag &= ~PARENB;
  toptions.c_cflag &= ~CSTOPB;
  toptions.c_cflag &= ~CSIZE;
  toptions.c_cflag |= CS8;
  /* Canonical mode */
  toptions.c_lflag |= ICANON;
  /* commit the serial port settings */
  tcsetattr(fd, TCSANOW, &toptions);

  write(fd, &tarCmd[0], 1);
  write(fd, &tarCmd[1], 1);
  write(fd, &tarCmd[2], 1);  
  write(fd, &tarCmd[3], 1);
 
  while(true)
  {

    write(fd, &Quatcmd[0], 1);
    write(fd, &Quatcmd[1], 1);
    //write(fd, &cmd[2], 1);  
    write(fd, &cmd[3], 1);
    
    memset(buf, '\0', bufSize);
    n = read(fd, buf, bufSize);
    system("clear");
    /* insert terminating zero in the string */
    ParseQuaternion(buf, n);
    buf[n] = 0;
    
    usleep(100000);
  }
  return 0;
}
