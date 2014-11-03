#include "Interactable.h"

#include "Hero.h"

Interactable::~Interactable() {}

unsigned int Interactable::getID() {
    return m_ID;
}

InteractableType Interactable::getType() {
    return m_type;
}

bool Interactable::changeState(State newState) {
    if (observer->onPreStateChange(*this, m_state, newState)) {
        m_state = newState;
        observer->onPostStateChange(*this, m_state);
    } else {
        return false;
    }
}

bool Interactable::interact(Interactable& target) {
    if (observer->onPreInteract(*this, target)) {
        interact_impl(target);
        observer->onPostInteract(*this, target);
    } else {
        return false;
    }
}

Position Interactable::getPosition() {
    return m_position;
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
    : m_position(value["x"].asInt(), value["y"].asInt()) {
    auto properties = value["properties"];
    m_ID = properties["id"].asInt();
    m_state = State::ALIVE;
}

bool Interactable::interact_impl(Interactable& target) {
    target.interact_impl(*this);
}
