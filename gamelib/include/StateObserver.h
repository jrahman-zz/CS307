#ifndef STATE_OBSERVER_H
#define STATE_OBSERVER_H

#include "Util.h"

class Interactable;

class StateObserver {
public:
    virtual bool onPreStateChange(Interactable& obj, State current, State next) = 0;
    virtual void onPostStateChange(Interactable& obj, State current) = 0;
};

#endif
