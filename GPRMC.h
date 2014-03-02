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
#include "application.h"

#ifndef _GPRMC_H
#define _GPRMC_H

//#include <arduino.h>

#define COMMAS_NUMBER 12

#define TRUE  1
#define FALSE 0

#define CHECKSUM_VALID          1
#define CHECKSUM_NOT_PERFORMED  0
#define CHECKSUM_INVALID        -1

#define PROTOCOL_NAME       0
#define UTC_TIME            1
#define DATA_VALID          2
#define LATITUDE_DEGREES    3
#define LATITUDE_REFERENCE  4
#define LONGITUDE_DEGREES   5
#define LONGITUDE_REFERENCE 6
#define COURSE              7
#define SPEED               8
#define UTC_DATE            9
#define OPERATION_MODE      12

typedef unsigned int uint;


class GPRMC: public String {
    
    /*
     * This class inherits from the C++
     * String class and expands it to manipulate
     * particular types of Strings which are
     * GPRMC String from the NMEA protocol.
     */
    
private:
    
    int commas[COMMAS_NUMBER];  // Array of commas positions in the raw String
    int stringChecksum;         // The String checksum received value
    
    String findElements(int);       // Internal element finder for the parsing
    
public:
    
    GPRMC(char*);
    
    int checksum(void);         // Check if the String is valid or not
    
    String UTCtime(void);       // Return the UTC time
    String dataValid(void);     // Return the data valid character
    String UTCdate(void);       // Return the UTC date
    String latitudeDeg(void);   // Return the latitude degrees
    String latitudeRef(void);   // Return the latitude reference N/S
    String longitudeDeg(void);  // Return the longitude degrees
    String longitudeRef(void);  // Return the longitude reference W/E
    String course(void);        // Return the course degrees
    String speed(void);         // Return the speed in knots
    String opMode(void);        // Return the operation mode
    
    
};

#endif
