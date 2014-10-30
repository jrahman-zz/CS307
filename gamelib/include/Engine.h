#ifndef ENGINE_H
#define ENGINE_H

#include <memory>
#include <string>

#include "BaseMessage.h"
#include "BaseManager.h"

#include "ActionLog.h"
#include "GameLevel.h"
#include "HeroFascade.h"
#include "WorldFascade.h"

/*
 * Core class for game engine
 *
 *
 */
class Engine : public BaseManager {
public:
	Engine(std::string jsonLevel); // TODO, add scripting, etc
	~Engine();

	std::shared_ptr<WorldFascade> getWorld() const;
	std::shared_ptr<HeroFascade> getHero() const;
	
	bool sendMessage(BaseMessage* msg);
	bool executeCommand(unsigned int actorID, std::shared_ptr<Command> cmd);

	std::shared_ptr<ActionLog> getActionLog() const;
	void resetEngine();
protected:

	unsigned int getHeroID() const;

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
