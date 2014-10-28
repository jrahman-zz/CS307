#ifndef MOVE_COMMAND_H
#define MOVE_COMMAND_H

#include "Command.h"
#include "Moveable.h"
#include "Util.h"

class MoveCommand : public Command {
public:
	/*
	 *
	 */
	MoveCommand(Direction dir, distance);
	
	virtual ~MoveCommand();
protected:
	/*
	 * Direction the move is taking place in
	 */
	Direction direction;

	/*
	 * Distance the move should travel
 	 */
	unsigned int distance;
};

#endif // MOVE_COMMAND_H
