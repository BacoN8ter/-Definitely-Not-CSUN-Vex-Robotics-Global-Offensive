/////////////////////////////////////////////////////////////////////////////////////////////////////
//
// VEX Cortex UART
//
//
/////////////////////////////////////////////////////////////////////////////////////////////////////
task UARTReceive();
void Parse();
int nRcvIndex = 0;
int rcvChar;
const int messageSize = 256;
//const int maxMessageLength = 11;
char rcvChars[messageSize]; // Keep buffer of last 23 characters received.
int motorPowers[10];
char powerChars[4];
char portChars[3];


// // Setup the UART ports
// configureSerialPort(uartTwo, uartUserControl);
// setBaudRate(uartTwo, baudRate115200);
// startTask(UARTReceive);

task UARTReceive()
{
	//sendChar(uartTwo, '*');
	//while(!bXmitComplete(uartTwo))
	//{
	//	wait1Msec(50);
	//}

	while (true)
	{
		// Loop forever getting characters from the "receive" UART. Validate that they arrive in the expected
		// sequence.

		rcvChar = getChar(uartTwo);
		if (rcvChar == -1)
		{
			// No character available

			wait1Msec(3); // Don't want to consume too much CPU time. Waiting eliminates CPU consumption for this task.
			continue;
		}
		rcvChars[nRcvIndex] = rcvChar;
		++nRcvIndex;
		if(rcvChar == '}')
		{
			Parse();
		}

		if (nRcvIndex >= sizeof(rcvChars))
		{
			nRcvIndex = 0;


		}

	}
}

struct bufferData{
	bool contained;
	int startIndex;
	int endIndex;
};


void Parse()
{

	bufferData data;
	for(int i = 0; i < messageSize; i++)
	{
		if(rcvChars[i] == '{')
		{
			data.startIndex = i;
		}
		if(rcvChars[i] == '}')
		{
			data.endIndex = i;
		}
	}

	if(data.endIndex > data.startIndex)
	{
		data.contained = true;
	}

	if(data.contained)
	{
	//{(motorPort:power) ( ... ) ...     }
		for(int i = data.startIndex; i < data.endIndex; i++)
		{
	  	if(rcvChars[i] == '(')
	  	{
	  		for(int i = 0; i < 4; i++)
				{
					if(i < 3) portChars[i] = '\0';

					powerChars[i] = '\0';
				}
	  		i++;

	  		int index = 0;
	  		while(i < messageSize && rcvChars[i] != ':')
	  		{
	  			char tempChar = rcvChars[i];
	  			portChars[index] = tempChar;
	  			index++;
	  			i++;
	  		}

	  		int portNumber = atoi(portChars);

	  		i++;
	  		index = 0;

	  		while(i < messageSize && rcvChars[i] != ')')
	  		{
	  			powerChars[index] = rcvChars[i];
	  			index++;
	  			i++;
	  		}
				if(i >= messageSize) break;
	  		int powerNumber = atoi(powerChars);
				motorPowers[portNumber - 1] = powerNumber;
				nRcvIndex = 0;
	  	}
		}
	}

}

void configureSerial()
{
	configureSerialPort(uartTwo, uartUserControl);
	setBaudRate(uartTwo, baudRate19200);
	startTask(UARTReceive);
}
