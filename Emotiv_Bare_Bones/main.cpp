#include <iostream>
#include <map>
#include <sstream>
#include <cassert>
#include <stdexcept>
#include <cstdlib>
#include <stdio.h>
#include <conio.h>
#include <sstream>
#include <map>
#include <iomanip>
#include <thread>
#include <string>
#include <fstream>
#include <chrono>

/* ============================ [Emotiv Header Files] ============================ */
#include "IEmoStateDLL.h"
#include "Iedk.h"
#include "IedkErrorCode.h"
#include "SerialPort.h"
#include "MentalCommandControl.h"
#include "EmotivCloudClient.h"

using namespace std;

/* ============================ [Global Decalred Variables] ============================ */

EmoEngineEventHandle eEvent = IEE_EmoEngineEventCreate();
EmoStateHandle eState = IEE_EmoStateCreate();

int main(int argc, char** argv)
{
	//Change
	for (int i = 0; i < 10; i++)
		cout << i << endl;
	IEE_EngineDisconnect();
	IEE_EmoStateFree(eState);
	IEE_EmoEngineEventFree(eEvent);
	return 0;
}
/*
	To add stuff to online GitHub

	Open Team explorer --> Click on Green Plug --> Click on whatever Repo you're working on --> Setting
	--> Repo setting --> Ignore & Attribute Files --> on both Ignore/Attribute file click on 'Add' --> /.gitignore should pop up

	test

*/