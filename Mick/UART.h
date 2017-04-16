/////////////////////////////////////////////////////////////////////////////////////////////////////
//
// VEX Cortex UART
//
//
/////////////////////////////////////////////////////////////////////////////////////////////////////
task UARTReceive();
task Parse();
int nRcvIndex = 0;
int rcvChar;
const int messageSize = 128;
//const int maxMessageLength = 11;
char rcvChars[messageSize]; // Keep buffer of last 23 characters received.
char parseChars[messageSize];
int motorPowers[10];
char powerChars[5];
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
			wait1Msec(1);
			continue;
		}
		else
		{
			rcvChars[nRcvIndex] = rcvChar;
			++nRcvIndex;
			if(rcvChar == '}')
			{
				memcpy(parseChars, rcvChars, messageSize);
				startTask(Parse);
			}

			if (nRcvIndex >= sizeof(rcvChars))
			{
				nRcvIndex = 0;
			}
		}
	}
}

struct bufferData{
	bool contained;
	int startIndex;
	int endIndex;
};


task Parse()
{

	bufferData data;
	for(int i = 0; i < messageSize; i++)
	{
		if(parseChars[i] == '{')
		{
			data.startIndex = i;
		}
		if(parseChars[i] == '}')
		{
			data.endIndex = i;
			break;
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
	  	if(parseChars[i] == '(')
	  	{
	  		for(int i = 0; i < 5; i++)
				{
					if(i < 3) portChars[i] = '\0';
					powerChars[i] = '\0';
				}
	  		i++;

	  		int index = 0;
	  		while(i < messageSize && parseChars[i] != ':' && index < 3)
	  		{
	  			char tempChar = parseChars[i];
	  			portChars[index] = tempChar;
	  			index++;
	  			i++;
	  		}

	  		int portNumber = atoi(portChars);

	  		i++;
	  		index = 0;

	  		while(i < messageSize && (parseChars[i] == 0x2D || (parseChars[i] >= 0x30 && parseChars[i] <= 0x39)) && index < 5)
	  		{
	  			powerChars[index] = parseChars[i];
	  			index++;
	  			i++;
	  		}
	  		if(portNumber >= 0 && portNumber < 10)
	  		{
					if(i >= messageSize) break;

	  			int powerNumber = atoi(powerChars);
					motorPowers[portNumber] = powerNumber;
					nRcvIndex = 0;

					motor[portNumber] = motorPowers[portNumber];
				}
	  	}
		}
	}

}

void configureSerial()
{
	//configureSerialPort(uartTwo, uartUserControl);
	//setBaudRate(uartTwo, baudRate19200);
	//clear buffer

	startTask(UARTReceive);
}
