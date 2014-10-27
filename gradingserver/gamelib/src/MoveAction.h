#ifndef MOVE_ACTION_H
#define MOVE_ACTION_H

#include <memory>

#include "Action.h"
#include "Util.h"

class MoveAction : public Move {
public:
	MoveAction(std::shared_ptr<Moveable> actor, Direction direction, unsigned int time);
	virtual ~MoveAction();
	virtual void toJson();
protected:

private:
}


#endif // MOVE_ACTION_H
