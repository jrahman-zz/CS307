#include "Trigger.h"

Trigger::Trigger(std::string& tName, TriggerType tType) {
  name = tName;
  type = tType;
}

TriggerType Trigger::triggerTypeFromString(std::string& str) {
  if (str == "navigation") {
    return TriggerTypeNavigation;
  }
  return TriggerTypeUnknown;
}

