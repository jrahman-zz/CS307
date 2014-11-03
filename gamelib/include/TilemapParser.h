#pragma once

#include <memory>
#include <vector>
#include <tuple>

#include "Interactable.h"
#include "TileLayer.h"
#include "Trigger.h"
#include "Position.h"

using namespace std;

/**
 * Parses JSON files exported from Tiled Map Editor.
 */
class TilemapParser {
public:
    TilemapParser();

    bool parse(string& json_str);

    vector<shared_ptr<TileLayer>> getTileLayers();
    vector<tuple<Position, shared_ptr<Trigger>>> getTriggers();
    vector<tuple<Position, shared_ptr<Interactable>>> getActors();

    void debug();
    
protected:
    
    shared_ptr<TileLayer> parseLayer(Json::Value root);
    vector<tuple<Position, shared_ptr<Trigger>>> parseTriggers(Json::Value root);
    vector<tuple<Position, shared_ptr<Interactable>>> parseActors(Json::Value root);

private:
    vector<shared_ptr<TileLayer>> m_tileLayers;
    vector<shared_ptr<Trigger>> m_triggers;
    vector<shared_ptr<Interactable>> m_actors;

    unsigned int m_mapWidth;
    unsigned int m_mapHeight;
    unsigned int m_tileHeight;
    unsigned int m_tileWidth;
};
