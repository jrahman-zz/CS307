#include "ObjectiveLogEntry.h"

ObjectiveLogEntry::ObjectiveLogEntry(
        string dialogue,
        string prompt,
        string templateCode,
        int objectiveId) 
    : LogEntry()
    , m_dialogue(dialogue)
    , m_prompt(prompt)
    , m_templateCode(templateCode)
    , m_objectiveId(objectiveId)
{}

ObjectiveLogEntry::~ObjectiveLogEntry() {
}

Json::Value ObjectiveLogEntry::serialize() {
    Json::Value root(Json::objectValue);
    root["dialogue"] = m_dialogue;
    root["prompt"] = m_prompt;
    root["templateCode"] = m_templateCode;
    root["objectiveId"] = m_objectiveId;

    return root;
}

string ObjectiveLogEntry::getType() {
    return "objective";
}
