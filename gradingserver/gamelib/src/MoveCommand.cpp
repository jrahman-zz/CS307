#include "MoveCommand.h"

MoveCommand::MoveCommand(Direction direction, unsigned int distance) :
	direction(direction), distance(distance) {};

MoveCommand::~MoveCommand() {};

virtual bool MoveCommand::execute(Interactable& actor) {
	try {
		auto target = dynamic_cast<Moveable>(actor);
		bool ret = true;
		
		while (distance-- > 0) {
			ret &&= target.move(direction);
		}
	} catch (std::bad_cast e) {
		return false;
	}

	return ret;
}
