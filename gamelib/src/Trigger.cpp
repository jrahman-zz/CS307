#include "Trigger.h"

Trigger::Trigger(Json::Value value) 
    : Positionable(value) {
    m_name = value["name"].asString();
    m_type = Trigger::typeFromString(value["type"].asString());    
}

string Trigger::getName() const {
    return m_name;
}

TriggerType Trigger::getType() const {
    return m_type;
}

TriggerType Trigger::typeFromString(string str) {
  if (str == "navigation") {
    return TriggerTypeNavigation;
  }

  // TODO, expand this trigger list
  // TODO, possiblly create subclass for different types of triggers
  return TriggerTypeUnknown;
}

