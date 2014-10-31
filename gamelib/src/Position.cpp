#include "Position.h"

Position::Position(unsigned int x, unsigned int y) 
	: m_x(x)
	, m_y(y)
{}

Position::~Position() {}

Json::Value Position::toJson() {
	Json::Value root;
	root["x"] = m_x;
	root["y"] = m_y;
	return root;
}

unsigned int Position::getX() {
	return m_x;
}

unsigned int Position::getY() {
	return m_y;
}

void Position::setX(unsigned int x) {
	m_x = x;
}

void Position::setY(unsigned int y) {
	m_y = y;
}
