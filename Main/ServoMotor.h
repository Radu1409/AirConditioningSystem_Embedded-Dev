#ifndef SERVOMOTOR_H
#define SERVOMOTOR_H

#include <Arduino.h>

namespace ServoMotor {
    // Interfață pentru comenzi
    class Command {
    public:
        virtual void execute() = 0;
    };

    // Comandă concretă pentru deschiderea servomecanismului
    class OpenCommand : public Command {
    public:
        void execute() override;
    };

    // Comandă concretă pentru închiderea servomecanismului
    class CloseCommand : public Command {
    public:
        void execute() override;
    };

    // Executor care poate primi și executa comenzi
    class ServoExecutor {
    private:
        Command* command;

    public:
        void setCommand(Command* cmd);
        void executeCommand();
    };
}

#endif // SERVOMOTOR_H
