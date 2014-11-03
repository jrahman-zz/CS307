#include "Position.h"

Position::Position(unsigned int x, unsigned int y) 
    : m_x(x)
    , m_y(y)
    , m_valid(true)
{}

Position::Position(const Position& rhs) 
    : m_x(rhs.m_x)
    , m_y(rhs.m_y)
    , m_valid(rhs.m_valid)
{}

Position::Position() 
    : m_valid(false)
    , m_x(0)
    , m_y(0)
{}

Position::~Position() {}

Json::Value Position::toJson() const {
    if (!m_valid) {
        throw runtime_error("Not initialized");
    }
    
    Json::Value root;
    root["x"] = m_x;
    root["y"] = m_y;
    return root;
}

unsigned int Position::getX() const {
    if (!m_valid) {
        throw runtime_error("Not initialized");
    }
    return m_x;
}

unsigned int Position::getY() const {
    if (!m_valid) {
        throw runtime_error("Not initialized");
    }
    return m_y;
}

void Position::setX(unsigned int x) {
    m_x = x;
}

void Position::setY(unsigned int y) {
    m_y = y;
}
