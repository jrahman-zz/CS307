#include "MoveCommand.h"

MoveCommand::MoveCommand(Direction direction, unsigned int distance)
    : m_direction(direction)
    , m_distance(distance)
{}

MoveCommand::~MoveCommand() {}

shared_ptr<LogEntry> MoveCommand::execute(Interactable& actor) {
    
    shared_ptr<LogEntry> ret = nullptr;

    try {
        auto target = dynamic_cast<Moveable&>(actor);
        // TODO, handle multispace move 
    } catch (std::bad_cast e) {
        return nullptr;
    }

    return ret;
}
