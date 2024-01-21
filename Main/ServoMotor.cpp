#include "ServoMotor.h"

namespace ServoMotor {
    void OpenCommand::execute() {
        Serial.println("-");
        //std::cout << "Deschide servomecanism.\n";
        // Implementarea efectivă pentru deschidere
    }

    void CloseCommand::execute() {
        Serial.println("-");
        //std::cout << "Închide servomecanism.\n";
        // Implementarea efectivă pentru închidere
    }

    void ServoExecutor::setCommand(Command* cmd) {
        command = cmd;
    }

    void ServoExecutor::executeCommand() {
        command->execute();
    }
}
