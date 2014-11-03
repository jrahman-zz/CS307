#include "Hero.h"


Hero::Hero(Json::Value value)
    : Moveable(value) {
    m_type = InteractableType::HERO;
}

Hero::~Hero() {}
