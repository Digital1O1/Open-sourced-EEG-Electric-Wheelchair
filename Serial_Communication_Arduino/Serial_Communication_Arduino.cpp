#include <conio.h>
#include <windows.h>
#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
#include <string.h>
#include <stdio.h>
#include <sstream>
#include <ctime>
#include <cstdlib>
#include <time.h>
#include <chrono>
#include <stdlib.h> 

#include "SerialPort.h"
#include "IEmoStateDLL.h"
#include "Iedk.h"
#include "IedkErrorCode.h"
using namespace std;

const int SAMPLE = 5; //5 --> Original || 10 --> Significantly smaller values
double alphaArray[SAMPLE], thetaArray[SAMPLE], gammaArray[SAMPLE], low_betaArray[SAMPLE], high_betaArray[SAMPLE];
double mean_alpha, mean_theta, mean_gamma, mean_low_beta, mean_high_beta,random_data1,random_data2 = 0;
double alpha, low_beta, high_beta, gamma, theta,
AF3, AF4, T7, T8, Pz = 0;

/*
	[]=================================================================== NOTES FROM 6/20/20 ===================================================================[]

	*** IMPORTANT NOTE WHEN USING VISUAL STUDIO 2019 V 16.6.2 ***

	When running this example straight from this site : https://www.xanthium.in/Serial-Port-Programming-using-Win32-API

	To make this work with VS 16.6.2 go to --> Project --> 'Project Name' properties --> Configuration Properties --> Character Set --> 
	select 'Use Multi-Byte Character Set'

	'Static Casting' (LPCWSTR) to the ComPortName won't work for some reason, and I didn't want to vest more time to figuring out why.

	Reference link to Stackoverflow solution is found here ---> https://stackoverflow.com/questions/33001284/incompatible-with-parameter-of-type-lpcwstr
*/
  
int main()
{
	/*-----------------------------------ESTABLISH SERIAL COMMUNICATION HERE--------------------------------------------*/


	/*-----------------Wrtie Variables-----------------*/

	HANDLE hComm;							// Handle to the Serial port
	char   ComPortName[] = "\\\\.\\COM7";	// Name of the Serial port(May Change) to be opened,
	BOOL   Status;							// Status of the various operations 
	DWORD  dwEventMask;						// Event mask to trigger
	DWORD  dNoOFBytestoWrite;				// No of bytes to write into the port
	DWORD  dNoOfBytesWritten = 0;			// No of bytes written to the port
	srand(time(NULL));						// Dummy data to be sent to Arduino

	/*-----------------Read Variables-----------------*/

	char  TempChar;							// Temperory Character
	char  SerialBuffer[256];				// Buffer Containing Rxed Data
	DWORD NoBytesRead;                      // Bytes read by ReadFile()
	int i = 0;


	printf("\n   +==========================================+");
	printf("\n   |     Serial Transmission from PC Side     |");
	printf("\n   +==========================================+\n");

	/*----------------------------------- Opening the Serial Port --------------------------------------------*/

	hComm = CreateFile(ComPortName,                       // Name of the Port to be Opened
		GENERIC_READ | GENERIC_WRITE,      // Read/Write Access
		0,                                 // No Sharing, ports cant be shared
		NULL,                              // No Security
		OPEN_EXISTING,                     // Open existing port only
		0,                                 // Non Overlapped I/O
		NULL);                             // Null for Comm Devices

	if (hComm == INVALID_HANDLE_VALUE)
		printf("\n   Error! - Port %s can't be opened", ComPortName);
	else
		printf("\n   Port %s Opened\n ", ComPortName);


	/*------------------------------- Setting the Parameters for the SerialPort ------------------------------*/

	DCB dcbSerialParams = { 0 };                        // Initializing DCB structure
	dcbSerialParams.DCBlength = sizeof(dcbSerialParams);

	Status = GetCommState(hComm, &dcbSerialParams);     //retreives  the current settings

	if (Status == FALSE)
		printf("\n   Error! in GetCommState()");

	dcbSerialParams.BaudRate = CBR_115200;      // Setting BaudRate = 9600 || Max buad rate = 115200
	dcbSerialParams.ByteSize = 8;             // Setting ByteSize = 8
	dcbSerialParams.StopBits = ONESTOPBIT;    // Setting StopBits = 1
	dcbSerialParams.Parity = NOPARITY;      // Setting Parity = None 

	Status = SetCommState(hComm, &dcbSerialParams);  //Configuring the port according to settings in DCB 

	if (Status == FALSE)
	{
		printf("\n   Error! in Setting DCB Structure");
	}
	else
	{
		printf("\n   Setting DCB Structure Successfull\n");
		printf("\n       Baudrate = %d", dcbSerialParams.BaudRate);
		printf("\n       ByteSize = %d", dcbSerialParams.ByteSize);
		printf("\n       StopBits = %d", dcbSerialParams.StopBits);
		printf("\n       Parity   = %d", dcbSerialParams.Parity);
	}

	/*------------------------------------ Setting Timeouts --------------------------------------------------*/

	COMMTIMEOUTS timeouts = { 0 };

	timeouts.ReadIntervalTimeout = 50;
	timeouts.ReadTotalTimeoutConstant = 50;
	timeouts.ReadTotalTimeoutMultiplier = 10;
	timeouts.WriteTotalTimeoutConstant = 50;
	timeouts.WriteTotalTimeoutMultiplier = 10;

	if (SetCommTimeouts(hComm, &timeouts) == FALSE)
	{
		printf("\n   Error! in Setting Time Outs");
	}
	else
	{
		printf("\n   Setting Serial Port Timeouts Successfull\n");
		printf("\n   Press any key to pause the program  \n");

	}

	/*------------------------------------ Setting WaitComm() Event   ----------------------------------------*/
	while (!_kbhit())
	{
		/*
				state = IEE_EngineGetNextEvent(eEvent);

		if (state == EDK_OK)
		{
			IEE_Event_t eventType = IEE_EmoEngineEventGetType(eEvent);
			IEE_EmoEngineEventGetUserId(eEvent, &userID);

			if (eventType == IEE_UserAdded)
			{
				printf("\n   +==========================================+");
				printf("\n   |         CONNECTION ESTABLISHED           |");
				printf("\n   +==========================================+\n");

				IEE_FFTSetWindowingType(userID, IEE_HAMMING);

				ready = true;
			}
		}
		*/

		//String that holds data being sent ot Arduino
		ostringstream data_To_Arduino;

		//Generate dummy data
		random_data1 = rand() % 20 / 2.3;
		random_data2 = rand() % 10 / 1.3;

		//Sending dummy data
		data_To_Arduino << "<" << random_data1 << "," << random_data2 << ">"<< endl;

		/*
		//Actual string being sent to Arduino
		data_To_Arduino << "<" << mean_alpha << "," << mean_theta << "," <<						
						mean_gamma << "," << mean_low_beta << "," << mean_high_beta << "," << AF3 <<
						"," << AF4 << "," << T7 << "," << T8 << "," << Pz << ">"
						<< endl;
		*/

		string stringToArduino = data_To_Arduino.str();											//Ostringstream conversion into string
		char lpBuffer[sizeof(data_To_Arduino) + 1];												//Sizing of char array based on data_To_Arduino, basing size of 
																								//stringToArduino will throw error for lpbuffer not being big enough

		//char lpBuffer[sizeof(convertedAlphaDouble) + 1];										//PROBLEM IS HERE THIS IS THE WRONG VERSION : sizeof(convertedAlphaDouble) + 1

		strcpy_s(lpBuffer, stringToArduino.c_str());											//THIS IS RIGHT FOR SOME REASON
		dNoOFBytestoWrite = sizeof(lpBuffer);													//Calculating the no of bytes to write into the port

		Status = WriteFile(hComm,																// Handle to the Serialport
			lpBuffer,																			// Data to be written to the port 
			dNoOFBytestoWrite,																	// No of bytes to write into the port
			&dNoOfBytesWritten,																	// No of bytes written to the port
			NULL);

		//----------------------Prints out values to console----------------------//
		///*
		if (Status == TRUE)
		printf("\nNumber Generated to Arduino: %s", lpBuffer);
		else
		printf("\n\n   Error %d in Writing to Serial Port", GetLastError());
		
		//*/
		/*
		// ================================================ START READ DATA PORTION ================================================ \\ 

		Status = SetCommMask(hComm, EV_RXCHAR); //Configure Windows to Monitor the serial device for Character Reception || EV_EXHAR = Any Character received
		//Create event for particular action --> ask windows to wait for event that's set by SetCommMask by using WaitCommEvent() that'll tell you wwhen the condition happens
		if (Status == FALSE)
		printf("\n\n    Error! in Setting CommMask");


		Status = WaitCommEvent(hComm, &dwEventMask, NULL); //Wait for the character to be received

		/*-------------------------- Program will Wait here till a Character is received ------------------------*/

		if (Status == FALSE)
		{
			printf("\n    Error! in Setting WaitCommEvent()");
		}
		else //If  WaitCommEvent()==True Read the RXed data using ReadFile();
		{
			//printf("\n\n    Characters Received : ");
			
			//--------------------------Where stuff is being read in and stored----------------------------------------//

			do
			{
				//--------------------------ReadFile() reads the recieved data from Serial Port----------------------------//

				Status = ReadFile(hComm, &TempChar, sizeof(TempChar), &NoBytesRead, NULL);

				//				   [1]       [2]		[3]				   [4]

			//	NOTES ABOUT READFILE FUNCTION

			//	[1] Handle to the device
			//	[2] Pointer to the buffer that gets the data being read from file or device
			//	[3] Max number of bytes to be read || used to find out number of bytes to read
			//	[4] Pointer to variable that receives the number of bytes read when using
			//	synchronous hFile parameter || Bytes successfully read by the ReadFile()

				//*/

				SerialBuffer[i] = TempChar;
				i++;

			} while (NoBytesRead > 0);

			//------------Printing the RXed String to Console----------------------//

			//printf("\n\n    ");
			int j = 0;
			for (j = 0; j < i - 1; j++)		// j < i-1 to remove the dupliated last character
			{
				printf("%c", SerialBuffer[j]);
			}

			//Clears and 'restarts' the serial buffer
			memset(SerialBuffer, 0, sizeof(SerialBuffer));
			i = 0;

			// ================================================ END READ DATA PORTION ================================================ \\ 
			//*/
		}// End of --> else //If  WaitCommEvent()==True Read the RXed data using ReadFile();
	
	}// End of --> while (!_kbhit())

	//------------Closing the Serial Port----------------------//
	CloseHandle(hComm);

	printf("\n\n+=======================================================================================+ \n");
	printf("\n   Port is closed....");

	return 0;

}