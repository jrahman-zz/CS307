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
	
	bool executeCommand(unsigned int actorID, std::shared_ptr<Command> cmd);

	std::shared_ptr<ActionLog> getActionLog() const;
	void resetEngine();
protected:

	unsigned int getHeroID() const;
	
	/*
	 * Return string representation of the JSON log
 	 */
	std::string getLog();
private:
	std::shared_ptr<GameLevel> level;
	std::shared_ptr<ActionLog> actions;

	unsigned int heroID;

	/*
	 * Flag controlling if engine should continue to accept
	 * commands controlling the character
 	 */
	bool isActive;
};

#endif // ENGINE_H
