#include <Windows.h>
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <string>
using namespace std;

/*
	IMPORTANT NOTE WHEN USING VISUAL STUDIO 2019 V 16.6.2

	When running this example straight from this site : https://www.xanthium.in/Serial-Port-Programming-using-Win32-API

	You HAVE to add/cast (LPCWSTR) to the ComPortName to avoid throwing the error 

	E0167  C++ argument of type is incompatible with parameter of type "LPCWSTR"

	Reference link to Stackoverflow solution is found here ---> https://stackoverflow.com/questions/33001284/incompatible-with-parameter-of-type-lpcwstr
*/
  
int main()
{
	HANDLE hComm;                          // Handle to the Serial port
	char   ComPortName[] = "\\\\.\\COM24"; // Name of the Serial port(May Change) to be opened,
	BOOL   Status;
	printf("\n\n +==========================================+");
	printf("\n |  Serial Transmission (Win32 API)         |");
	printf("\n +==========================================+\n");

	/*----------------------------------- Opening the Serial Port --------------------------------------------*/

	hComm = CreateFile((LPCWSTR)ComPortName,                       // Name of the Port to be Opened
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
		printf("\n   Error! in Setting Time Outs");
	else
		printf("\n\n   Setting Serial Port Timeouts Successfull");


	/*----------------------------- Writing a Character to Serial Port----------------------------------------*/
	char   lpBuffer[] = "A";		       // lpBuffer should be  char or byte array, otherwise write wil fail
	DWORD  dNoOFBytestoWrite;              // No of bytes to write into the port
	DWORD  dNoOfBytesWritten = 0;          // No of bytes written to the port

	dNoOFBytestoWrite = sizeof(lpBuffer); // Calculating the no of bytes to write into the port

	Status = WriteFile(hComm,               // Handle to the Serialport
		lpBuffer,            // Data to be written to the port 
		dNoOFBytestoWrite,   // No of bytes to write into the port
		&dNoOfBytesWritten,  // No of bytes written to the port
		NULL);

	if (Status == TRUE)
		printf("\n\n    %s - Written to %s", lpBuffer, ComPortName);
	else
		printf("\n\n   Error %d in Writing to Serial Port", GetLastError());

	CloseHandle(hComm);//Closing the Serial Port
	printf("\n ==========================================\n");
	std::cin.get();
	//_getch();

	return 0;
}