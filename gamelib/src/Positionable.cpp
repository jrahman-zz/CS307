#include "Positionable.h"

Positionable::Positionable(Json::Value value) 
    : m_position(value["x"].asInt(), value["y"].asInt())
    , m_ID(stoi(value["properties"].get("id", "-1").asString())) 
{}

Positionable::~Positionable() {
}

Position Positionable::getPosition() const {
    return m_position;
}

void Positionable::setPosition(Position position) {
    m_position = position;
}

int Positionable::getID() const {
    return m_ID;
}

