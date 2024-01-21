// Singleton pentru centralizarea configurărilor
#ifndef CONFIGMANAGER_H
#define CONFIGMANAGER_H

#include <Arduino.h>

class ConfigManager {
private:
    static ConfigManager* instance;

    // Constructor privat pentru a preveni crearea de instanțe directe
    ConfigManager() {}

public:
    static ConfigManager& getInstance();

    // Alte funcționalități ale ConfigManager
    void displayConfiguration() const;
};

#endif // CONFIGMANAGER_H
