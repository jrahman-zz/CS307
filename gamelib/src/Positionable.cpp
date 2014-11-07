#include "Positionable.h"

#include <iostream>

Positionable::Positionable(Json::Value value)
    : m_position(value["x"].asInt(), value["y"].asInt()) {
    auto properties = value["properties"];
    m_ID = properties["id"].asInt();
    cout << "Positionable " << m_position.getX() << " " << m_position.getY() << endl;
}

Positionable::Positionable(const Positionable& rhs)
    : m_position(rhs.m_position)
    , m_ID(rhs.m_ID)
{}

Positionable::~Positionable() {
}

Position Positionable::getPosition() const {
    return m_position;
}

unsigned int Positionable::getID() const {
    return m_ID;
}

