// Singleton pentru centralizarea configurărilor
#include "ConfigManager.h"

// Inițializare statică a membrului singleton
ConfigManager* ConfigManager::instance = nullptr;

ConfigManager& ConfigManager::getInstance() {
    if (!instance) {
        instance = new ConfigManager();
    }
    return *instance;
}

void ConfigManager::displayConfiguration() const {
    Serial.println("-");
    //std::cout << "Configurația centralizat
}
