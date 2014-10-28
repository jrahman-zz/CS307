#ifndef MOVE_COMMAND_H
#define MOVE_COMMAND_H

#include "Command.h"
#include "Moveable.h"
#include "Util.h"

class MoveCommand : public Command {
public:
	MoveCommand(Direction dir) : direction(dir) {}
	virtual ~MoveCommand() {}
	virtual bool execute(Moveable& actor) {
		return actor.move(direction);
	}
protected:
	Direction direction;

};

#endif // MOVE_COMMAND_H
