#ifndef WORLD_H
#define WORLD_H

#include <memory>

#include "Util.h"

class Engine;

/*
 * The World class provides a mechanism for the player to examine the state of the world
 *
 *
 *
 */
class WorldFascade {

public:
	WorldFascade(std::shared_ptr<Engine> engineRef);
	~WorldFascade();

	bool isNPC(Direction direction);
	bool isEnemy(Direction direction);
	bool isBuilding(Direction direction);
	bool isOpen(Direction direction);
	bool isChallengeEntrance(Direction direction);
	bool isLevelExit(Direction direction);
		
protected:
	bool isNPC(unsigned int x, unsigned int y);
	bool isEnemy(unsigned int x, unsigned int y);
	bool isBuilding(unsigned int x, unsigned int y);
	bool isOpen(unsigned int x, unsigned int y);
	bool isChallengeEntrance(unsigned int x, unsigned int y);
	bool isLevelExit(unsigned int x, unsigned int y);

private:
	std::shared_ptr<Engine> engine;
};


#endif // WORLD_H
