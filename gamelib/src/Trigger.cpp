#include "Trigger.h"

Trigger::Trigger(Json::Value value) 
	: m_type(Trigger::typeFromString(value["type"].asString()) 
	, m_name(value["name"].asString()) {
}

TriggerType Trigger::typeFromString(string str) {
  if (str == "navigation") {
    return TriggerTypeNavigation;
  }
  return TriggerTypeUnknown;
}

