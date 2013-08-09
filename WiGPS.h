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

#ifndef _WIGPS_H
#define _WIGPS_H

#include <arduino.h>
#include <SoftwareSerial.h>

#include "GPRMC.h"

#define KMKNOT 1.852

/*****************
 * Data constants 
 *****************/

#define PROTOCOL 		"GPRMC"
#define BUFFER_LENGTH 	75

/*******************
 * GPS POWER STATES
 *******************/

#define ON 1
#define OFF 0

/**************
 * ERROR CODES
 **************/

#define TRUE 1
#define FALSE 0

/*************
 * TYPEDEFS
 *************/

typedef unsigned int uint;
typedef unsigned char uchar;
typedef SoftwareSerial* Port;

class WiGPS {

private:

	/***************
	 * PRIVATE VARS
	 ***************/

	Port serialPort;			// A pointer to the serial port the GPS communicates through
	uint portType;				// Port type, see upside to understand types
   	uint powerPort;				// The pin Arduino uses to activate/deactivate the GPS
	bool powerState;			// Power state of the GPS

	int hours;					// Last UTC time data from the GPS
	int minutes;
	int seconds;
	//int milliseconds;

	int day;					// Last UTC date data from the GPS
	int month;
	int year;

	int latitudeDeg;			// Last Latitude data from the GPS
	int latitudeMin;
	int latitudeSec;
	char latitudeRef;

	int longitudeDeg;			// Last Longitude data from the GPS
	int longitudeMin;
	int longitudeSec;
	char longitudeRef;

	int Speed;					// Last speed from the GPS (km/h)
	int Course;					// Last course over ground (degrees from the north)

	int dataReady;				// Data ready to be read

	/******************
	 * PRIVATE METHODS
	 ******************/

	void parseGPRMC(GPRMC*);		// Extract data from the GPRMC String
	
public:

	/*****************
	 * PUBLIC METHODS
	 *****************/
	
	WiGPS(int, int, int);			

	int on(void);	 				// Powers on the GPS module
	int off(void);	 				// Turns off the GPS module and stop tracking data
	bool update(void);			 	// Starts fetching data from the GPS.

	String time(void);				// Returns an Arduino String object for the UTC time
	String date(void);				// Returns an Arduino String object for the UTC date
	String latitude(void);			// Returns an Arduino String object for the latitude
	String longitude(void);			// Returns an Arduino String object for the longitude
	String speed(void);				// Returns an Arduino String object for the speed
	String course(void);			// Returns an Arduino String object for the course

	~WiGPS();
};

#endif
