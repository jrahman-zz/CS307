#ifndef TRIGGER_H
#define TRIGGER_H

#include <string>

#include "json/json.h"
#include "Interactable.h"
#include "Positionable.h"

using namespace std;

enum class TriggerType { DIALOGUE, LEVELEXIT, UNKNOWN };

/*
 * TODO Inject GameState
 */

class Trigger : public Positionable {
public:

    virtual ~Trigger();
    /*
     * Activate trigger
     */
    bool trigger(Interactable& target);

    string getName() const;
    TriggerType getType() const;
    
    bool isTriggered() const;

    bool isRepeatable() const;

    bool isTriggerable() const;

    static TriggerType typeFromString(string str);
    
    static shared_ptr<Trigger> createFromJson(TriggerType type, Json::Value val);
protected:

    Trigger(Json::Value value);
    /*
     * Ban constructor to prevent public instantiation
     */
    Trigger() = delete;

    virtual bool triggerImpl(Interactable& target) = 0;

private:

    string m_name;

    TriggerType m_type;

    /*
     * Can this trigger be repeated, default false
     */
    bool m_repeatable;

    /*
     * Will this trigger halt movement
     */
    bool m_stopMovement;

    /*
     * Actor ID to target
     */
    bool m_triggerTarget;

    /*
     * Has this trigger been activated, if repeatable, reset once the hero moves off
     */
    bool m_triggered;
};

#endif
