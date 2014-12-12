#include "RotateLogEntry.h"

RotateLogEntry::RotateLogEntry(
    unsigned int actorID,
    Rotation rotation)
    : m_actorID(actorID)
    , m_rotation(rotation)
{}

RotateLogEntry::~RotateLogEntry() {}

Json::Value RotateLogEntry::serialize() {
    Json::Value root(Json::objectValue);
    unsigned int s;
    switch (m_rotation) { // TODO, make this a function
        case Rotation::R0:
            s = 0;
            break;
        case Rotation::R90:
            s = 90;
            break;
        case Rotation::R180:
            s = 180;
            break;
        case Rotation::R270:
            s = 270;
            break;
        default:
            s = 0;
    }
    root["rotation"] = s;
    root["actorID"] = m_actorID;

    return root;
}

string RotateLogEntry::getType() {
    return string("rotate");
}
