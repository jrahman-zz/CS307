#include "Interactable.h"

Interactable::Interactable(
	Position position,
	unsigned int actorID,
	std::weak_ptr<Engine> engineRef,
	State startState) :
	position(position),
	currentState(startState),
	ID(actorID),
	engine(engineRef) {}

Interactable::~Interactable() {}
