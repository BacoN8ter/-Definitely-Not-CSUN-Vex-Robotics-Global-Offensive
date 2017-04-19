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
char floatChars[12];
bool firstPass = false;
int initialHeading = 0;

// // Setup the UART ports
// configureSerialPort(uartTwo, uartUserControl);
// setBaudRate(uartTwo, baudRate115200);
// startTask(UARTReceive);

typedef struct Sensor
{
	float roll;
	float pitch;
	float yaw; //degrees
}Sensor;

Sensor jetsonSensors;

task UARTReceive()
{
	//sendChar(uartTwo, '*');
	//while(!bXmitComplete(uartTwo))
	//{
	//	wait1Msec(50);
	//}
	while(getChar(uartTwo) != -1){}
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
	int messageType;//0 - gyro
	//1 - Object Detected
};


task Parse()
{

	bufferData data;


	for(int i = 0; i < messageSize; i++)
	{
		if(parseChars[i] == '{')
		{
			data.startIndex = i;
			if(parseChars[i+1] == '0')
			{
				data.messageType = 0;
			}
			else if(parseChars[i+1] == '1')
			{
				data.messageType = 1;
			}
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
		if(data.messageType == 0)
		{
			int count = 0;
			// 0 roll
			// 1 pitch
			// 2 yaw

			//{0 (roll,pitch, yaw)     }

			for(int i = data.startIndex; i < data.endIndex; i++)
			{

				if(parseChars[i] == '(')
				{
					memset(floatChars, '\0', 12);
					i++;
					int j = 0;
					while(parseChars[i] != ')' && j < 12)
					{
						floatChars[j] = parseChars[i];
						j++;
						i++;
					}

					switch(count)
					{
					case 0:
						jetsonSensors.yaw  = atof(floatChars);
						break;
					case 1:
						jetsonSensors.pitch = atof(floatChars);
						break;
					case 2:
						jetsonSensors.roll   = atof(floatChars);
						break;
					}
					count++;

				}
			}
		}
	}
	if(!firstPass)
	{
		firstPass = true;
		initialHeading = jetsonSensors.pitch;
	}
}

void configureSerial()
{
	//configureSerialPort(uartTwo, uartUserControl);
	//setBaudRate(uartTwo, baudRate19200);
	//clear buffer

	startTask(UARTReceive);
}
