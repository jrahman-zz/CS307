#ifndef MOVEABLE_H
#define MOVEABLE_H

#include <memory>

#include "json/json.h"
#include "MoveLogEntry.h"
#include "Interactable.h"
#include "Util.h"

class Moveable : public Interactable {
	
public:
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
	Moveable(Json::Value value);
private:
};


#endif // MOVEABLE_H
