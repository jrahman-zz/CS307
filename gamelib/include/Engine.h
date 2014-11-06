#ifndef ENGINE_H
#define ENGINE_H

#include <memory>
#include <string>
#include <vector>

#include "ActionLog.h"
#include "HeroFascade.h"
#include "WorldFascade.h"

#include "LevelManager.h"

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
class Engine {
public:
    Engine(string levelJson);
    ~Engine();

    void resetLevel();

    shared_ptr<WorldFascade> getWorld() const;
    shared_ptr<HeroFascade> getHero() const;
    
    unsigned int getTimestep() const;

    shared_ptr<ActionLog> getActionLog() const;
    string getLog() const;

    void resetEngine();
protected:

    void init(string levelJson);

    unsigned int getHeroID() const;

private:
    shared_ptr<ActionLog> m_actions;

    /*
     * Object to manage level state
     */
    shared_ptr<LevelManager> m_levelManager;

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

    /*
     * Store actors index by ID
     */
    vector<shared_ptr<Interactable>> m_actors;
    
    /*
     * Record tilemap
     */
    shared_ptr<TileLayer> m_tileMap;

    /*
     * Position indexed triggers
     */
    vector<shared_ptr<Trigger>> m_triggers;

    unsigned int m_height;
    unsigned int m_width;

    shared_ptr<ActionLog> m_actionLog;

    unsigned int m_currentTimestep;
};

#endif // ENGINE_H
