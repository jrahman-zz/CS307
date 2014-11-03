#pragma once

#include <string>

#include "json/json.h"
#include "Interactable.h"

using namespace std;

typedef enum {
    TriggerTypeUnknown,
    TriggerTypeNavigation
} TriggerType;

class Trigger : public Interactable {
public:
    Trigger(Json::Value value);

    static TriggerType triggerTypeFromString(string& str);

protected:

    string m_name;
    TriggerType m_type;
private:
};

