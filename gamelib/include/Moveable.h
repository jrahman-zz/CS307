#ifndef MOVEABLE_H
#define MOVEABLE_H

#include <memory>

#include "MoveLogEntry.h"
#include "Interactable.h"
#include "Util.h"

class Moveable : public Interactable {
	
public:
	Moveable(
		unsigned int actorID,
		State state = State::ALIVE);
	virtual ~Moveable();
	
	/*
	 * All of these functions return true if the move was
	 * successful, and false if not
	 */
	virtual bool moveUp();
	virtual bool moveDown();
	virtual bool moveLeft();
	virtual bool moveRight();
	virtual bool move(Direction direction);
	
protected:
private:
};


#endif // MOVEABLE_H
