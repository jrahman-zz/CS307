#include "Hero.h"


Hero::Hero(Json::Value value)
    : Moveable(value) {
    setInteractableType(InteractableType::HERO);
}

Hero::~Hero() {}


bool Hero::interact(Interactable& obj) {
    // Dispatch to objs impl for Hero
    return obj.interact(*this);
}

bool Hero::interact_impl(Hero& hero) {
    // TODO
    return true;
}

bool Hero::interact_impl(Enemy& enemy) {
    // TODO
    return true;
}
