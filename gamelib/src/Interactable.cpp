#include "Interactable.h"

Interactable::Interactable(
	Position position,
	unsigned int actorID,
	Engine* engineRef,
	State startState) :
	position(position),
	currentState(startState),
	ID(actorID),
	engine(engineRef) {}

Interactable::~Interactable() {}
