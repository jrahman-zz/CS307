#ifndef TRIGGER_H
#define TRIGGER_H

#include <string>

#include "json/json.h"
#include "Interactable.h"

using namespace std;

enum class TriggerType { DIALOGUE, LEVELEXIT, UNKNOWN };

class Trigger : public Positionable {
public:
    Trigger(Json::Value value);

    string getName() const;
    virtual TriggerType getType() const;
    //virtual bool stopMovement() const = 0;

    static TriggerType typeFromString(string str);
    static shared_ptr<Trigger> createFromJson(TriggerType type, Json::Value val);
protected:
    
    /*
     * Ban constructor to prevent public instantiation
     */
    Trigger() = delete;

    string m_name;
    TriggerType m_type;
};

#endif
