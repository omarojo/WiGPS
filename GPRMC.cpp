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

#include "GPRMC.h"
#include "arduino.h"


GPRMC::GPRMC(char* gprmc) : String(gprmc){
    /*
     * Initialize the oject and parse the incoming String
     * looking for all commas in the String.
     */

    int p = 0; 
    int* c = commas;

    for(int i = 0; i<COMMAS_NUMBER; i++){
        p = this->indexOf(',', p);
        if(p == -1){
            while(i<COMMAS_NUMBER){
                *(c++) = -1;
                i++;
            };
        }
        else{
            *(c++) = (p++);
        }
    }

    p = this->indexOf('*') + 1;
    if(p > 0){
        stringChecksum = this->substring(p).toInt();
    }else{
        stringChecksum = -1;
    };  
}


int GPRMC::checksum(void){
    /*
     * Perform the checksum of the 
     * entire String if possible.
     */
    int ret_value = CHECKSUM_NOT_PERFORMED;
    if(stringChecksum == -1){
        ret_value = CHECKSUM_NOT_PERFORMED;
    }
    else{

        // Perform the checksum and select what to return

    }
    
    return ret_value;
}


String GPRMC::findElements(int elementNumber){
    /*
     * Calculate the element relative subString length
     * from the raw GPRMC String. Then, extract
     * a subString and return it
     */

    // Get the comma right BEFORE the selected element
    int startComma = commas[elementNumber-1];
    // Get the comma right AFTER the selected element
    int stopComma = commas[elementNumber];
    //Return the substring inside the commas
    return this->substring(startComma+1, stopComma);
}


String GPRMC::UTCtime(void){
    return findElements(UTC_TIME);
}


String GPRMC::dataValid(void){
    return findElements(DATA_VALID);
}


String GPRMC::UTCdate(void){
    return findElements(UTC_DATE);
}


String GPRMC::latitudeDeg(void){
    return findElements(LATITUDE_DEGREES);
}


String GPRMC::latitudeRef(void){
    return findElements(LATITUDE_REFERENCE);
}


String GPRMC::longitudeDeg(void){
    return findElements(LONGITUDE_DEGREES);
}


String GPRMC::longitudeRef(void){
    return findElements(LONGITUDE_REFERENCE);
}


String GPRMC::course(void){
    return findElements(COURSE);
}


String GPRMC::speed(void){
    return findElements(SPEED);
}


String GPRMC::opMode(void){
    return findElements(OPERATION_MODE);
}
