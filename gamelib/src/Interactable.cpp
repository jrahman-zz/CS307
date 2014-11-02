#include "Interactable.h"

#include "Hero.h"

Interactable::Interactable(Json::Value value) {
	m_ID = value["id"].asInt();
	m_state = State::ALIVE;
}

Interactable::~Interactable() {}

unsigned int Interactable::getID() {
	return m_ID;
}

InteractableType Interactable::getType() {
	return m_type;
}

InteractableType Interactable::getInteractableType(string type) {
	// TODO
	
	if (type == "hero") {
		return InteractableType::HERO;
	}

	return InteractableType::HERO;
}

shared_ptr<Interactable> Interactable::createFromJson(InteractableType type, Json::Value val) {

	shared_ptr<Interactable> ptr;
	switch (type) {
		case InteractableType::HERO:
			ptr = shared_ptr<Hero>(new Hero(val));
			break;
		default:
			ptr = nullptr;
			break;
	}
	return ptr;
}
