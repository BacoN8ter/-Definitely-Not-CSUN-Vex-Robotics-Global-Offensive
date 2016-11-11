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
const int messageSize = 22;
const int maxMessageLength = 11;
char rcvChars[messageSize]; // Keep buffer of last 23 characters received.
int messageStart = -1;



// // Setup the UART ports
// configureSerialPort(uartTwo, uartUserControl);
// setBaudRate(uartTwo, baudRate115200);
// startTask(UARTReceive);

task UARTReceive()
{
	while (true)
	{
		// Loop forever getting characters from the "receive" UART. Validate that they arrive in the expected
		// sequence.

		static int nLastRcvChar = 0;

		rcvChar = getChar(uartTwo);
		if (rcvChar == -1)
		{
			// No character available

			wait1Msec(3); // Don't want to consume too much CPU time. Waiting eliminates CPU consumption for this task.
			continue;
		}
		++nLastRcvChar;
		nLastRcvChar %= 256;

		nLastRcvChar = rcvChar;
		rcvChars[nRcvIndex] = rcvChar;
		++nRcvIndex;
		if (nRcvIndex >= sizeof(rcvChars))
		{
			nRcvIndex = 0;

			Parse();
		}

	}
}




void Parse()
{
	/*
	{^(yaw:#######)}

	*/
	messageStart = -1;
	bool messageExists = false;

	for(int i = 0; i < messageSize; i++)
	{

		if(rcvChars[i] == '}' && i > messageStart && messageStart != -1)
		{
			messageExists = true;
			break;
		}
		else if(rcvChars[i] == '{')
		{
			messageStart = i;
		}

	}

	if(messageExists)
	{
		for(int i = messageStart; i < messageSize - messageStart; i++)
		{

		}
	}
}

void configureSerial()
{
	configureSerialPort(uartTwo, uartUserControl);
	setBaudRate(uartTwo, baudRate19200);
	startTask(UARTReceive);
}
