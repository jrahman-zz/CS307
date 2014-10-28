#ifndef ENGINE_H
#define ENGINE_H

#include <memory>
#include <string>

#include "ActionLog.h"
#include "GameLevel.h"
#include "HeroFascade.h"
#include "WorldFascade.h"

/*
 * Core class for game engine
 *
 *
 */
class Engine {
public:
	Engine(std::shared_ptr<GameLevel> gameLevel); // TODO, add scripting, etc
	~Engine();

	std::shared_ptr<WorldFascade> getWorld() const;
	std::shared_ptr<HeroFascade> getHero() const;
	
	std::shared_ptr<ActionLog> getActionLog() const;
	void resetEngine();

protected:

private:
	std::shared_ptr<GameLevel> level;
	std::shared_ptr<ActionLog> actions;
};

#endif // ENGINE_H
