#ifndef ROTATABLE_H
#define ROTATABLE_H

#include <string>

#include "json/json.h"
#include "Interactable.h"
#include "RotateLogEntry.h"
#include "RotateObserver.h"

class Rotatable : public Interactable {
public:

    virtual ~Rotatable();

    void registerRotateObserver(weak_ptr<RotateObserver> observer);

    bool rotate(Rotation newRotation);

    Rotation getRotation() const;

    bool canRotate() const;

    void setCanRotate(bool value);

protected:

    Rotatable(Json::Value value);

    /*
     * Ban default constructor
     */
    Rotatable() = delete;

    static Rotation rotationFromInt(unsigned int r);

private:
    Rotation m_rotation;
    bool m_canRotate;
    weak_ptr<RotateObserver> m_rotateObserver;
};

#endif
