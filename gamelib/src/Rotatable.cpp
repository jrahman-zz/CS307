#include "Rotatable.h"

Rotatable::Rotatable(Json::Value value)
    : Interactable(value)
{
    auto rotate = value["rotation"].asInt();
    m_rotation = Rotatable::rotationFromInt(rotate);
}

Rotatable::~Rotatable() {}

bool Rotatable::rotate(Rotation newRotation) {
    if (newRotation != Rotation::RUNKNOWN) {
        shared_ptr<RotateLogEntry> entry(new RotateLogEntry(getID(), newRotation));
        log(entry);
        m_rotation = newRotation;
        return true;
    }
    return false;
}

Rotation Rotatable::rotationFromInt(unsigned int r) {
    Rotation rot;
    switch (r) {
        case 0:
            rot = Rotation::R0;
            break;
        case 90:
            rot = Rotation::R90;
            break;
        case 180:
            rot = Rotation::R180;
            break;
        case 270:
            rot = Rotation::R270;
            break;
        default:
            rot = Rotation::RUNKNOWN;
    }
    return rot;
}
