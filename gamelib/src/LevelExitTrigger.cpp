#include "LevelExitTrigger.h"

LevelExitTrigger::LevelExitTrigger(Json::Value value)
    : Trigger(value)
{}

LevelExitTrigger::~LevelExitTrigger() {}

bool LevelExitTrigger::triggerImpl(Interactable& target) {
    return true; // TODO
}
