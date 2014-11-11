#include "Trigger.h"

#include "DialogueTrigger.h"
#include "LevelExitTrigger.h"

Trigger::Trigger(Json::Value value) 
    : Positionable(value)
    , m_type(Trigger::typeFromString(value["type"].asString()))
    , m_name(std::move(value["name"].asString()))
{}

string Trigger::getName() const {
    return m_name;
}

TriggerType Trigger::getType() const {
    return m_type;
}

shared_ptr<Trigger> Trigger::createFromJson(TriggerType type, Json::Value value) {
    shared_ptr<Trigger> ptr;
    switch (type) {
        case TriggerType::LEVELEXIT:
            ptr = shared_ptr<LevelExitTrigger>(new LevelExitTrigger(value));
            break;
        case TriggerType::DIALOGUE:
            ptr = shared_ptr<DialogueTrigger>(new DialogueTrigger(value));
            break;
    }
    return ptr;
}

TriggerType Trigger::typeFromString(string str) {
  if (!str.compare("levelexit")) {
    return TriggerType::LEVELEXIT;
  } else if (!str.compare("dialogue")) {
    return TriggerType::DIALOGUE;
  }

  // TODO, expand this trigger list
  // TODO, possiblly create subclass for different types of triggers
  return TriggerType::UNKNOWN;
}

