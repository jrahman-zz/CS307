#include "Positionable.h"

Positionable::Positionable(Json::Value value)
    : m_position(value["x"].asInt(), value["y"].asInt())
    , m_ID(Positionable::nextID++)
{}

Position Positionable::getPosition() const {
    return m_position;
}

unsigned int Positionable::getID() const {
    return m_ID;
}

/*
 * We draw all our unique IDs from this
 * NOT threadsafe!
 */
unsigned int Positionable::nextID = 0;
