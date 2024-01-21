// Logger.cpp
#include "Logger.h"

Logger* Logger::instance = nullptr; // Inițializare instanță la nullptr
Logger* Logger::logger = nullptr; // Inițializare instanță logger la nullptr


Logger::Logger() {
  if (!rtc.begin()) {
    Serial.println("Couldn't find RTC");
    while (1);
  }

  if (rtc.lostPower()) {
    Serial.println("RTC lost power, let's set the time!");
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
  }
}

Logger* Logger::getInstance() {
  if (!instance) {
    instance = new Logger();
    logger = instance; // setează logger să fie instanța creată
  }
  return instance;
}


//void Logger::logInfo(const char* message) {
//  printTimestamp();
//  Serial.print("[\033[32mINFO\033[0m] "); // Verde
//  Serial.println(message);
//  delay(2000);
//}
//
//void Logger::logWarning(const char* message) {
//  printTimestamp();
//  Serial.print("[\033[33mWARNING\033[0m] "); // Galben
//  Serial.println(message);
//  delay(2000);
//}
//
//void Logger::logError(const char* message) {
//  printTimestamp();
//  Serial.print("[\033[31mERROR\033[0m] "); // Roșu
//  Serial.println(message);
//  delay(2000);
//}


void Logger::logInfo(const char* message) {
  logFormat("[\033[32mINFO\033[0m]", " %s", message);
}

void Logger::logWarning(const char* message) {
  logFormat("[\033[33mWARNING\033[0m]", " %s", message);
}

void Logger::logError(const char* message) {
  logFormat("[\033[31mERROR\033[0m]", " %s", message);
}

void Logger::logFormat(const char* level, const char* format, ...) {
  printTimestamp();

  char buffer[256]; // Alocare unui buffer suficient de mare
  va_list args;
  va_start(args, format);
  vsnprintf(buffer, sizeof(buffer), format, args);
  va_end(args);

  Serial.print(level);
  Serial.println(buffer);
  delay(2000);
}

//void Logger::logInfoFormat(const char* format, ...) {
//  printTimestamp();
//
//  char buffer[256]; // Alocare unui buffer suficient de mare
//  va_list args;
//  va_start(args, format);
//  vsnprintf(buffer, sizeof(buffer), format, args);
//  va_end(args);
//
//  Serial.print("[\033[32mINFO\033[0m] "); // Verde
//  Serial.println(buffer);
//  delay(2000);
//}
void Logger::logInfoFormat(const char* format, ...) {
  printTimestamp();

  const int bufferSize = 512;  // Dimensiunea buffer-ului

  char buffer[bufferSize];
  va_list args;
  va_start(args, format);

  int length = snprintf(buffer, bufferSize, "[\033[32mINFO\033[0m] ");

  if (length >= 0 && length < bufferSize) {
    while (*format) {
      if (*format == '%' && *(format + 1) == 'f') {
        float value = va_arg(args, double);
        char tempBuffer[16];  // Un buffer temporar pentru conversia valorii de tip float
        dtostrf(value, 6, 2, tempBuffer);
        length += snprintf(buffer + length, bufferSize - length, "%s", tempBuffer);
        format += 2;
      } else {
        buffer[length++] = *format++;
      }

      if (length >= bufferSize) {
        Serial.println("[\033[31mERROR\033[0m] Buffer depășit în logInfoFormat.");
        return;
      }
    }

    buffer[length] = '\0';
    Serial.println(buffer);
  } else {
    Serial.println("[\033[31mERROR\033[0m] Buffer depășit în logInfoFormat.");
  }

  va_end(args);
  delay(2000);
}


//void Logger::printTimestamp() {
//  unsigned long currentMillis = millis();
//  unsigned long seconds = currentMillis / 1000;
//  unsigned long minutes = seconds / 60;
//  unsigned long hours = minutes / 60;
//
//  Serial.print("[");
//  Serial.print(hours % 24); // Afișează orele în format 24 de ore
//  Serial.print(":");
//  Serial.print(minutes % 60);
//  Serial.print(":");
//  Serial.print(seconds % 60);
//  Serial.print("] ");
//}

//void Logger::printTimestamp() {
//  DateTime now = rtc.now();
//  Serial.print("[");
//  Serial.print(now.year(), DEC);
//  Serial.print(":");
//  printDigits(now.month());
//  Serial.print(":");
//  printDigits(now.day());
//  Serial.print("] ");
//}

void Logger::printMonthAbbreviation(int month) {
  // Verifică valabilitatea lunii
  if (month >= 1 && month <= 12) {
    // Vector cu abrevieri lunare
    const char* monthAbbreviations[] = {"Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};
    
    // Afișează abrevierea lunii corespunzătoare
    Serial.print(monthAbbreviations[month - 1]);
  } else {
    // Dacă luna nu este validă, afișează un mesaj de eroare
    Serial.print("Invalid Month");
  }
}

void Logger::printTimestamp() {
  DateTime now = rtc.now();
  
  // Afișează data în formatul [YYYY Mon DD: HH:MM:SS]
  Serial.print("[");
  Serial.print(now.year(), DEC);
  Serial.print(" ");
  printMonthAbbreviation(now.month());
  Serial.print(" ");
  printDigits(now.day(), false);
  Serial.print(": ");
  printDigits(now.hour(), true);
  Serial.print(":");
  printDigits(now.minute(), true);
  Serial.print(":");
  printDigits(now.second(), true);
  Serial.print("] ");
}

void Logger::printDigits(int digits, bool leadingZero) {
  // Adaugă un zero în fața cifrelor mai mici decât 10 (dacă leadingZero este true)
  if (digits < 10 && leadingZero)
    Serial.print('0');
  Serial.print(digits);
}
//void Logger::printDigits(int digits) {
//  Serial.print(digits < 10 ? '0' : ' ');
//  Serial.print(digits);
//}
