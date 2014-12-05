#include "ObjectiveTrigger.h"

#include "ObjectiveLogEntry.h"

ObjectiveTrigger::ObjectiveTrigger(Json::Value value)
    : Trigger(value)
    , m_dialogue(value["properties"]["dialogue"].asString())
    , m_prompt(value["properties"]["prompt"].asString())
    , m_templateCode(value["properties"].get("templateCode", "").asString())
    , m_objectiveID(stoi(value["properties"]["objectiveId"].asString()))
{
    if (isRepeatable()) {
        throw runtime_error("Objective triggers not allowed to repeat");
    }
}

ObjectiveTrigger::~ObjectiveTrigger() {}

bool ObjectiveTrigger::arriveImpl(Interactable& target, shared_ptr<GameState> state) {
    log(shared_ptr<ObjectiveLogEntry>(
                new ObjectiveLogEntry(m_dialogue, m_prompt, m_templateCode, m_objectiveID))
    );

    // Update the current objective ID
    state->setCurrentObjectiveID(m_objectiveID);

    return true;
}

bool ObjectiveTrigger::leaveImpl(Interactable& target, shared_ptr<GameState> state) {
    return true;
}
