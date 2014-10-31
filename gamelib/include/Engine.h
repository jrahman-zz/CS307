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

using namespace std;

/*
 * Core class for game engine
 */
class Engine : public BaseManager {
public:
	Engine(string levelJson); // TODO, add scripting, etc
	~Engine();

	std::shared_ptr<WorldFascade> getWorld() const;
	std::shared_ptr<HeroFascade> getHero() const;
	
	bool sendMessage(BaseMessage* msg);
	bool executeCommand(unsigned int actorID, shared_ptr<Command> cmd);

	unsigned int getTimestep() const;

	shared_ptr<ActionLog> getActionLog() const;
	void resetEngine();
protected:

	unsigned int getHeroID() const;

private:
	std::shared_ptr<GameLevel> m_level;
	std::shared_ptr<ActionLog> m_actions;

	unsigned int m_heroID;

	/*
	 * Flag controlling if engine should continue to accept
	 * commands controlling the character
 	 */
	bool m_isActive;

	/*
 	 * Store a copy of the Json defining the level, in case of reset
 	 */
	string m_levelJson;

	/*
	 * Log to record actions and events for recording
 	 */
	shared_ptr<ActionLog> m_log;

	unsigned int m_timestep;
};

#endif // ENGINE_H
