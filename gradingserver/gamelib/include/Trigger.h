#pragma once

#include <string>

typedef enum {
  TriggerTypeUnknown,
  TriggerTypeNavigation
} TriggerType;

class Trigger {
  public:
    std::string name;
    TriggerType type;

    Trigger(std::string& tName, TriggerType tType);

    static TriggerType triggerTypeFromString(std::string& str);

  protected:
  private:
};


