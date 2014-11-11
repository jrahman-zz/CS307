#pragma once

#include <memory>
#include <vector>

#include "Positionable.h"
#include "Interactable.h"
#include "TileLayer.h"
#include "Trigger.h"

using namespace std;

/**
 * Parses JSON files exported from Tiled Map Editor.
 */
class TilemapParser {
public:
    explicit TilemapParser(string jsonStr);

    vector<shared_ptr<TileLayer>> getTileLayers();
    vector<shared_ptr<Trigger>> getTriggers();
    vector<shared_ptr<Interactable>> getActors();

    unsigned int getMapWidth();
    unsigned int getMapHeight();
    unsigned int getTileWidth();
    unsigned int getTileHeight();

    unsigned int getUserID() const;
    unsigned int getLevelID() const;
    unsigned int getNextLevelID() const;
    unsigned int getClassID() const;

    void debug();
    
protected:
    
    /*
     * Ban the constructors we don't want
     */
    TilemapParser() = delete;
    TilemapParser(const TilemapParser& rhs) = delete;

    void parse(string jsonStr);
    void checkInput(Json::Value root);
    void checkLevel(Json::Value root);

    shared_ptr<TileLayer> parseLayer(Json::Value root);
    vector<shared_ptr<Trigger>> parseTriggers(Json::Value root);
    vector<shared_ptr<Interactable>> parseActors(Json::Value root);

private:
    vector<shared_ptr<TileLayer>> m_tileLayers;
    vector<shared_ptr<Trigger>> m_triggers;
    vector<shared_ptr<Interactable>> m_actors;

    unsigned int m_mapWidth;
    unsigned int m_mapHeight;
    unsigned int m_tileHeight;
    unsigned int m_tileWidth;

    unsigned int m_userID;
    unsigned int m_levelID;
    unsigned int m_nextLevelID;
    unsigned int m_classID;
};
