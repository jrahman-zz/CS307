#ifndef MOVE_MESSAGE_H
#define MOVE_MESSAGE_H

class MoveMessage : public BaseMessage {
public:
	MoveMessage(unsigned int targetID)
	: BaseMessage(MessageType::MOVE, targetID)
}

#endif
