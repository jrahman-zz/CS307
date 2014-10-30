#include "Moveable.h"

Moveable::Moveable(
		unsigned int actorID,
		Engine* engineRef,
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
	unsigned int timestep = engine->getTimestep();

	// TODO, update position

	std::shared_ptr<MoveLogEntry> entry(new MoveLogEntry(timestep, ID, position));
	engine->getActionLog()->log(entry);
	return true;
}

