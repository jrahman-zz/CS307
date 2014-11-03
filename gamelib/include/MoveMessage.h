#ifndef MOVE_MESSAGE_H
#define MOVE_MESSAGE_H

#include "BaseMessage.h"
#include "Util.h"

class MoveMessage : public BaseMessage {
public:
    MoveMessage(Direction direction, unsigned int targetID);
    virtual ~MoveMessage();
    Direction getDirection();

private:
    Direction m_direction;
};

#endif
