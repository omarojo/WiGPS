#include "application.h"
// This #include statement was automatically added by the Spark IDE.
#include "WiGPS.h"

// This #include statement was automatically added by the Spark IDE.
#include "GPRMC.h"


/***************
 * WiGPS Arduino Library, BasicGPS example.
 * Connect the GPS-11571 module to your Arduino
 * Pins are connected as following:
 * VCC: 3.3V, common GND
 * RX - Serial1
 * TX - Serial1
 * Backup battery not connected
 * Power ON/OFF to pin 7
 ***************/

// Initialize a new WiGPS object
WiGPS gps(7);//Not really needed right now.. disconnected means GPS is ON

void setup() {
  // You will inspect values trough the Serial Port
  Serial.begin(9600);
  
  // The GPS will start looking for satellites
  gps.on();
  delay(3000);
  Serial.println("Please wait...");
  gps.update();
   
  // After data have been retrieved you'll get them
  Serial.print("Time: ");
  Serial.println(gps.time());
  Serial.print("Date: ");
  Serial.println(gps.date());
  Serial.print("Latitude: ");
  Serial.println(gps.latitude());
  Serial.print("Longitude: ");
  Serial.println(gps.longitude());
  Serial.print("Speed: ");
  Serial.println(gps.speed());
  Serial.print("Course: ");
  Serial.println(gps.course());
  
  // Turn off the GPS to save battery without loosing RTC data
  gps.off();
}

void loop() {
  // Loop forever here
}





// void setup() 
// {
//   Serial.begin(9600);
//   Serial1.begin(9600);

// }

// void loop() 
// {
//   // read from port 0, send to port 1:
//   /*if (Serial.available()) 
//   {
//     int inByte = Serial.read();
//     Serial1.print(inByte, BYTE);
//   }*/
//   // read from port 1, send to port 0:
//   if (Serial1.available()) 
//   {
//     int inByte = Serial1.read();
//     Serial.println(inByte);
//   }
// }