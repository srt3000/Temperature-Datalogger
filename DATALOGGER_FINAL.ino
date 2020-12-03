#include <SPI.h>
#include <SD.h>
#include <Wire.h>
#include "RTClib.h"
RTC_DS1307 rtc;
char daysOfTheWeek[7][12] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};
File myFile;
float temp;
int tempPin = A0;

void setup() {
  // Open serial communications and wait for port to open:
  Serial.begin(9600);
  sd_init();
  // rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));//auto update from computer time
    rtc.adjust(DateTime(2019, 10, 9, 12, 13, 10));// to set the time manualy 

}

void loop() 
{
  sd_write();

}
void sd_init()
{
//    while (!Serial) 
//    {
//    ; // wait for serial port to connect. Needed for native USB port only
//    }


  Serial.print("Initializing SD card...");

  if (!SD.begin(4)) {
    Serial.println("initialization failed!");
    while (1);
  }
  Serial.println("initialization done.");
}
void sd_write()
{
    DateTime now = rtc.now();
 //  if (myFile)
   {
    myFile = SD.open("data.csv", FILE_WRITE);
    myFile.print(daysOfTheWeek[now.dayOfTheWeek()]);
    myFile.print(",");
    myFile.print(now.day());
    myFile.print('/');
    myFile.print(now.month());
    myFile.print('/');
    myFile.print(now.year());
    myFile.print(",");
    myFile.print(now.hour());
    myFile.print(':');
    myFile.print(now.minute());
    myFile.print(':');
    myFile.print(now.second());
    myFile.print(",");
    tempread();
    myFile.print(",");
    myFile.print("TEMPERATURE   ");
    myFile.println(temp);
    // close the file:
    myFile.println();
     myFile.close();
   }
//    myFile = SD.open("test.txt", FILE_WRITE);

  // if the file opened okay, write to it:
  
//  if (myFile) 
//  {  
////    tempread();
////    myFile.println(temp);
////    // close the file:
////    myFile.close();
//    Serial.println("done.");
//  } 
}
void tempread()
{
     temp = analogRead(tempPin);  // read analog volt from sensor and save to variable temp
        temp = temp * 0.48828125;    // convert the analog volt to its temperature equivalent
        Serial.print("TEMPERATURE = ");
        Serial.print(temp); // display temperature value
        Serial.print("*C");
        Serial.println();
        delay(1000); // update sensor reading each one second    
        Serial.print("Writing to test.txt...");
}
