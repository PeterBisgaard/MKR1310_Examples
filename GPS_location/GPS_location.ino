/*
  GPS Location
  This sketch uses the GPS to determine the location of the board
  and prints it to the Serial monitor.
  Circuit: 
   - MKR board
   - MKR GPS attached via I2C cable
  This example code is in the public domain.
*/

#include <Arduino_MKRGPS.h>
#include "GPS_statistic.h"

GPS_statistic myGPSstat(1000);

void setup() {
  // initialize serial communications and wait for port to open:
  Serial.begin(115200);
  Serial.println("Starting up!");
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }

  // If you are using the MKR GPS as shield, change the next line to pass
  // the GPS_MODE_SHIELD parameter to the GPS.begin(...)
  if (!GPS.begin()) {
    Serial.println("Failed to initialize GPS!");
    while (1);
  }
    Serial.println("Startup done!");
}

void loop() {

  // check if there is new GPS data available

  if (GPS.available()) {
    // read GPS values
    float latitude   = GPS.latitude();
    float longitude  = GPS.longitude();
    float altitude   = GPS.altitude();
    float speed      = GPS.speed();
    int   satellites = GPS.satellites();
    myGPSstat.addReading(satellites);
    float avgSatelites = myGPSstat.avgSatelites();
    unsigned int minSatelites = myGPSstat.minSatelites();
    unsigned int maxSatelites = myGPSstat.maxSatelites();
    
    // print GPS values
    Serial.print("Location: ");
    Serial.print(latitude, 7);
    Serial.print(", ");
    Serial.println(longitude, 7);
    Serial.print("Altitude: ");
    Serial.print(altitude);
    Serial.println("m");
    Serial.print("Ground speed: ");
    Serial.print(speed);
    Serial.println(" km/h");
    Serial.print("Number of satellites: ");
    Serial.println(satellites);
    
    Serial.print("Satellites statistic: ");
    char s[16];
    sprintf(s, "min: %u, max: %u, avg: ", minSatelites, maxSatelites);
    Serial.print(s);
    Serial.println(avgSatelites);
    Serial.println();
  }
// else
//  {
//    Serial.println("No GPS available");
//    delay(2000);
//  }
}
