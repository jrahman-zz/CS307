#include "HeroFascade.h"

HeroFascade::HeroFascade(std::shared_ptr<Engine> engineRef, unsigned int heroID) :
	engine(engineRef),
	heroID(heroID) {}

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
	auto ptr = std::shared_ptr<Command>(new MoveCommand(direction, distance));
	return engine->executeCommand(heroID, ptr);
}
