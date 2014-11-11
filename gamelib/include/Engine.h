#ifndef ENGINE_H
#define ENGINE_H

#include <memory>
#include <string>
#include <vector>

#include "ActionLog.h"
#include "HeroFascade.h"
#include "WorldFascade.h"

#include "GameState.h"
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

    shared_ptr<WorldFascade> getWorld() const;
    shared_ptr<HeroFascade> getHero() const;
    
    unsigned int getTimestep() const;

    /*
     * Get level output
     */
    string getResult() const;

    /*
     * Call prior to beginning a submission run
     */
    bool startSubmission();
    
    /*
     * Call following the end of a submission
     */
    void endSubmission();

    /*
     * Completely reset all game state
     */
    void resetEngine();
protected:

    void init(string levelJson);
    
    Json::Value getLog() const;
private:

    shared_ptr<TileLayer> mergeLayers(vector<shared_ptr<TileLayer>> layers);

    /*
     * Object to manage level state
     */
    shared_ptr<LevelManager> m_levelManager;

    /*
     * Single hero instance for user control
     */
    shared_ptr<Hero> m_hero;

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

    unsigned int m_levelID;
    unsigned int m_userID;
    unsigned int m_classID;

    shared_ptr<GameState> m_gameState;
    shared_ptr<ActionLog> m_actionLog;
    shared_ptr<TimeKeeper> m_timekeeper;
};

#endif // ENGINE_H
