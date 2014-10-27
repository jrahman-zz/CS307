#ifndef HERO_FASCADE_H
#define HERO_FASCADE_H

#include <memory>

#include "Command.h"
#include "MoveCommand.h"
#include "Util.h"


/*
 * Define a interface for executing commands against your hero character
 * This class is the instance that will actually be given to the student
 * to run command against
 */
class HeroFascade {
public:
	HeroFascade(std::shared_ptr<Engine> engineRef) : engine(engineRef) {}
	~HeroFascade()
	
	bool moveUp(unsigned int distance = 1) { move(Direction.UP, distance); }
	bool moveDown(unsigned int distance = 1) { move(Direction.DOWN, distance); };
	bool moveLeft(unsigned int distance = 1) { move(Direction.LEFT, distance); };
	bool moveRight(unsigned int distance = 1) { move(Direction.RIGHT, distance); };

	// TODO IMPLEMENT THIS
	bool move(Direction direction, unsigned int distance = 1);

protected:

private:	
}

#endif // HERO_FASCADE_H
