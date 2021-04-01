/*
  GPS_statistic - Library for creating statistics for GPS
  Created by Peter Bisgaard Andersen, 20210330
  
*/

#ifndef GPS_statistic_h
#define GPS_statistic_h

#include "Arduino.h"

class GPS_statistic
{
  public:
    GPS_statistic(unsigned long noReadingToAverageOver);
    void addReading(int numberOfSatelites);
    unsigned int totalNoOfReadings();
    float avgSatelites();
    unsigned int maxSatelites();
    unsigned int minSatelites();
    float avgMinuteBetweenReadings();
    unsigned int maxMinuteBetweenReadings();
    unsigned int minMinuteBetweenReadings();
    //float runningAverage(unsigned long nuToAverageOver, float oldAverage, int newValue);
    float totalAverage(unsigned long noToAverageOver, float oldAverage, int newValue);
  private:
    unsigned long _minutesSinceStart;
    unsigned long _lastMinutesSinceStart;
    unsigned long _noReadingToAverageOver;
    unsigned long _totalNoOfReadings;
    
    float _avgSatelites;
    unsigned int _maxSatelites;
    unsigned int _minSatelites;
  
    float _avgMinuteBetweenReadings;
    unsigned int _maxMinuteBetweenReadings;
    unsigned int _minMinuteBetweenReadings;
};

#endif
