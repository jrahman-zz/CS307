#include "Trigger.h"

#include "DialogueTrigger.h"
#include "LevelExitTrigger.h"
#include "ObjectiveTrigger.h"

#include "Moveable.h"

Trigger::Trigger(Json::Value value) 
    : Positionable(value)
    , m_name(std::move(value["name"].asString())) 
    , m_type(Trigger::typeFromString(value["type"].asString()))
    , m_repeatable(stoi(value["properties"].get("repeatable", "0").asString()))
    , m_stopMovement(stoi(value["properties"].get("stopMove", "1").asString()))
    , m_triggerTarget(stoi(value["properties"].get("triggerTarget", "-1").asString()))
    , m_triggered(false)
{}

Trigger::~Trigger() {}

bool Trigger::arrive(Interactable& target, shared_ptr<GameState> state) {
    if ((m_triggerTarget < 0 || m_triggerTarget == target.getID()) && isTriggerable()) {
        m_triggered = arriveImpl(target, state);
        if (m_triggered && m_stopMovement) {
            dynamic_cast<Moveable&>(target).setCanMove(false);
        }
    } else {
        return false; // Didn't activate trigger
    }
    return m_triggered;
}

bool Trigger::leave(Interactable& target, shared_ptr<GameState> state) {
    if (m_triggerTarget < 0 || m_triggerTarget == target.getID()) {
        auto ret = leaveImpl(target, state);
        return ret;
    } else {
        return false; // What exactly is the meaning of this return value??
    }
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
        case TriggerType::OBJECTIVE:
            ptr = shared_ptr<ObjectiveTrigger>(new ObjectiveTrigger(value));
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
    } else if (!str.compare("objective")) {
        return TriggerType::OBJECTIVE;
    }

    return TriggerType::UNKNOWN;
}

