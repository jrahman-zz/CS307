#include "Enemy.h"

Enemy::Enemy(Json::Value value)
    : Moveable(value)
{
    setInteractableType(InteractableType::ENEMY);
}

Enemy::~Enemy() {
}

bool Enemy::interact(Interactable& target) {
    return target.interact(*this);
}

bool Enemy::interact_impl(Hero& target) {
    // TODO
    return true;
}

bool Enemy::interact_impl(Enemy& target) {
    // TODO
    return true;
}
