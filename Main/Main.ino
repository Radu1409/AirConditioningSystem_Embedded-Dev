//#include "lib/dht.h"
//#include "lib/Logger.h"
//#include <Servo.h>
//#include "TimerOne.h"
//
//dht DHT;
//Servo myServo;
//
//int angle = 0;  // Unghiul pentru servo motor
//int fanSpeed = 0;  // Viteza ventilatorului
//
//const int servoPin = 9;  // Pinul pentru servo motor
//const int mosfetPin = 6;  // Pinul pentru tranzistorul MOSFET
//
//// Constants
//#define DHT22_PIN 2  // Pinul DHT22 (senzorul de temperatură și umiditate)
//
//// Variables
//float hum;  // Stocare valoare umiditate
//float temp; // Stocare valoare temperatură
//
//Logger* logger = nullptr;  // Declarare și inițializare a obiectului logger
//
//void setup() {
//  Serial.begin(9600);
//
//  logger = Logger::getInstance();  // Obține instanța logger
//  logger->logInfo("Sistemul de climatizare se activează...");
//  logger->logInfo("Sistemul se inițializează...");
//
//  logger->logInfo("Se setează Servo-Motor pe PIN 8...");
//  myServo.attach(servoPin);  // Atașează obiectul servo la pinul corespunzător
//  pinMode(mosfetPin, OUTPUT);  // Setează pinul MOSFET ca OUTPUT
//  digitalWrite(mosfetPin, LOW);  // Asigură-te că MOSFET este inițial în starea LOW
//  logger->logInfo("Se setează unghiul pentru Servo-Motor...");
//  Timer1.initialize(50);  // Setează o frecvență de 50 Hz (20 ms perioadă)
//  Timer1.pwm(mosfetPin, 512);  // Setează PWM pe pinul mosfetPin cu o valoare arbitrară (512)
//  
//  logger->logInfo("Sistemul a fost inițializat cu succes!");
//}
//
//void loop() {
//  logger->logInfo("Acesta este un mesaj INFO.");
//  logger->logWarning("Atenție, acesta este un mesaj de avertizare.");
//  logger->logError("Eroare! Acesta este un mesaj de eroare.");
//
//  int chk = DHT.read22(DHT22_PIN);
//  hum = DHT.humidity;
//  temp = DHT.temperature;
//  logger->logInfoFormat("Temperatura: %f Celsius, Umiditate: %f%", temp, hum);
//
//  angle = 20;  // Modifică unghiul în funcție de necesități
//  myServo.write(angle);
//
//  // Mapează unghiul la intervalul 0-255 pentru a controla viteza ventilatorului
//  fanSpeed = map(angle, 0, 180, 0, 255);
//
//  // Setează viteza ventilatorului folosind PWM
//  //analogWrite(mosfetPin, fanSpeed);
//  analogWrite(mosfetPin, 255);
//  delay(5000);  // Așteaptă 5 secunde între iterații (poți ajusta intervalul în funcție de nevoile tale)
//}
//


//Libraries
#include "lib/dht.h"
#include "lib/Logger.h"
#include <Servo.h>
#include <avr/wdt.h>
#include "TimerOne.h"

dht DHT;
Servo myServo;
//int angle = 45;

int angle = 0;  // Unghiul pentru servo motor
float fanSpeed = 0;  // Viteza ventilatorului

//const int servoPin = 9;  // Pinul pentru servo motor
//const int mosfetPin = 6;  // Pinul pentru tranzistorul MOSFET

const int servoPin = 9;  // Pinul pentru servo motor
const int mosfetPin = 3;  // Pinul pentru tranzistorul MOSFET

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
    logger = Logger::getInstance(); // obține instanța logger
    logger->logInfo("The air conditioning system turns on...");
    logger->logInfo("The system is now initializing...");

    logger->logInfo("Setting Servo-Motor to PIN 8...");
//    servo.attach(8);
    myServo.attach(servoPin);  // Atașează obiectul servo la pinul corespunzător
    myServo.write(0);
    pinMode(mosfetPin, OUTPUT);  // Setează pinul MOSFET ca OUTPUT
    //digitalWrite(mosfetPin, LOW);
    analogWrite(mosfetPin, 0);
    logger->logInfo("Setting angle to Servo-Motor...");
//    servo.write(angle);
//    delay(1000);
//    pinMode(GATE, OUTPUT);
//    digitalWrite(GATE, LOW);
    logger->logInfo("The system has been successfully initialized!");
    //attachInterrupt(digitalPinToInterrupt(2), counter, RISING);
    
}

void loop()
{
    
    logger->logInfo("Acesta este un mesaj INFO.");
    logger->logWarning("Atentie, acesta este un mesaj de avertizare.");
    logger->logError("Eroare! Acesta este un mesaj de eroare.");
    int chk = DHT.read22(DHT22_PIN);
    hum = DHT.humidity;
    temp= DHT.temperature;
    logger->logInfoFormat("Temperature: %f Celsius, Humidity: %f%", temp, hum);
    angle = 120;
    myServo.write(angle);
    //angle = myServo.read();  // Citește unghiul de la servo motor
    //fanSpeed = map(angle, 0, 180, 0, 255);  // Mapează unghiul la o valoare potrivită pentru PWM
    //delay(5000);
    logger->logInfo("Waiting");
    //digitalWrite(mosfetPin, 30);  // Setează viteza ventilatorului folosind PWM
    fanSpeed = map(angle, 0, 180, 0, 255);
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
    
//    logger->logInfo("fanSpeed: 162");
//    analogWrite(mosfetPin, 162);
//    delay(10000);
//    logger->logInfo("fanSpeed: 51");
//    analogWrite(mosfetPin, 51);
//    delay(10000);
//    logger->logInfo("fanSpeed: 162");
//    analogWrite(mosfetPin, 162);
//    delay(10000);
//    logger->logInfo("fanSpeed: 255");
//    analogWrite(mosfetPin, 255);
 
    delay(100);  // Așteaptă 100 de milisecunde (poți ajusta acest interval în funcție de nevoile tale)

    //wdt_reset();
}
