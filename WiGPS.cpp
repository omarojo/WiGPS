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
#if defined(SPARK)
#include "application.h"
#endif

#include "WiGPS.h"

void WiGPS::parseGPRMC(GPRMC* str){
    /*
     * Save all data from the GPRMC string
     * in a numeric format in memory.
     */

    hours = str->UTCtime().substring(0,2).toInt();
    minutes = str->UTCtime().substring(2,4).toInt();
    seconds = str->UTCtime().substring(4,6).toInt();

    day = str->UTCdate().substring(0,2).toInt();
    month = str->UTCdate().substring(2,4).toInt();
    year = str->UTCdate().substring(4,6).toInt();

    latitudeDeg = str->latitudeDeg().substring(0,2).toInt();
    latitudeMin = str->latitudeDeg().substring(2,4).toInt();
    latitudeSec = str->latitudeDeg().substring(5,6).toInt();
    latitudeRef = str->latitudeRef().charAt(0);

    longitudeDeg = str->longitudeDeg().substring(0,3).toInt();
    longitudeMin = str->longitudeDeg().substring(3,5).toInt();
    longitudeSec = str->longitudeDeg().substring(6,7).toInt();
    longitudeRef = str->longitudeRef().charAt(0);

    String speedString(str->speed());
    int speedDot = speedString.indexOf('.');
    Speed = speedString.substring(0,speedDot).toInt();

    String courseString(str->course());
    int courseDot = courseString.indexOf('.');
    Course = courseString.substring(0,courseDot).toInt();

    return;
}


/******************
 * PUBLIC METHODS
 ******************/


WiGPS::WiGPS(int pw){

    return;
}
void WiGPS::init(int pw) {
    dataReady = FALSE;
    Serial1.begin(9600);//serialPort->begin(9600);
    powerPort = pw;
    pinMode(pw, OUTPUT);
    digitalWrite(powerPort, LOW);
    return;
}

int WiGPS::on(void){
    /*
     * Powers on the GPS which
     * starts watching for satellites
     * to retrieve data from them
     */

    //int timeout = 3;
    int counter = 0;
    digitalWrite(powerPort, HIGH);
    while(!Serial1.available()){
        if(counter++ < 3){
            delay(1000);
        }else{
            return -1;
        };
    };
    return 0;
}


int WiGPS::off(void){
    /*
     * Powers off the GPS which
     * stops watching for satellites
     * but keeps the last RTC data
     * and RAM memory data for future
     * exploring.
     */

    //int timeout = 3;
    int counter = 0;
    digitalWrite(powerPort, LOW);
    while(Serial1.available()){
        if(counter++ < 3){
            delay(1000);
        }else{
            return -1;
        };
    };
    return 0;
}


bool WiGPS::update(void){
    /*
     * The main function for fetching data
     * from the GPS module.
     * This function gets incoming Strings
     * from the serial port and store them
     * in a buffer if they starts with the $ char
     * After retrieving a "valid" String the
     * parser is called.
     */

    char buffer[BUFFER_LENGTH_2];
    char *buf = buffer;
    int dataReady = FALSE;
    int failed5 = 0;


    while(buf - buffer < BUFFER_LENGTH_2){
        *(buf++) = '\0';
    }
    buf = buffer;

    while(!dataReady){
        // Wait for the first incoming header
        while(Serial1.read() != '$');
        // Store the first 5 chars
        for(int i = 0; i<5; i++){
            while(!Serial1.available());

            *(buf++) = Serial1.read();
        }
        //Serial.println("buffer:");
        // Serial.println(buffer);
        if(strncmp(buffer, PROTOCOL, 5) == 0){
            //Serial.println(buffer);
            // This is the right String, go on
            do {
                // Fetch the rest of the GPRMC String
                while(!Serial1.available());
                *buf = Serial1.read();
            } while(*(buf++) != '\n');

            GPRMC str(buffer);
            Serial.println(str);

            if(str.dataValid().equals("A")){
                // The string is ok, extract data
                // TODO: ADD CHECKSUM CONTROL TO THE STRING
                //Serial.println(str);
                parseGPRMC(&str);

                //Now break the cycle
                dataReady = TRUE;
                return dataReady;
            };
        };
        //Serial.println("6- Data is not ready ");
        //Serial.println("------");
        //failed5++;
        // if(failed5 == 1500){
        //     Serial.println("7- Too many fails.. quitting ");
        //     return TRUE;
        // }

        buf = buffer;
    };
    return TRUE;
}


String WiGPS::time(void){
    /*
     * Get the time from the
     * last updated data in the memory
     * in the format of the String d
     */

    String h(hours);
    String m(minutes);
    //String s(seconds);
    String f = h + String(':') + m;// + String(':') + s;
    return f;
}


String WiGPS::date(void){
    /*
     * Get the date from the
     * last updated data in the memory
     * in the format of the String d
     */

    String d(day);
    String m(month);
    //String y(year);
    String f = d + String('-') + m;//+ String('-') + y;
    return f;
}


String WiGPS::latitude(void){
    /*
     * Get the latitude from the
     * last updated data in the memory
     * in the format of the String d
     */

    String d(latitudeDeg);
    String m(latitudeMin);
    String s(latitudeSec);
    String r(latitudeRef);
    char c = DEGREE_CHAR;
    String f = d + String(c) + m + String('\'') + s + String('\"') + r;
    return f;
}


String WiGPS::longitude(void){
    /*
     * Get the longitude from the
     * last updated data in the memory
     * in the format of the String d
     */

    String d(longitudeDeg);
    String m(longitudeMin);
    String s(longitudeSec);
    String r(longitudeRef);
    char c = DEGREE_CHAR;
    String f = d + String(c) + m + String('\'') + s + String('\"') + r;
    return f;
}


String WiGPS::speed(void){
    /*
     * Get the speed from the
     * last updated data in the memory
     * in the format of the String d (km/h)
     */

    String s((int)(KMKNOT*Speed));
    String f = s + String(" km/h");
    return f;
}


String WiGPS::course(void){
    /*
     * Get the course from the
     * last updated data in the memory
     * in the format of the String d
     */

    String s(Course);
    char c = DEGREE_CHAR;
    String f = s + String(c);
    return s;
}

WiGPS::~WiGPS(){
    /*
     * This destroys the created
     * SoftwareSerial object.
     */

    //delete serialPort;
}

