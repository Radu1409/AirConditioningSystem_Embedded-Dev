//Libraries
#include "Logger.h"
#include "Dht.h"
#include <Servo.h>
#include <avr/wdt.h>
//#include "TimerOne.h"

dht DHT;
Servo myServo;

float fanSpeed = 0;  // Viteza ventilatorului

const int mosfetPin = 3;  // Pinul pentru tranzistorul MOSFET

const int RELAY_PIN = 7;
const int RELAY_PIN1 = 4;

//Constants
#define DHT22_PIN 2     // DHT 22  (AM2302) - what pin we're connected to
#define GATE 6

//Variables
float hum;  //Stores humidity value
float temp; //Stores temperature value

Logger* logger = nullptr; // declarare și inițializare a obiectului logger

void setup()
{
    TCCR2B = TCCR2B & B11111000 | B00000001; // for PWM frequency of 31372.55 Hz
    //TCCR2B = TCCR2B & B11111000 | B00000010; // for PWM frequency of 3921.16 Hz

    //TCCR0B = TCCR0B & B11111000 | B00000001; // for PWM frequency of 62500.00 Hz PIN D5 / D6
    //TCCR1B = TCCR1B & B11111000 | B00000001; // set timer 1 divisor to 1 for PWM frequency of 31372.55 Hz // PIN D9 / D10
    Serial.begin(9600);
    //wdt_enable(WDTO_4S);
    pinMode(RELAY_PIN, OUTPUT);
    digitalWrite(RELAY_PIN, HIGH);

    pinMode(RELAY_PIN1, OUTPUT);
    digitalWrite(RELAY_PIN1, HIGH);
    
    logger = Logger::getInstance(); // obține instanța logger
    logger->logInfo("The air conditioning system turns on...");
    logger->logInfo("The system is now initializing...");

    pinMode(mosfetPin, OUTPUT);  // Setează pinul MOSFET ca OUTPUT
    //digitalWrite(mosfetPin, LOW);
    analogWrite(mosfetPin, 0);
    logger->logInfo("The system has been successfully initialized!");    
}

void loop()
{
    digitalWrite(RELAY_PIN, LOW);
    delay(10000);
    digitalWrite(RELAY_PIN, HIGH);
    delay(1000);

    digitalWrite(RELAY_PIN1, LOW);
    delay(10000);
    digitalWrite(RELAY_PIN1, HIGH);
    delay(1000);
    
    logger->logInfo("Acesta este un mesaj INFO.");
    logger->logWarning("Atentie, acesta este un mesaj de avertizare.");
    logger->logError("Eroare! Acesta este un mesaj de eroare.");
    int chk = DHT.read22(DHT22_PIN);
    hum = DHT.humidity;
    temp= DHT.temperature;
    logger->logInfoFormat("Temperature: %f Celsius, Humidity: %f%", temp, hum);

    logger->logInfo("Waiting");
    //digitalWrite(mosfetPin, 30);  // Setează viteza ventilatorului folosind PWM
    //fanSpeed = map(angle, 0, 180, 0, 255);
    //logger->logInfoFormat("fanSpeed: %f", fanSpeed);

    logger->logInfo("fanSpeed: 128");
    analogWrite(mosfetPin, 128);
    delay(10000);
    logger->logInfo("fanSpeed: 64");
    analogWrite(mosfetPin, 64);
    delay(10000);
    logger->logInfo("fanSpeed: 192");
    analogWrite(mosfetPin, 192);
    delay(10000);
    logger->logInfo("fanSpeed: 255");
    analogWrite(mosfetPin, 255);
    
    delay(100);  // Așteaptă 100 de milisecunde (poți ajusta acest interval în funcție de nevoile tale)
    //wdt_reset();
}
