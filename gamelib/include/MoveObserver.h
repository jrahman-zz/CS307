#ifndef MOVE_OBSERVER_H
#define MOVE_OBSERVER_H

#include "Position.h"

class Moveable;

class MoveObserver {
public:
    MoveObserver() {}
    ~MoveObserver() {}

    virtual bool onPreMove(Moveable& obj, Position next) = 0;
    virtual void onPostMove(Moveable& obj, Position old) = 0;
};

#endif
