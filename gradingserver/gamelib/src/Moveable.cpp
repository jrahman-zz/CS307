#include "Moveable.h"


Moveable::Moveable(
		Position position,
		unsigned int actorID,
		std::weak_ptr<Engine> engineRef,
		State state) :
	Interactable(position, actorId, engineRef, state, engineRef) {}


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

