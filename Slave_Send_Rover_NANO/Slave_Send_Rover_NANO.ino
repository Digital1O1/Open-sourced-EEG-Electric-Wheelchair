//BLE Variables
#include <SoftwareSerial.h>
#define BT_RX 2
#define BT_TX 3
SoftwareSerial slave_B(BT_RX, BT_TX); //RX||TX

//Probably not needed
const byte SIZE = 32;

const byte numChars = 128;//63; //1 Character = 1 Byte | Spaces are not "included" in this buffer | Go over buffer --> No values echoed back || REPLACE THIS WITH VECTOR IF YOU HAVE TIME
// Reference : https://www.lettercount.com/ || ---------------------------------------Action Type :Action Power : == 67 Total Characters --> Get rid of four spaces --> 63

//Parsing stuff
char receivedChars[numChars];
char tempChars[numChars];

//Bluetooth Stuff
char sent_String[SIZE];

// variables to hold the parsed data
int action_Type, action_Power = 0;

boolean newData = false;


String data;

//===================================================================================================================================================================================================================================

void setup()
{
  Serial.begin(115200);
  slave_B.begin(115200);

}

//===================================================================================================================================================================================================================================

void loop()
{
  recieveData();
  if (newData == true)
  {
    strcpy(tempChars, receivedChars); // this temporary copy is necessary to protect the original data
    // because strtok() used in parseData() replaces the commas with \0
    parseData();
    echoSerialValues();               //Sent to C++ Program since it's expecting something back
    doStuffWithEEGData();
    newData = false;
  }

}

//===================================================================================================================================================================================================================================

void recieveData()
{
  static boolean recvInProgress = false;
  static byte index = 0;
  char startMarker = '<';
  char endMarker = '>';
  char incoming_data;

  while (Serial.available() > 0 && newData == false)
  {
    incoming_data = Serial.read();

    if (recvInProgress == true)
    {
      if (incoming_data != endMarker)
      {
        receivedChars[index] = incoming_data;
        index++;
        if (index >= numChars)
        {
          index = numChars - 1;
        }
      }
      else
      {
        receivedChars[index] = '\0'; // terminate the string
        recvInProgress = false;
        index = 0;
        newData = true;
      }
    }

    else if (incoming_data == startMarker)
    {
      recvInProgress = true;
    }
  }
//  else
//  {
//    Serial.println("No connection with C++ program...");
//  }
}

//===================================================================================================================================================================================================================================
// split the data into its parts
void parseData()
{

  char * strtokIndx; // this is used by strtok() as an index

  strtokIndx = strtok(tempChars, ",");     // get the first part - the string
  action_Type = atof(strtokIndx);          // convert this part to a float

  strtokIndx = strtok(NULL, ">");          // this continues where the previous call left off
  action_Power = atof(strtokIndx);

}

//===================================================================================================================================================================================================================================
void echoSerialValues()
{
  // const byte numChars = 63; //1 Character = 1 Byte | Spaces are not "included" in this buffer | Go over buffer --> No values echoed back
  // the "int" values aren't included in the count

  Serial.println("--------------------------------------------------------------------------------------------");

  Serial.print("Action Type : ");
  Serial.println(action_Type);
  Serial.print("Action Power : ");
  Serial.println(action_Power);
}
//===================================================================================================================================================================================================================================
void doStuffWithEEGData()
{
  data = '<' + String(action_Type) + ',' + String(action_Power) + '>';
  data.toCharArray(sent_String, SIZE);
  //Serial.println(sent_String);
  slave_B.write(sent_String);
}
