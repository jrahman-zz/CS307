#include "Interactable.h"

Interactable::Interactable(unsigned int actorID, State startState)
	: m_ID(actorID)
	, m_currentState(startState)
{}

Interactable::~Interactable() {}

InteractableType Interactable::getInteractableType(string type) {
	// TODO

	return InteractableType::HERO;
}

shared_ptr<Interactable> Interactable::createFromJson(InteractableType type, Json::Value val) {

	switch (type) {
		case InteractableType::HERO:
			// TODO
			break;
		default:
			// TODO
			break;
	}
	return nullptr;
}
