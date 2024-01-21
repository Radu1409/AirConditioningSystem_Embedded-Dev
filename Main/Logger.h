#ifndef LOGGER_H
#define LOGGER_H

#include <Arduino.h>
#include <Wire.h>
#include <RTClib.h>

class Logger {
private:
  Logger(); // constructor privat pentru a impune pattern-ul singleton
  static Logger* instance; // instanță statică a clasei Logger
  static Logger* logger; // instanță statică pentru utilizare ca obiect logger

  RTC_DS3231 rtc; // obiect RTC pentru a obține data și ora

public:
  static Logger* getInstance(); // metoda pentru a obține instanța clasei Logger
  void logInfo(const char* message); // metoda pentru a înregistra mesaje INFO
  void logWarning(const char* message); // metoda pentru a înregistra mesaje WARNING
  void logError(const char* message); // metoda pentru a înregistra mesaje ERROR
  void printTimestamp();
  void printDigits(int digits, bool leadingZero);
  void logFormat(const char* level, const char* format, ...);
  void logInfoFormat(const char* format, ...);
  void printMonthAbbreviation(int month);
  
  // alte metode pot fi adăugate pentru diferite nivele de logare sau formate
};

extern Logger* logger; // declarare externă pentru obiectul logger

#endif // LOGGER_H
