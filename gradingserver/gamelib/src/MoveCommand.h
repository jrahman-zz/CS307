#ifndef MOVE_COMMAND_H
#define MOVE_COMMAND_H

#include "Command.h"
#include "Util.h"

class MoveCommand : public Command {
public:
	MoveCommand(Direction dir) : direction(dir) {}
	virtual ~MoveCommand() {}
	virtual bool execute(Moveable& actor) {
		actor.move(direction);
	}
proected:
	Direction direction;

}

#endif // MOVE_COMMAND_H
