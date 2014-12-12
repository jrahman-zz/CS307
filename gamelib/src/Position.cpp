#include "Position.h"

#include <iostream>
using namespace std;

Position::Position(int x, int y) 
    : m_x(x)
    , m_y(y)
    , m_xValid(true)
    , m_yValid(true)
{}

Position::Position() 
    : m_x(0)
    , m_y(0)
    , m_xValid(false)
    , m_yValid(false)

{}

Position::Position(const Position& rhs)
    : m_x(rhs.m_x)
    , m_y(rhs.m_y)
    , m_xValid(rhs.m_xValid)
    , m_yValid(rhs.m_yValid)
{}

Json::Value Position::toJson() const {
    Json::Value root(Json::ValueType::objectValue);
    root["x"] = m_x;
    root["y"] = m_y;
    return root;
}

int Position::getX() const {
    if (!isValid()) {
        throw runtime_error("Invalid Position");
    }
    return m_x;
}

int Position::getY() const {
    if (!isValid()) {
        throw runtime_error("Invalid Position");
    }    
    return m_y;
}

void Position::setX(int x) {
    m_xValid = true;
    m_x = x;
}

void Position::setY(int y) {
    m_yValid = true;
    m_y = y;
}

bool Position::isValid() const {
    return m_xValid && m_yValid;
}

string Position::toString() const {
    string s = to_string(m_x) + ":" + to_string(m_y) + "v" + to_string(isValid());
    return s;
}
