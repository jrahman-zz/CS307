#include "Position.h"

Position::Position(unsigned int x, unsigned int y) :
	x(x), y(y) {}

Position::~Position() {}

Json::Value Position::toJson() {
	Json::Value root;
	root["x"] = x;
	root["y"] = y;
	return root;
}

unsigned int Position::getX() {
	return x;
}

unsigned int Position::getY() {
	return y;
}

void Position::setX(unsigned int x) {
	this->x = x;
}

void Position::setY(unsigned int y) {
	this->y = y;
}
