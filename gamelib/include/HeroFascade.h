#ifndef HERO_FASCADE_H
#define HERO_FASCADE_H

#include <memory>

#include "Command.h"
#include "MoveCommand.h"
#include "Util.h"

using namespace std;

/* Forward delcaration */
class Engine;

/*
 * Define a interface for executing commands against your hero character
 * This class is the instance that will actually be given to the student
 * to run command against
 */
class HeroFascade {
public:
	HeroFascade(shared_ptr<Hero> hero);
	~HeroFascade();
	
	unsigned int moveUp(unsigned int distance = 1);
	unsigned int moveDown(unsigned int distance = 1);
	unsigned int moveLeft(unsigned int distance = 1);
	unsigned int moveRight(unsigned int distance = 1);

protected:
		
	/*
	 * Primary movement implementation
	 */	
	unsigned int move(Direction direction, unsigned int distance = 1);

	/*
	 * Reference to the game engine object
	 */
	shared_ptr<Hero> m_hero;
private:	
};

#endif // HERO_FASCADE_H
