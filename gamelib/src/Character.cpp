#include "Character.h"

Character::Character(Json::Value value)
    : Moveable(value)
{
    setInteractableType(InteractableType::NPC);
}

Character::~Character() {
}

bool Character::interact(Interactable& target) {
    return target.interact(*this);
}

bool Character::interact_impl(Hero& target) {
    // TODO
    return true;
}

bool Character::interact_impl(Enemy& target) {
    // TODO
    return true;
}
