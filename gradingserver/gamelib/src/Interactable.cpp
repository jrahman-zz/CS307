#include "Interactable.h"

Interactable::Interactable(unsigned int x, unsigned int y, unsigned int actorID, State startState) :
	currentState(startState),
	ID(actorID) {
}

Interactable::~Interactable() {
}


