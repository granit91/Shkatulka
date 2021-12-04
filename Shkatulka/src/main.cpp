// программа для шкатулки в квесте на пушкинской 10
// version 1.0
#include "Arduino.h"
#include "SoftwareSerial.h"
#include "DFRobotDFPlayerMini.h"

#define gerkon1 4
#define gerkon2 6
#define gerkon3 3
#define gerkon4 7
#define gerkon5 5
#define magnit 12

int seq = 0;
uint32_t myTimer;
uint32_t myTimer1;
bool res;
uint32_t Timer;
bool track1;
bool track2;
bool track3;
bool track4;
bool track5;
bool trackfinish;

SoftwareSerial mySoftwareSerial(9, 10); // RX, TX
DFRobotDFPlayerMini myDFPlayer;
void printDetail(uint8_t type, int value);

void setup()
{
  mySoftwareSerial.begin(9600);
  Serial.begin(115200);
  pinMode (gerkon1,INPUT);
  pinMode (gerkon2,INPUT);
  pinMode (gerkon3,INPUT);
  pinMode (gerkon4,INPUT);
  pinMode (gerkon5,INPUT);
  pinMode (magnit, OUTPUT);
  digitalWrite(magnit, LOW);

  Serial.println();
  Serial.println(F("DFRobot DFPlayer Mini Demo"));
  Serial.println(F("Initializing DFPlayer ... (May take 3~5 seconds)"));
  
  if (!myDFPlayer.begin(mySoftwareSerial)) {  //Use softwareSerial to communicate with mp3.
    Serial.println(F("Unable to begin:"));
    Serial.println(F("1.Please recheck the connection!"));
    Serial.println(F("2.Please insert the SD card!"));
    while(true);
  }
  Serial.println(F("DFPlayer Mini online."));
  
  myDFPlayer.setTimeOut(5); //Set serial communictaion time out 500ms
  
  //----Set volume----
  myDFPlayer.volume(30);  //Set volume value (0~30).
}

void printDetail(uint8_t type, int value){
  switch (type) {
    case TimeOut:
      Serial.println(F("Time Out!"));
      break;
    case WrongStack:
      Serial.println(F("Stack Wrong!"));
      break;
    case DFPlayerCardInserted:
      Serial.println(F("Card Inserted!"));
      break;
    case DFPlayerCardRemoved:
      Serial.println(F("Card Removed!"));
      break;
    case DFPlayerCardOnline:
      Serial.println(F("Card Online!"));
      break;
    case DFPlayerUSBInserted:
      Serial.println("USB Inserted!");
      break;
    case DFPlayerUSBRemoved:
      Serial.println("USB Removed!");
      break;
    case DFPlayerPlayFinished:
      Serial.print(F("Number:"));
      Serial.print(value);
      Serial.println(F(" Play Finished!"));
      break;
    case DFPlayerError:
      Serial.print(F("DFPlayerError:"));
      switch (value) {
        case Busy:
          Serial.println(F("Card not found"));
          break;
        case Sleeping:
          Serial.println(F("Sleeping"));
          break;
        case SerialWrongStack:
          Serial.println(F("Get Wrong Stack"));
          break;
        case CheckSumNotMatch:
          Serial.println(F("Check Sum Not Match"));
          break;
        case FileIndexOut:
          Serial.println(F("File Index Out of Bound"));
          break;
        case FileMismatch:
          Serial.println(F("Cannot Find File"));
          break;
        case Advertise:
          Serial.println(F("In Advertise"));
          break;
        default:
          break;
      }
      break;
    default:
      break;
  }
  
}

void loop()
{


if (seq==0) 
  {
    track1 = false;
    track2 = false;
    track3 = false;
    track4 = false;
    track5 = false;
  }

if (digitalRead(gerkon1)==LOW and not track1) 
  {
    seq = 1;
    myDFPlayer.play(1);
    track1 = true;
  }

if (myDFPlayer.available() and myDFPlayer.readType() == 5 and (myDFPlayer.read()==1 or myDFPlayer.read()==3 or myDFPlayer.read()==5 or myDFPlayer.read()==7 or myDFPlayer.read()==9)) trackfinish = true;
 
if (digitalRead(gerkon2)==LOW and not track2 and trackfinish) 
  {
    myDFPlayer.play(3);
    track2 = true;
    trackfinish = false;
  }

if (digitalRead(gerkon2)==LOW and seq==1) 
  {
    seq = 2;
  }

if (digitalRead(gerkon2)==LOW and (seq==3 or seq==4 or seq==5)) 
  {
    seq = 0;
  }

if (digitalRead(gerkon3)==LOW and not track3 and myDFPlayer.readType() == 5 and trackfinish) 
  {
    myDFPlayer.play(5);
    track3 = true;
    trackfinish = false;
  }

if (digitalRead(gerkon3)==LOW and seq==2) 
  {
    seq = 3;
  }

if (digitalRead(gerkon3)==LOW and (seq==1 or seq==4 or seq==5)) 
  {
    seq = 0;
  }

if (digitalRead(gerkon4)==LOW and not track4 and myDFPlayer.readType() == 5 and trackfinish) 
  {
    myDFPlayer.play(7);
    track4 = true;
    trackfinish = false;
  }

if (digitalRead(gerkon4)==LOW and seq==3) 
  {
    seq = 4;
  }

if (digitalRead(gerkon4)==LOW and (seq==1 or seq==2 or seq==5)) 
  {
    seq = 0;
  }

if (digitalRead(gerkon5)==LOW and not track5 and myDFPlayer.readType() == 5 and trackfinish) 
  {
    myDFPlayer.play(9);
    track5 = true;
    trackfinish = false;
  }

if (digitalRead(gerkon5)==LOW and seq==4) 
  {
    seq = 5;
  }

if ( digitalRead(gerkon5)==LOW and (seq==1 or seq==2 or seq==3)) 
  {
    seq = 0;
  }

Timer = millis();

if (millis()- myTimer1 > 1000) 
  {
    myTimer1 = millis();
    //Serial.print("Последовательность: ");
    //Serial.println(seq);

    /*Serial.print("Сработка_1: ");
    Serial.print(track1);
    Serial.print("Сработка_2: ");
    Serial.print(track2);
    Serial.print("Сработка_3: ");
    Serial.print(track3);
    Serial.print("Сработка_4: ");
    Serial.print(track4);
    Serial.print("Сработка_5: ");
    Serial.print(track5);
    */

  }
//if (myDFPlayer.available() and myDFPlayer.readType() == 5) Serial.println("vse");

if (seq==5 and not res and myDFPlayer.available() and myDFPlayer.read()==9 and myDFPlayer.readType() == 5) 
  { // Если последовательность 5 и трек 5 доиграл шкатулка открывается на 10 секунд
    digitalWrite(magnit, HIGH);
    myTimer = Timer;
    res = true;
    Serial.println("vse");
  }

if (seq==5 and Timer - myTimer >= 10000 and res) 
  {   
    Timer = 0; 
    digitalWrite(magnit, LOW); 
    seq = 0;
    res = false;
  }

}