#include "HeroFascade.h"

#include "Engine.h"

HeroFascade::HeroFascade(shared_ptr<Engine> engineRef, unsigned int heroID)
	: m_engine(engineRef)
	, m_heroID(heroID)
{}

HeroFascade::~HeroFascade() {}

bool HeroFascade::moveUp(unsigned int distance) {
	return move(Direction::UP, distance);
}

bool HeroFascade::moveDown(unsigned int distance) {
	return move(Direction::DOWN, distance);
}

bool HeroFascade::moveLeft(unsigned int distance) {
	return move(Direction::LEFT, distance);
}

bool HeroFascade::moveRight(unsigned int distance) {
	return move(Direction::RIGHT, distance);
}

bool HeroFascade::move(Direction direction, unsigned int distance) {
	auto ptr = shared_ptr<Command>(new MoveCommand(direction, distance));
	return m_engine->executeCommand(m_heroID, ptr);
}
