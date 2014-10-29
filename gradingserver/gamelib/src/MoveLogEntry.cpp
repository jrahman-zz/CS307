#include "MoveLogEntry.h"

MoveLogEntry::MoveLogEntry(
	unsigned int timestamp,
	unsigned int actorID,
	Position position) :
	LogEntry(timestep),
	actorID(actorID),
	position(position) {}

MoveLogEntry::~MoveLogEntry() {}

Json::Value MoveLogEntry::serialize() {
	Json::Value root;
	root["position"] = position.toJson();
	root["actorID"] = actorID;

	return root;
}

std::string MoveLogEntry::getType() {
	return std::string("move");
}

