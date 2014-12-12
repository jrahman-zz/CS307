#include "DialogueLogEntry.h"

DialogueLogEntry::DialogueLogEntry(
        unsigned int actorID,
        string dialogue)
    : m_actorID(actorID)
    , m_dialogue(dialogue)
{}

DialogueLogEntry::~DialogueLogEntry() {}

Json::Value DialogueLogEntry::serialize() {
    Json::Value root(Json::objectValue);
    root["dialogue"] = m_dialogue;
    root["actorID"] = m_actorID;

    return root;
}

string DialogueLogEntry::getType() {
    return string("dialogue");
}
