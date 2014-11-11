#include "LevelExitTrigger.h"

LevelExitTrigger::LevelExitTrigger(Json::Value value)
    : Trigger(value)
{}

LevelExitTrigger::~LevelExitTrigger() {}

bool LevelExitTrigger::arriveImpl(Interactable& target, shared_ptr<GameState> state) {
    state->setLevelOver(true);
    state->setCanMove(false);
    return true;
}

bool LevelExitTrigger::leaveImpl(Interactable& target, shared_ptr<GameState> state) {

    return true;
}
