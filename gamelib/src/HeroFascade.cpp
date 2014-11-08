#include "HeroFascade.h"

#include "Engine.h"

HeroFascade::HeroFascade(shared_ptr<Hero> hero, shared_ptr<TimeKeeper> timekeeper)
    : m_hero(hero)
    , m_timekeeper(timekeeper)
{}

HeroFascade::~HeroFascade() {}

unsigned int HeroFascade::moveUp(unsigned int distance) {
    return move(Direction::UP, distance);
}

unsigned int HeroFascade::moveDown(unsigned int distance) {
    return move(Direction::DOWN, distance);
}

unsigned int HeroFascade::moveLeft(unsigned int distance) {
    return move(Direction::LEFT, distance);
}

unsigned int HeroFascade::moveRight(unsigned int distance) {
    return move(Direction::RIGHT, distance);
}

unsigned int HeroFascade::move(Direction direction, unsigned int distance) {
    unsigned int distanceTraveled = 0;
    while (distance-- > 0 && m_hero->move(direction)) {
        m_timekeeper->incrementClock();
        distanceTraveled++;
    }
    return distanceTraveled;
}
