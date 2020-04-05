/*
   https://forum.arduino.cc/index.php?topic=488107.0
   https://forum.arduino.cc/index.php?topic=381796.0
   https://www.google.com/search?q=reciving+UART+serial+data+then+send+through+BLE+arduino&oq=reciving+UART+serial+data+then+send+through+BLE+arduino&aqs=chrome..69i57.11204j1j4&sourceid=chrome&ie=UTF-8
*/
//Bluetooth Variables
#include <SoftwareSerial.h>
#define BT_RX 2//8
#define BT_TX 3//9
SoftwareSerial master_B(BT_RX, BT_TX); //RX||TX || AT+ROLE1 --> AT+DISC --> AT+CONNxxxxxxx

int incoming_info = 13;
boolean newData = false;

const byte numChars = 128; //This was the problem with High Beta getting cut off
char receivedChars[numChars];
char tempChars[numChars];
const byte SIZE = 32;

int action_Type, action_Power = 0;


int redPin = 7;
int greenPin = 6;
int bluePin = 5;

void setup()
{
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);

  master_B.begin(115200);
  Serial.begin(115200);


}
void loop()
{
  readStartEndMarkers();
  if (newData == true)
  { // strcpy(copy destination, copy source); Link: http://www.cplusplus.com/reference/cstring/strcpy/ || THIS INCLUDE THE NULL TERMINAL = '\0'
    strcpy(tempChars, receivedChars);         // this temporary copy is necessary to protect the original data
    parseData();                              // because strtok() used in parseData() replaces the commas with \0
    showParsedData();
    newData = false;
  }
}
//==========================================================================================================

void setColor(int redValue, int greenValue, int blueValue)
{
  analogWrite(redPin, redValue);
  analogWrite(greenPin, greenValue);
  analogWrite(bluePin, blueValue);
}
//==========================================================================================================

void readStartEndMarkers()
{
  static boolean readingValues = false;        // static = visible to only one function | variables declared as static will only be made/initialized the first time a function is called
  static byte index = 0;                       // normal local variables get created/destroyed everytime a function is called
  char startMarker = '<';                      // static variables persist beyond the function call --> preserves data between function calls
  char endMarker = '>';
  char recieve;

  while (master_B.available() > 0 && newData == false)
  {
    recieve = master_B.read();

    if (readingValues == true)
    {
      digitalWrite(greenPin, HIGH);

      if (recieve != endMarker)
      {
        receivedChars[index] = recieve;
        index++;

        if (index >= numChars)
        {
          index = numChars - 1;
        }

      }
      else
      {
        receivedChars[index] = '\0'; // terminate the string
        readingValues = false;
        index = 0;
        newData = true;
      }
    }

    else if (recieve == startMarker)
    {
      readingValues = true;
    }

    digitalWrite(greenPin, LOW);

  }

}

void parseData()
{
  char * strtokIndx; // this is used by strtok() as an index

  strtokIndx = strtok(tempChars, ",");     // get the first part - the string
  action_Type = atof(strtokIndx);          // convert this part to a float

  strtokIndx = strtok(NULL, ">");          // this continues where the previous call left off
  action_Power = atof(strtokIndx);
}
//==========================================================================================================

void showParsedData()
{
  Serial.println("--------------------------------------------------------------------------------------------");

  //Serial.println("---------------------------------------");
  Serial.print("Action Type : ");
  Serial.println(action_Type);

  Serial.print("Action Power : ");
  Serial.println(action_Power);
}
