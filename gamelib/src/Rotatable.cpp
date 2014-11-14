#include "Rotatable.h"

Rotatable::Rotatable(Json::Value value)
    : Interactable(value)
    , m_rotation(Rotatable::rotationFromInt(stoi(value["properties"].get("rotation", "0").asString())))
    , m_canRotate(true)
{}

Rotatable::~Rotatable() {}

bool Rotatable::rotate(Rotation newRotation) {
    if (newRotation != Rotation::RUNKNOWN && m_canRotate) {
        if (m_rotation != newRotation) {
            shared_ptr<RotateLogEntry> entry(new RotateLogEntry(getID(), newRotation));
            log(entry);
            m_rotation = newRotation;
        }
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

bool Rotatable::canRotate() const {
    return m_canRotate;
}

void Rotatable::setCanRotate(bool value) {
    m_canRotate = value;
}
