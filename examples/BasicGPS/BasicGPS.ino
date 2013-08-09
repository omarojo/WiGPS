/*
Copyright 2013 Daniele Faugiana
  
This file is part of "WiGPS Arduino Library".

"WiGPS Arduino Library" is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

"WiGPS Arduino Library" is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with "WiGPS Arduino Library". If not, see <http://www.gnu.org/licenses/>.
*/

#include <SoftwareSerial.h>
#include <WiGPS.h>

/***************
 * WiGPS Arduino Library, BasicGPS example.
 * Connect the GPS-11571 module to your Arduino
 * Pins are connected as following:
 * VCC: 5V, common GND
 * RX to pin 8
 * TX to pin 9
 * Backup battery not connected
 * Power ON/OFF to pin 7
 ***************/

// Initialize a new WiGPS object
WiGPS gps(7,8,9);

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