#include "Moveable.h"


Moveable::Moveable(unsigned int x, unsigned int y, unsigned int actorID, State state = State.ALIVE) :
	Interactable(x, y, actorId, state) {

}


Moveable::~Moveable() {

}

virtual bool Moveable::moveUp() {
	return move(Direction.UP);
}

virtual bool Moveable::moveDown() {
	return move(Direction.DOWN);
}

virtual bool Moveable::moveLeft() {
	return move(Direction.LEFT);
}

virtual bool Moveable::moveRight() {
	return move(Direction.RIGHT);
}

virtual bool Moveable::move(Direction direction) {
	// TODO Implement
	return false;
}

