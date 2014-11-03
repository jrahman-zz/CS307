#include "Trigger.h"

Trigger::Trigger(Json::Value value) 
    : Positionable(value)
    , m_type(Trigger::typeFromString(value["type"].asString()) 
    , m_name(value["name"].asString()) {
}

string Trigger::getName() {
    return m_name;
}

TriggerType Trigger::getType() {
    return m_type;
}

TriggerType Trigger::typeFromString(string str) {
  if (str == "navigation") {
    return TriggerTypeNavigation;
  }
  return TriggerTypeUnknown;
}

