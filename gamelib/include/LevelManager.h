#ifndef LEVEL_MANAGER_H
#define LEVEL_MANAGER_H

#include <unordered_map>
#include <memory>
#include <string>

#include "StateObserver.h"
#include "MoveObserver.h"
#include "InteractObserver.h"

#include "GameState.h"

#include "Interactable.h"
#include "Moveable.h"
#include "TileLayer.h"
#include "Trigger.h"
#include "TimeKeeper.h"

using namespace std;

class LevelManager : public StateObserver, public MoveObserver, public InteractObserver {
public:

    explicit LevelManager(shared_ptr<TileLayer> tile, shared_ptr<GameState> state);
    virtual ~LevelManager();

    bool addActor(shared_ptr<Interactable>);
    bool removeActor(unsigned int actorID);
    bool removeActor(Position position);

    bool addTrigger(shared_ptr<Trigger> trigger);
    bool removeTrigger(string triggerName);

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
    
    /*
     * Remove unwanted default constructors
     */
    LevelManager() = delete;
    LevelManager(const LevelManager& rhs) = delete;

    /*
     * Run triggers
     */
    void runTriggers(shared_ptr<Interactable> actor, Position old);

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
    unordered_map<string, shared_ptr<Trigger>> m_triggersName;

    shared_ptr<GameState> m_gameState;
private:

};

#endif
