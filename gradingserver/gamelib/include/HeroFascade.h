#ifndef HERO_FASCADE_H
#define HERO_FASCADE_H

#include <memory>

#include "Command.h"
#include "MoveCommand.h"
#include "Util.h"

/* Forward delcaration */
class Engine;

/*
 * Define a interface for executing commands against your hero character
 * This class is the instance that will actually be given to the student
 * to run command against
 */
class HeroFascade {
public:
	HeroFascade(std::shared_ptr<Engine> engineRef, unsigned int heroID);
	~HeroFascade();
	
	bool moveUp(unsigned int distance = 1);
	bool moveDown(unsigned int distance = 1);
	bool moveLeft(unsigned int distance = 1);
	bool moveRight(unsigned int distance = 1);

protected:
		
	/*
	 * Primary movement implementation
	 */	
	bool move(Direction direction, unsigned int distance = 1);

	/*
	 * Reference to the game engine object
	 */
	std::shared_ptr<Engine> engine;
	unsigned int heroID;
private:	
};

#endif // HERO_FASCADE_H
