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

//Data Variables
boolean newData = false;
const byte numChars = 128;
char receivedChars[numChars];
char tempChars[numChars];
int action_Type, action_Power = 0;
int data_LED = 13;

//Rover Variables


//LEFT MOTOR
int speed_Motor_A = 10;
int motor_A_pin_1 = 9;
int motor_A_pin_2 = 8;

//RIGHT MOTOR
int speed_Motor_B = 5;
int motor_B_pin_3 = 7;
int motor_B_pin_4 = 6;

void setup()
{
  pinMode(data_LED, OUTPUT);

  master_B.begin(115200);
  Serial.begin(115200);

  pinMode(speed_Motor_A, OUTPUT);
  pinMode(speed_Motor_B, OUTPUT);
  pinMode(motor_A_pin_1, OUTPUT);
  pinMode(motor_A_pin_2, OUTPUT);
  pinMode(motor_B_pin_3, OUTPUT);
  pinMode(motor_B_pin_4, OUTPUT);
}
void loop()
{
  readStartEndMarkers();
  if (newData == true)
  { // strcpy(copy destination, copy source); Link: http://www.cplusplus.com/reference/cstring/strcpy/ || THIS INCLUDE THE NULL TERMINAL = '\0'
    strcpy(tempChars, receivedChars);         // this temporary copy is necessary to protect the original data
    parseData();                              // because strtok() used in parseData() replaces the commas with \0
    //showParsedData();
    rover();
    newData = false;
  }
}
//==========================================================================================================

void readStartEndMarkers()
{
  static boolean readingValues = false;        // static = visible to only one function | variables declared as static will only be made/initialized the first time a function is called
  static byte index = 0;                       // normal local variables get created/destroyed everytime a function is called
  char startMarker = '<';                      // static variables persist beyond the function call --> preserves data between function calls
  char endMarker = '>';
  char recieve;

  if(master_B.available() > 0 && newData == false)
  {
    recieve = master_B.read();

    if (readingValues == true)
    {
      digitalWrite(data_LED, HIGH);

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

    digitalWrite(data_LED, LOW);
    //Serial.println("No incoming data...");

  }
  else
  {
    Serial.println("No connection with Master BLE...");
    delay(1000);
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
  Serial.print("<");
  Serial.print(action_Type);

  Serial.print(",");
  Serial.print(action_Power);
  Serial.println(">");
}
//==========================================================================================================

// Directional movements
void backward()
{
  digitalWrite(motor_A_pin_1, HIGH);
  digitalWrite(motor_B_pin_4, HIGH);
  digitalWrite(motor_A_pin_2, LOW);
  digitalWrite(motor_B_pin_3, LOW);
}

void forward()
{
  digitalWrite(motor_A_pin_1, LOW);
  digitalWrite(motor_B_pin_4, LOW);
  digitalWrite(motor_A_pin_2, HIGH);
  digitalWrite(motor_B_pin_3, HIGH);
}

void left()
{
  digitalWrite(motor_A_pin_1, LOW);
  digitalWrite(motor_A_pin_2, HIGH);
  digitalWrite(motor_B_pin_3, LOW);
  digitalWrite(motor_B_pin_4, HIGH);
}

void right()
{
  digitalWrite(motor_A_pin_1, HIGH);
  digitalWrite(motor_A_pin_2, LOW);
  digitalWrite(motor_B_pin_3, HIGH);
  digitalWrite(motor_B_pin_4, LOW);
}

void stop()
{
  digitalWrite(motor_A_pin_1, LOW);
  digitalWrite(motor_B_pin_4, LOW);
  digitalWrite(motor_A_pin_2, LOW);
  digitalWrite(motor_B_pin_3, LOW);
}

void increase_speed()
{
    for (int i = 0; i < 256; i++)
  {
    //Serial.print("Speed Forward : "); Serial.println(i);
    analogWrite(speed_Motor_A, i);
    analogWrite(speed_Motor_B, i);
    delay(10);
  }
}


void decrease_speed()
{
    for (int i = 255; i > 0; i-=3)
  {
    //Serial.print("Speed Backward : "); Serial.println(i);
    analogWrite(speed_Motor_A, i);
    analogWrite(speed_Motor_B, i);
    delay(10);
  }
}
void rover()
{
  switch (action_Type)
  {
    case 2 : //Up
      {
        Serial.println("========= FORWARD =========");
        forward();
        increase_speed();
        decrease_speed();
        break;
      }
    case 4 : //Down
      {
        Serial.println("========= BACKWARD =========");
        backward();
        increase_speed();
        decrease_speed();
        break;
      }
    case 32 : //Left
      {
        Serial.println("========= LEFT =========");
        left();
        increase_speed();
        decrease_speed();
        break;
      }

    case 64 : //Right
      {
        Serial.println("========= RIGHT =========");
        right();
        increase_speed();
        decrease_speed();
        break;
      }

    default:
    {
      Serial.println("Waiting for signal....");
      stop();
    }
    
  }

}
