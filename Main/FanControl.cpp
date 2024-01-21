#include "FanControl.h"

namespace Fan {
    FanControl::FanControl(FanState* initState) : currentState(initState) {}

    void FanControl::setState(FanState* newState) {
        currentState = newState;
    }

    void FanControl::request() {
        currentState->handle();
    }

    void FanOffState::handle() {
        //std::cout << "Ventilatorul este oprit.\n";
    }

    void FanOnState::handle() {
        //std::cout << "Ventilatorul este în funcțiune.\n";
    }
}
