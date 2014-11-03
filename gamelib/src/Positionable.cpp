#include "Positionable.h"

Positionable::Positionable(Json::Value value)
    : m_position(value["x"].asInt(), value["y"].asInt()) 
{}

Position Positionable::getPosition() {
    return m_position;
}


