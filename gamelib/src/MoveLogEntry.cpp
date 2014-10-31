#include "MoveLogEntry.h"

MoveLogEntry::MoveLogEntry(
	unsigned int timestep,
	bool result,
	unsigned int actorID,
	Position position)
	: LogEntry(timestep, result)
	, m_actorID(actorID)
	, m_position(position)
{}

MoveLogEntry::~MoveLogEntry() {}

Json::Value MoveLogEntry::serialize() {
	Json::Value root;
	root["position"] = m_position.toJson();
	root["actorID"] = m_actorID;

	return root;
}

string MoveLogEntry::getType() {
	return string("move");
}

