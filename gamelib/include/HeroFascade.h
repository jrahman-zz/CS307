#ifndef HERO_FASCADE_H
#define HERO_FASCADE_H

#include <memory>

#include "Hero.h"
#include "TimeKeeper.h"
#include "Util.h"

using namespace std;

/*
 * Define a interface for executing commands against your hero character
 * This class is the instance that will actually be given to the student
 * to run command against
 */
class HeroFascade {
public:
    HeroFascade(shared_ptr<Hero> hero, shared_ptr<TimeKeeper> timekeeper);
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
     * Reference to the hero object
     */
    shared_ptr<Hero> m_hero;

    /*
     * Reference to the timekeeper
     */
    shared_ptr<TimeKeeper> m_timekeeper;
private:    
};

#endif // HERO_FASCADE_H
