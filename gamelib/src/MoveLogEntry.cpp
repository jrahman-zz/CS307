#include "MoveLogEntry.h"

MoveLogEntry::MoveLogEntry(
    unsigned int actorID,
    Position position)
    : m_actorID(actorID)
    , m_position(position)
{}

MoveLogEntry::~MoveLogEntry() {}

Json::Value MoveLogEntry::serialize() {
    Json::Value root(Json::objectValue);
    root["position"] = m_position.toJson();
    root["actorID"] = m_actorID;

    return root;
}

string MoveLogEntry::getType() {
    return string("move");
}
