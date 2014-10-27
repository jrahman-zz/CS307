#ifndef ENGINE_H
#define ENGINE_H

#include <memory>

#include "GameLevel.h"
#include "ActionLog.h"

/*
 * Core class for game engine
 *
 *
 */
class Engine {
public:
	Engine(std::shared_ptr<GameLevel> gameLevel) : level(gameLevel) {}; // TODO, add scripting, etc
		

protected:

private:
	std::shared_ptr<GameLevel> level;
	std::shared_ptr<ActionLog> actions;
}

#endif // ENGINE_H
