#pragma once

#include <string>

#include "json/json.h"
#include "Interactable.h"

using namespace std;

typedef enum {
    TriggerTypeUnknown,
    TriggerTypeNavigation
} TriggerType;

class Trigger : public Positionable {
public:
    Trigger(Json::Value value);

    string getName() const;
    TriggerType getType() const;

    static TriggerType typeFromString(string str);
protected:
    string m_name;
    TriggerType m_type;
};

