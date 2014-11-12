#ifndef INTERACTABLE_H
#define INTERACTABLE_H

#include <memory>
#include <string>

#include "InteractObserver.h"
#include "StateObserver.h"

#include "json/json.h"
#include "Positionable.h"
#include "Position.h"
#include "Util.h"

using namespace std;

enum class InteractableType { HERO, ENEMY, NPC };

/* Forward delcarations */
class Hero;
class Enemy;

class Interactable : public Positionable {
public:
    virtual ~Interactable();

    InteractableType getType() const;

    bool changeState(State newState);
    bool interact(Interactable& target);

    void registerInteractObserver(weak_ptr<InteractObserver> obs);
    void registerStateObserver(weak_ptr<StateObserver> obs);    
    
    static InteractableType getInteractableType(string type);
    static shared_ptr<Interactable> createFromJson(InteractableType type, Json::Value val);

protected:
    
    /*
     * Protected constructor to prevent public instantiation
     */
    Interactable(Json::Value value);

    /*
     * Prohibit default construction
     */
    Interactable() = delete;

    /*
     * Target specified implementations
     */
    virtual bool interact_impl(Hero& hero) = 0;
    virtual bool interact_impl(Enemy& enemy) = 0;

    weak_ptr<StateObserver> m_stateObserver;
    weak_ptr<InteractObserver> m_interactObserver;

    void setInteractableType(InteractableType);
private:
    State m_state;
    InteractableType m_type;
};



#endif // INTERACTABLE_H
