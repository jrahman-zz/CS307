#ifndef MOVE_COMMAND_H
#define MOVE_COMMAND_H

#include <memory>

#include "Command.h"
#include "Moveable.h"
#include "Util.h"

using namespace std;

class MoveCommand : public Command {
public:
    /*
     *
     */
    MoveCommand(Direction dir, unsigned int distance);
    
    virtual ~MoveCommand();
protected:

    virtual shared_ptr<LogEntry> execute(Interactable& actor);

    /*
     * Direction the move is taking place in
     */
    Direction m_direction;

    /*
     * Distance the move should travel
     */
    unsigned int m_distance;
};

#endif // MOVE_COMMAND_H
