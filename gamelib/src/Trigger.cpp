#include "Trigger.h"

#include "DialogueTrigger.h"
#include "LevelExitTrigger.h"

Trigger::Trigger(Json::Value value) 
    : Positionable(value)
    , m_type(Trigger::typeFromString(value["type"].asString()))
    , m_name(std::move(value["name"].asString()))
    , m_repeatable(value["properties"].get("repeatable", false).asBool())
    , m_stopMovement(value["properties"].get("stopMove", true).asBool())
    , m_triggerTarget(value["properties"].get("triggerTarget", -1).asInt())
    , m_triggered(false)
{}

Trigger::~Trigger() {}

bool Trigger::trigger(Interactable& target) {
    if ((m_triggerTarget < 0 || m_triggerTarget == target.getID()) && isTriggerable()) {
        m_triggered = triggerImpl(target);
    } else {
        return false; // Didn't activate trigger
    }
    return m_triggered;
}

bool Trigger::isTriggerable() const {
    return (m_repeatable && m_triggered) || !m_triggered;
}

string Trigger::getName() const {
    return m_name;
}

TriggerType Trigger::getType() const {
    return m_type;
}

bool Trigger::isTriggered() const {
    return m_triggered;
}

bool Trigger::isRepeatable() const {
    return m_repeatable;
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
        default:
            throw invalid_argument("Unknown trigger type");
    }
    return ptr;
}

TriggerType Trigger::typeFromString(string str) {
  if (!str.compare("levelexit")) {
    return TriggerType::LEVELEXIT;
  } else if (!str.compare("dialogue")) {
    return TriggerType::DIALOGUE;
  }

  return TriggerType::UNKNOWN;
}

