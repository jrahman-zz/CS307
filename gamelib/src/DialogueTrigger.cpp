#include "DialogueTrigger.h"

DialogueTrigger::DialogueTrigger(Json::Value value)
    : Trigger(value)
{}

DialogueTrigger::~DialogueTrigger() {}

bool DialogueTrigger::triggerImpl(Interactable& target) {
    return true; // TODO
}
