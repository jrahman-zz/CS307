#ifndef INTERACTABLE_H
#define INTERACTABLE_H

#include <memory>
#include <string>

#include "ActorObserver.h"
#include "json/json.h"
#include "Position.h"
#include "Util.h"

using namespace std;

enum class InteractableType { HERO };

/* Forward delcarations */
class Hero;
class Enemy;

class Interactable : public Positionable {
public:
    virtual ~Interactable();

    unsigned int getID();
    InteractableType getType();

    bool changeState(State newState);
    bool interact(Interactable& target);
    Position getPosition();

    
    /*
     * TODO rip these out of this class, don't think they belong here
     */
    static InteractableType getInteractableType(string type);
    static shared_ptr<Interactable> createFromJson(InteractableType type, Json::Value val);

protected:
    
    /*
     * Protected constructor to prevent public instantiation
     */
    Interactable(Json::Value value);

    /*
     * Double dispatch implementations
     */
    virtual bool interact_impl(Interactable& target) = 0;
    
    /*
     * Target specified implementations
     */
    virtual void interact_impl(Hero& hero) = 0;
    virtual bool interact_impl(Enemy& enemy) = 0;

    unsigned int m_ID;

    InteractableType m_type;
private:
    State m_state;
};


#endif // INTERACTABLE_H
