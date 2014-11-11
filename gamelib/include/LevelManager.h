#ifndef LEVEL_MANAGER_H
#define LEVEL_MANAGER_H

#include <unordered_map>
#include <memory>

#include "StateObserver.h"
#include "MoveObserver.h"
#include "InteractObserver.h"

#include "Interactable.h"
#include "Moveable.h"
#include "TileLayer.h"
#include "Trigger.h"
#include "TimeKeeper.h"

using namespace std;

class LevelManager : public StateObserver, public MoveObserver, public InteractObserver {
public:

    explicit LevelManager(TileLayer tilemap);
    explicit LevelManager(TileLayer&& tilemap);
    virtual ~LevelManager();

    bool addActor(shared_ptr<Interactable>);
    bool removeActor(unsigned int actorID);
    bool removeActor(Position position);

    bool addTrigger(shared_ptr<Trigger> trigger);
    bool removeTrigger(unsigned int triggerID);

    /*
     * Hooks for observer pattern
     */
    virtual bool onPreStateChange(Interactable& obj, State next);
    virtual void onPostStateChange(Interactable& obj, State old);

    virtual bool onPreMove(Moveable& obj, Position next);
    virtual void onPostMove(Moveable& obj, Position old);

    virtual bool onPreInteract(Interactable& src, Interactable& target);
    virtual void onPostInteract(Interactable& src, Interactable& target);

protected:
    shared_ptr<TileLayer> m_tilemap;

    /*
     * Actor resources
     */    
    unordered_map<Position, shared_ptr<Interactable>> m_actors;
    unordered_map<unsigned int, shared_ptr<Interactable>> m_actorsID;

    /*
     * Trigger resources
     */
    unordered_map<Position, shared_ptr<Trigger>> m_triggers;
    unordered_map<unsigned int, shared_ptr<Trigger>> m_triggersID;
    vector<shared_ptr<Trigger>> m_currentTriggers;
private:

};

#endif
