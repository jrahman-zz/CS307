#include "DialogueTrigger.h"

#include "DialogueLogEntry.h"

DialogueTrigger::DialogueTrigger(Json::Value value)
    : Trigger(value)
    , m_dialogue(value["properties"]["dialogue"].asString())
    , m_sourceActor(stoi(value["properties"]["actor"].asString()))
{}

DialogueTrigger::~DialogueTrigger() {}

bool DialogueTrigger::arriveImpl(Interactable& target, shared_ptr<GameState> state) {
    log(shared_ptr<DialogueLogEntry>(new DialogueLogEntry(m_sourceActor, m_dialogue)));
    return true;
}

bool DialogueTrigger::leaveImpl(Interactable& target, shared_ptr<GameState> state) {

    return true;
}
