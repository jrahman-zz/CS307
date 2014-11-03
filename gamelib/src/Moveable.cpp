#include "Moveable.h"

Moveable::Moveable(Json::Value value)
	: Interactable(value)
{}


Moveable::~Moveable() {

}

bool Moveable::moveUp() {
	return move(Direction::UP);
}

bool Moveable::moveDown() {
	return move(Direction::DOWN);
}

bool Moveable::moveLeft() {
	return move(Direction::LEFT);
}

bool Moveable::moveRight() {
	return move(Direction::RIGHT);
}

bool Moveable::move(Direction direction) {
	int dx = 0, dy = 0;
	switch (direction) {
		case Direction::UP:
			dy = -1;
			break;
		case Direction::DOWN:
			dy = 1;
			break;
		case Direction::LEFT:
			dx = -1;
			break;
		case Direction::RIGHT:
			dx = 1;
			break;
	}
	Position next(m_position.getX() + dx, m_position.getY() + dy);
	if (observer->onPreMove(*this, m_position, next)) {
		m_position = next;
		observer->onPostMove(*this, m_position);`
	} else {
		return false;
	}
}

