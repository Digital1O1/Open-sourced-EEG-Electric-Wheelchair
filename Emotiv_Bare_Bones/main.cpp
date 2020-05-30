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


	IEE_EngineDisconnect();
	IEE_EmoStateFree(eState);
	IEE_EmoEngineEventFree(eEvent);
	return 0;
}