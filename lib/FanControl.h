#ifndef FANCONTROL_H
#define FANCONTROL_H

#include <iostream>

namespace Fan {
    // Interfață pentru diferitele stări ale ventilatorului
    class FanState {
    public:
        virtual void handle() = 0;
    };

    // Stare concretă pentru ventilator oprit
    class FanOffState : public FanState {
    public:
        void handle() override;
    };

    // Stare concretă pentru ventilator în funcțiune
    class FanOnState : public FanState {
    public:
        void handle() override;
    };

    // Context care utilizează o anumită stare
    class FanControl {
    private:
        FanState* currentState;

    public:
        FanControl(FanState* initState);
        void setState(FanState* newState);
        void request();
    };
}

#endif // FANCONTROL_H