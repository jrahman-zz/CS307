#include "Interactable.h"

#include "Character.h"
#include "Hero.h"
#include "Enemy.h"

Interactable::~Interactable() {}

InteractableType Interactable::getType() const {
    return m_type;
}

bool Interactable::changeState(State newState) {
    auto observer = m_stateObserver.lock();
    if (observer == nullptr) {
        return false;
    }
    
    if (observer->onPreStateChange(*this, newState)) {
        auto oldState = m_state;
        m_state = newState;
        observer->onPostStateChange(*this, oldState);
    } else {
        return false;
    }
    return true;
}

bool Interactable::interact(Interactable& target) {
    auto observer = m_interactObserver.lock();
    if (observer == nullptr) {
        return false;
    }

    if (observer->onPreInteract(*this, target)) {
        auto ret = interact(target);
        observer->onPostInteract(*this, target);
        return ret;
    }
    return false;
}

void Interactable::registerInteractObserver(weak_ptr<InteractObserver> obs) {
    m_interactObserver = obs;
}

void Interactable::registerStateObserver(weak_ptr<StateObserver> obs) {
    m_stateObserver = obs;
}

InteractableType Interactable::getInteractableType(string type) {
    if (type == "hero") {
        return InteractableType::HERO;
    } else if (type == "enemy") {
        return InteractableType::ENEMY;
    } else if (type == "npc") {
        return InteractableType::NPC;
    }

    throw invalid_argument("Unknown InteractableType");
    return InteractableType::HERO;
}

shared_ptr<Interactable> Interactable::createFromJson(InteractableType type, Json::Value val) {

    shared_ptr<Interactable> ptr;
    switch (type) {
        case InteractableType::HERO:
            ptr = shared_ptr<Hero>(new Hero(val));
            break;
        case InteractableType::ENEMY:
            ptr = shared_ptr<Enemy>(new Enemy(val));
            break;
        case InteractableType::NPC:
            ptr = shared_ptr<Character>(new Character(val));
            break;
        default:
            break;
    }
    return ptr;
}


/*
 * ===================================================================
 */

Interactable::Interactable(Json::Value value) 
    : Positionable(value)
    , m_state(State::ALIVE) {
}

void Interactable::setInteractableType(InteractableType type) {
    m_type = type;
}
