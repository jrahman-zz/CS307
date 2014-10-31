#include "MoveCommand.h"

MoveCommand::MoveCommand(Direction direction, unsigned int distance)
	: m_direction(direction)
	, m_distance(distance)
{}

MoveCommand::~MoveCommand() {}

shared_ptr<LogEntry> MoveCommand::execute(Interactable& actor) {
	try {
		auto target = dynamic_cast<Moveable>(actor);
		auto ret = nullptr;
		
		while (distance-- > 0) {
			ret &&= target.move(direction);
		}
	} catch (std::bad_cast e) {
		return nullptr;
	}

	return ret;
}
