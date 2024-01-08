#include <iostream>

// Interfață pentru comenzi
class Command {
public:
    virtual void execute() = 0;
};

// Comandă concretă pentru deschiderea servomecanismului
class OpenCommand : public Command {
public:
    void execute() override {
        std::cout << "Deschide servomecanism.\n";
        // Implementarea efectivă pentru deschidere
    }
};

// Comandă concretă pentru închiderea servomecanismului
class CloseCommand : public Command {
public:
    void execute() override {
        std::cout << "Închide servomecanism.\n";
        // Implementarea efectivă pentru închidere
    }
};

// Executor care poate primi și executa comenzi
class ServoExecutor {
private:
    Command* command;

public:
    void setCommand(Command* cmd) {
        command = cmd;
    }

    void executeCommand() {
        command->execute();
    }
};