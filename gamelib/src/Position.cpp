#include "Position.h"

Position::Position(unsigned int x, unsigned int y) 
    : m_x(x)
    , m_y(y)
    , m_xValid(true)
    , m_yValid(true)
{}

Position::Position(const Position& rhs) 
    : m_x(rhs.m_x)
    , m_y(rhs.m_y)
    , m_yValid(rhs.m_yValid)
    , m_xValid(rhs.m_xValid)
{}

Position::Position() 
    : m_xValid(false)
    , m_yValid(false)
    , m_x(0)
    , m_y(0)
{}

Position::~Position() {}

Json::Value Position::toJson() const {
    Json::Value root(Json::ValueType::arrayValue);
    root["x"] = m_x;
    root["y"] = m_y;
    return root;
}

unsigned int Position::getX() const {
    return m_x;
}

unsigned int Position::getY() const {
    return m_y;
}

void Position::setX(unsigned int x) {
    m_xValid = true;
    m_x = x;
}

void Position::setY(unsigned int y) {
    m_yValid = true;
    m_y = y;
}
