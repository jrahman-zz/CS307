#include "Interactable.h"

Interactable::Interactable(Position position, unsigned int actorID, State startState) :
	position(position),
	currentState(startState),
	ID(actorID) {}

Interactable::~Interactable() {}


