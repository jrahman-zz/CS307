#include "Interactable.h"

#include "Hero.h"

Interactable::~Interactable() {}

InteractableType Interactable::getType() const {
    return m_type;
}

bool Interactable::changeState(State newState) {
    if (m_stateObserver->onPreStateChange(*this, m_state, newState)) {
        m_state = newState;
        m_stateObserver->onPostStateChange(*this, m_state);
    } else {
        return false;
    }
}

bool Interactable::interact(Interactable& target) {
    if (m_interactObserver->onPreInteract(*this, target)) {
        auto ret = interact(target);
        m_interactObserver->onPostInteract(*this, target);
        return true;
    }
    return false;
}

void Interactable::registerInteractObserver(shared_ptr<InteractObserver> obs) {
    m_interactObserver = obs;
}

void Interactable::registerStateObserver(shared_ptr<StateObserver> obs) {
    m_stateObserver = obs;
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


/*
 * ===================================================================
 */

Interactable::Interactable(Json::Value value) 
    : Positionable(value) {
    auto properties = value["properties"];
    m_ID = properties["id"].asInt();
    m_state = State::ALIVE;
}

void Interactable::setInteractableType(InteractableType type) {
    m_type = type;
}
