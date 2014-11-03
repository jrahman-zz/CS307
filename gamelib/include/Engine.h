#ifndef ENGINE_H
#define ENGINE_H

#include <memory>
#include <string>
#include <map>
#include <tuple>

#include "BaseMessage.h"
#include "BaseManager.h"

#include "ActorObserver.h"

#include "ActionLog.h"
#include "HeroFascade.h"
#include "WorldFascade.h"

#include "Interactable.h"
#include "TilemapParser.h"
#include "TileLayer.h"
#include "Tile.h"
#include "Trigger.h"
#include "Position.h"

using namespace std;

/*
 * Core class for game engine
 */
class Engine : public BaseManager, ActorObserver {
public:
    Engine(string levelJson); // TODO, add scripting, etc
    ~Engine();

    void Init(string levelJson);

    shared_ptr<WorldFascade> getWorld() const;
    shared_ptr<HeroFascade> getHero() const;
    
    virtual bool sendMessage(BaseMessage* msg);
    bool executeCommand(unsigned int actorID, shared_ptr<Command> cmd);

    /*
     * Hooks for observer pattern
     */
    virtual bool onPreStateChange(Interactable& obj, State current, State next)
    virtual void onPostStateChange(Interactable& obj, State current);

    virtual bool onPreMove(Moveable& moving, Position current, Position next);
    virtual void onPostMove(Moveable& moving, Position current);

    virtual bool onPreInteract(Interactable& src, Interactable& target);
    virtual void onPostInteract(Interactable& src, Interactable& target);

    unsigned int getTimestep() const;

    shared_ptr<ActionLog> getActionLog() const;
    void resetEngine();
protected:

    unsigned int getHeroID() const;

private:
    shared_ptr<ActionLog> m_actions;

    unsigned int m_heroID;

    /*
     * Flag controlling if engine should continue to accept
     * commands controlling the character
     */
    bool m_isActive;

    /*
     * Store a copy of the Json defining the level, in case of reset
     */
    string m_levelJson;

    map<unsigned int, tuple<Position, shared_ptr<Interactable>>> m_actorID;
    map<Position, shared_ptr<Interactable>> m_actors;
    shared_ptr<TileLayer> m_tileMap;
    map<Position, shared_ptr<Trigger>> m_triggers;
    unsigned int m_height;
    unsigned int m_width;

    /*
     * Log to record actions and events for recording
     */
    shared_ptr<ActionLog> m_log;

    unsigned int m_timestep;
};

#endif // ENGINE_H
