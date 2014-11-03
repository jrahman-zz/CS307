#ifndef POSITIONABLE_H
#define POSITIONABLE_H

#include <memory>

#include "ActorObserver.h"
#include "json/json.h"
#include "Position.h"

using namespace std;

class Positionable {
public:
    ~Positionable();
    Position getPosition();

protected:
    Positionable(Json::Value value);

    Position m_position;

    shared_ptr<ActorObserver> m_observer;
};

#endif
