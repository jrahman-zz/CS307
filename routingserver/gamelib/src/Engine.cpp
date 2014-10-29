#include "Engine.h"

Engine::Engine(std::shared_ptr<GameLevel> gameLevel) :
	level(gameLevel), isActive(true), heroID(0) {}

Engine::~Engine() {}

std::shared_ptr<WorldFascade> Engine::getWorld() const {
	std::shared_ptr<Engine> self(this);
	std::shared_ptr<WorldFascade> world(new WorldFascade(self));
	return world;
}

std::shared_ptr<HeroFascade> Engine::getHero() const {
	std::shared_ptr<Engine> self(this);
	std::shared_ptr<HeroFascade> hero(new HeroFascade(self, getHeroID()));
	return hero;
}

bool Engine::executeCommand(unsigned int actorID, std::shared_ptr<Command> cmd) {
	// TODO, how will this integrate with the logging mechanism
	
	Interactable i(Position(0, 0), 0, std::weak_ptr<Engine>(this), State::ALIVE); // TODO, lookup interactable
	return (*cmd)(i);
}

void Engine::resetEngine() {
	// TODO
}

unsigned int Engine::getHeroID() const {
	return heroID;
}
