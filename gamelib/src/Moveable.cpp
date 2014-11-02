#include "Moveable.h"

#include "Engine.h"

Moveable::Moveable(unsigned int actorID, State state)
	: Interactable(actorID, state)
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
	//unsigned int timestep = m_engine->getTimestep();

	// TODO, update position

	Position position(0, 0);
	//shared_ptr<MoveLogEntry> entry(new MoveLogEntry(timestep, true, m_ID, position));
	//m_engine->getActionLog()->log(entry);
	//return entry->getResult();
	return true;
}

