/*
  GPS_statistic.cpp - Library for creating statistics for GPS
  Created by Peter Bisgaard Andersen, 20210330
  
*/

#include "Arduino.h"
#include "GPS_statistic.h"


GPS_statistic::GPS_statistic(unsigned long noReadingToAverageOver){
  _minutesSinceStart = millis()/60000;
  _lastMinutesSinceStart = _minutesSinceStart;
  _noReadingToAverageOver = noReadingToAverageOver;
}

void GPS_statistic::addReading(int numberOfSatelites, byte gpsHour){
  unsigned long actMinutesSinceStart = millis()/60000;
  int minutesSinceLastReading = actMinutesSinceStart - _lastMinutesSinceStart;
  if(minutesSinceLastReading < _minMinuteBetweenReadings)
    _minMinuteBetweenReadings = minutesSinceLastReading;
  if(minutesSinceLastReading > _maxMinuteBetweenReadings)
    _maxMinuteBetweenReadings = minutesSinceLastReading;
  _lastMinutesSinceStart = actMinutesSinceStart;

  if(gpsHour<=24){
    if(lastGpsHoue != gpsHour)
      hourStatistic[gpsHour] = 0;
    hourStatistic[gpsHour] = hourStatistic[gpsHour]+1;
  }
  
  _totalNoOfReadings++;
  if((numberOfSatelites < _minSatelites)||(_minSatelites == 0))
    _minSatelites = numberOfSatelites;
  if(numberOfSatelites > _maxSatelites)
    _maxSatelites = numberOfSatelites;

  _avgSatelites = totalAverage(_totalNoOfReadings, _avgSatelites, numberOfSatelites);
}

// Not used
//float GPS_statistic::runningAverage(nuToAverageOver, oldAverage, newValue){
//  float pathToSubstract = oldAverage / nuToAverageOver;
//  return oldAverage - pathToSubstract + newValue / nuToAverageOver;
//}

float GPS_statistic::totalAverage(unsigned long totalnumbers, float oldAverage, int newValue){
   return oldAverage + (newValue - oldAverage) / totalnumbers;
}

unsigned int GPS_statistic::totalNoOfReadings(){
  return _totalNoOfReadings;
}

float GPS_statistic::avgSatelites(){
  return _avgSatelites;
}

unsigned int GPS_statistic::maxSatelites(){
  return _maxSatelites;
}

unsigned int GPS_statistic::minSatelites(){
  return _minSatelites;
}

int *GPS_statistic::getHourStatistic(){
  return &hourStatistic
}

float GPS_statistic::avgMinuteBetweenReadings(){
  return _avgMinuteBetweenReadings;
}

unsigned int GPS_statistic::maxMinuteBetweenReadings(){
  return _maxMinuteBetweenReadings;
}

unsigned int GPS_statistic::minMinuteBetweenReadings(){
  return _minMinuteBetweenReadings;
}
