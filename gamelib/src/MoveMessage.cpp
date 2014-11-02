#include "MoveMessage.h"

MoveMessage::MoveMessage(
	Direction direction,
	unsigned int targetID) 
	: BaseMessage(MessageType::MOVE, targetID)
	, m_direction(direction)
{}

MoveMessage::~MoveMessage() {}

Direction MoveMessage::getDirection() {
	return m_direction;
}
