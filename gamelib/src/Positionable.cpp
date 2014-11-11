#include "Positionable.h"

Positionable::Positionable(Json::Value value) 
    : m_position(value["x"].asInt(), value["y"].asInt()) {
    auto properties = value["properties"];
    m_ID = properties["id"].asInt();
}

Positionable::~Positionable() {
}

Position Positionable::getPosition() const {
    return m_position;
}

void Positionable::setPosition(Position position) {
    m_position = position;
}

unsigned int Positionable::getID() const {
    return m_ID;
}

