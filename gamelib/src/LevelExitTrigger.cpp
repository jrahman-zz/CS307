#include "LevelExitTrigger.h"

LevelExitTrigger::LevelExitTrigger(Json::Value value)
    : Trigger(value)
    , m_nextLevelID(stoi(value["properties"]["nextLevel"].asString()))
{}

LevelExitTrigger::~LevelExitTrigger() {}

bool LevelExitTrigger::arriveImpl(Interactable& target, shared_ptr<GameState> state) {
    state->setLevelOver(true);
    state->setNextLevel(m_nextLevelID);

    return true;
}

bool LevelExitTrigger::leaveImpl(Interactable& target, shared_ptr<GameState> state) {

    return true;
}
