// Name : Muhammad Syahendra Anindyantoro
// Bluetooth Smarthome with 4 channel, apk MSA Smarthome.apk
// Github : github.com/hendras1722

#include <EEPROM.h>
String readString;

#define ON 0
#define OFF 1
const int relay1 = 2;
const int relay2 = 3;
const int relay3 = 4;
const int relay4 = 5;    //Connect relay4 to pin 5
byte State1 = 1;
byte State2 = 1;
byte State3 = 1;
byte State4 = 1;
byte State5 = 1;
char input;
void setup()
{
  Serial.begin(9600);            //Set rate for communicating with phone
  
  pinMode(relay1, OUTPUT);       //Set relay1 as an output
  pinMode(relay2, OUTPUT);
  pinMode(relay3, OUTPUT);      //Set relay2 as an output
  pinMode(relay4, OUTPUT);
//  digitalWrite(relay1, HIGH);     //Switch relay1 off
  //digitalWrite(relay2, HIGH);     //Swtich relay2 off
  //digitalWrite(relay3, HIGH);     //Switch relay1 off
  //digitalWrite(relay4, HIGH);     //Swtich relay2 off
 ReadEEPROM ();
}
void loop()
{
  while(Serial.available())    //Check if there are available bytes to read
  {
    delay(10);                 //Delay to make it stable
    char c = Serial.read();    //Conduct a serial read
    if (c == '#'){
      break;                   //Stop the loop once # is detected after a word
    }
    readString += c;                //Means readString = readString + c
  }
    if (readString.length() >0){
      Serial.println(readString);
      if(readString == "switch all on"){
        switchallon();
        EEPROM.write(1, 0);
        EEPROM.write(2, 0);
        EEPROM.write(3, 0);
        EEPROM.write(4, 0);
       }               
      else if(readString == "switch all off"){
        switchalloff();
        EEPROM.write(1, 1);
        EEPROM.write(2, 1);
        EEPROM.write(3, 1);
        EEPROM.write(4, 1);
      }             
      else if(readString == "relay1 on"){   
        digitalWrite(relay1, ON);
      EEPROM.write(1, 0);
      }
      else if(readString == "relay1 off"){
        digitalWrite(relay1, OFF);
      EEPROM.write(1, 1);
      }
       else if(readString == "relay2 on"){   
        digitalWrite(relay2, ON);
      EEPROM.write(2, 0);
      }
      else if(readString == "relay2 off"){
        digitalWrite(relay2, OFF);
      EEPROM.write(2, 1);
      }
       else if(readString == "relay3 on"){   
        digitalWrite(relay3, ON);
      EEPROM.write(3, 0);
      }
      else if(readString == "relay3 off"){
        digitalWrite(relay3, OFF);
      EEPROM.write(3, 1);
      }
      else if(readString == "relay4 on"){
        digitalWrite(relay4, ON);
      EEPROM.write(4, 0);
      }
      else if(readString == "relay4 off"){
        digitalWrite(relay4, OFF);
      EEPROM.write(4, 1);
      }
      readString="";
    }
}
void switchallon(){
  digitalWrite(relay1, ON);
  digitalWrite(relay2, ON);
  digitalWrite(relay3, ON);
  digitalWrite(relay4, ON);
}
void switchalloff(){
  digitalWrite(relay1, OFF);
  digitalWrite(relay2, OFF);
  digitalWrite(relay3, OFF);
  digitalWrite(relay4, OFF);
}
void ReadEEPROM (){
  State1 = EEPROM.read(1);
  State2 = EEPROM.read(2);
  State3 = EEPROM.read(3);
  State4 = EEPROM.read(4);
  State5 = EEPROM.read(5);
  
  digitalWrite(relay1,State1);
  Serial.print(F("Posisi Terakhir relay1 = "));
  if(State1==0)
    {Serial.println("ON");} else {Serial.println("OFF");}
  
  digitalWrite(relay2,State2);
  Serial.print(F("Posisi Terakhir relay2 = "));
  if(State2==0)
  {Serial.println("ON");} else {Serial.println("OFF");}

  digitalWrite(relay3,State3);
  Serial.print(F("Posisi Terakhir relay3 = "));
  if(State3==0)
  {Serial.println("ON");} else {Serial.println("OFF");}

  digitalWrite(relay4,State4);
  Serial.print(F("Posisi Terakhir relay4 = "));
  if(State4==0)
  {Serial.println("ON");} else {Serial.println("OFF");}

  //digitalWrite(switchallon,State4);
  //Serial.print(F("Posisi Terakhir Semua = "));
 // if(State5==0){Serial.println("ON");} else {Serial.println("OFF");}
 }

 void relayON (uint8_t r) {
  digitalWrite (r+1,ON); 
      EEPROM.write(r, 1);
        Serial.print("Relay ");
        Serial.print(r);
        Serial.println(" ON by Bluetooth");
}

void relayOFF (uint8_t r) {
  digitalWrite (r+1,OFF); 
      EEPROM.write(r, 0);
        Serial.print("Relay ");
        Serial.print(r);
        Serial.println(" OFF by Bluetooth");
}
