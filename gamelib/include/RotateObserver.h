#ifndef ROTATE_OBSERVER_H
#define ROTATE_OBSERVER_H

class Rotatable;

class RotateObserver {
public:
    virtual bool onPreRotate(Rotatable& src) = 0;
};

#endif
