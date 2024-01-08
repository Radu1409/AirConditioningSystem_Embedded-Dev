// Singleton pentru centralizarea configurărilor
class ConfigManager {
private:
    static ConfigManager* instance;

    // Constructor privat pentru a preveni crearea de instanțe directe
    ConfigManager() {}

public:
    static ConfigManager& getInstance() {
        if (!instance) {
            instance = new ConfigManager();
        }
        return *instance;
    }

    // Alte funcționalități ale ConfigManager
    void displayConfiguration() const {
        std::cout << "Configurația centralizată.\n";
    }
};

// Inițializare statică a membrului singleton
ConfigManager* ConfigManager::instance = nullptr;