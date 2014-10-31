#include "Engine.h"

Engine::Engine(string levelJson)
	: m_levelJson(levelJson)
	, m_isActive(true)
	, m_heroID(0)
{
	m_level = shared_ptr<GameLevel>(new GameLevel(m_levelJson));	
}

Engine::~Engine() {}

shared_ptr<WorldFascade> Engine::getWorld() const {
	shared_ptr<Engine> self(const_cast<Engine*>(this));
	shared_ptr<WorldFascade> world(new WorldFascade(self));
	return world;
}

shared_ptr<HeroFascade> Engine::getHero() const {
	shared_ptr<Engine> self(const_cast<Engine*>(this));
	shared_ptr<HeroFascade> hero(new HeroFascade(self, getHeroID()));
	return hero;
}

bool Engine::executeCommand(unsigned int actorID, shared_ptr<Command> cmd) {
	// TODO, how will this integrate with the logging mechanism
	
	auto actor = (*m_level)[Position(0, 0)];
	auto log = (*cmd)(*actor);
	
	m_log->log(log);
	return log->getResult();
}

void Engine::resetEngine() {

	/* Dtor will be called on old m_level by shared_ptr */
	m_level = shared_ptr<GameLevel>(new GameLevel(m_levelJson));
}

unsigned int Engine::getTimestep() const {
	return m_timestep;
}

unsigned int Engine::getHeroID() const {
	return m_heroID;
}
