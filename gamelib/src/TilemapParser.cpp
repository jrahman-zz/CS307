#include "TilemapParser.h"

#include <iostream>

TilemapParser::TilemapParser() {
}

bool TilemapParser::parse(std::string& json_str) {
    Json::Value root;
    Json::Reader reader;

    m_tileLayers.clear();
    m_triggers.clear(); 
    m_actors.clear();

    bool success = reader.parse(json_str, root);
    if (!success) {
        throw runtime_error("Failed to parse JSON:\n"
        + reader.getFormattedErrorMessages());
    }

    if (!root.isMember("width")) {
        throw runtime_error("Missing width");
    }
    
    if (!root.isMember("height")) {
        throw runtime_error("Missing height");
    }
    
    if (!root.isMember("tileheight")) {
        throw runtime_error("Missing tileheight");
    }

    if (!root.isMember("tilewidth")) {
        throw runtime_error("Missing tilewidth");
    }

    m_mapWidth = root["width"].asInt();
    m_mapHeight = root["height"].asInt();
    m_tileWidth = root["tilewidth"].asInt();
    m_tileHeight = root["tileheight"].asInt();

    if (m_tileHeight != m_tileWidth) {
        throw runtime_error("Non-square tile prohibited");
    }

    // These will be stored by the game state
    if (!root.isMember("layers")) {
        throw runtime_error("No layers");
    }

    Json::Value layers_elem = root["layers"];
    for (unsigned int i = 0; i < layers_elem.size(); i++) {
        Json::Value layer_elem = layers_elem[i];
    
        if (!layer_elem.isMember("type")) {
            throw runtime_error("No type for layer");
        }

        if (!layer_elem.isMember("width")) {
            throw runtime_error("No width for layer");
        }

        if (!layer_elem.isMember("height")) {
            throw runtime_error("No height for layer");
        }

        string type = layer_elem["type"].asString();
        if (type == "tilelayer") {
            auto layer = parseLayer(layer_elem);
            m_tileLayers.push_back(layer);
        } else if (type == "objectgroup") {
            if (!layer_elem.isMember("name")) {
                throw runtime_error("Unnamed object group layer");
            }
            string group_name = layer_elem["name"].asString();
            if (group_name == "TriggerLayer") {
                m_triggers = parseTriggers(layer_elem);
            } else if (group_name == "ActorLayer") {
                m_actors = parseActors(layer_elem);
            }
        }
    }

    return true;
}

vector<shared_ptr<TileLayer>> TilemapParser::getTileLayers() {
    return m_tileLayers;
}

vector<shared_ptr<Trigger>> TilemapParser::getTriggers() {
    return m_triggers;
}

vector<shared_ptr<Interactable>> TilemapParser::getActors() {
    return m_actors;
}

shared_ptr<TileLayer> TilemapParser::parseLayer(Json::Value root) {
    if (!root.isMember("data")) {
        throw runtime_error("No data in tilelayer");
    }

    int layer_width = root["width"].asInt();
    int layer_height = root["height"].asInt();

    if (layer_width != m_mapWidth) {
        throw runtime_error("Layer width mismatch");
    }

    if (layer_height != m_mapHeight) {
        throw runtime_error("layer height mismatch");
    }
    
    Json::Value data = root["data"];
    if (data.size() != m_mapHeight * m_mapWidth) {
        throw runtime_error("Data array wrong size");
    }

    shared_ptr<TileLayer> tile_layer(new TileLayer(m_mapWidth, m_mapHeight));
    int row = 0, col = 0;
      
    for (unsigned int j = 0; j < data.size(); j++) {
        int tile_id = data[j].asInt();
        (*tile_layer)[row][col] = Tile(tile_id);
        col = (col + 1) % layer_width;
        if (col == 0) {
            row++;
        }
    }

    return shared_ptr<TileLayer>(tile_layer);
}


vector<shared_ptr<Trigger>> TilemapParser::parseTriggers(Json::Value root) {
    vector<shared_ptr<Trigger>> triggers;
    Json::Value objects = root["objects"];

    int layer_width = root["width"].asInt();
    int layer_height = root["height"].asInt();

    if (layer_width != m_mapWidth) {
        throw runtime_error("Layer width mismatch");
    }

    if (layer_height != m_mapHeight) {
        throw runtime_error("Layer height mismatch");
    }

    for (unsigned int j = 0; j < objects.size(); j++) {
        Json::Value object = objects[j]; 

        int x = object["x"].asInt() / m_tileWidth;
        int y = object["y"].asInt() / m_tileHeight;

        if (x < 0 || y < 0 || x >= m_mapWidth || y >= m_mapHeight) {
            throw runtime_error("Illegal trigger position");
        }

        shared_ptr<Trigger> trigger(new Trigger(object));
        triggers.push_back(trigger);
    }
    return triggers;
}

vector<shared_ptr<Interactable>> TilemapParser::parseActors(Json::Value root) {
    vector<shared_ptr<Interactable>> actors;

    auto objects = root["objects"];

    int layer_width = root["width"].asInt();
    int layer_height = root["height"].asInt();

    if (layer_width != m_mapWidth) {
        throw runtime_error("Layer width mismatch");
    }

    if (layer_height != m_mapHeight) {
        throw runtime_error("Layer height mismatch");
    }

    for (unsigned int j = 0; j < objects.size(); j++) {
        Json::Value object  = objects[j];
        string object_name = object["name"].asString();
        string object_type = object["type"].asString();

        object["x"] = object["x"].asInt() / m_tileWidth;
        object["y"] = object["y"].asInt() / m_tileHeight;
    
        auto type = Interactable::getInteractableType(object["type"].asString());
        auto actor = Interactable::createFromJson(type, object); 
        actors.push_back(actor);
    }
    return actors;
}

unsigned int TilemapParser::getMapWidth() {
    return m_mapWidth;
}

unsigned int TilemapParser::getMapHeight() {
    return m_mapHeight;
}

unsigned int TilemapParser::getTileWidth() {
    return m_tileWidth;
}

unsigned int TilemapParser::getTileHeight() {
    return m_tileHeight;
}

void TilemapParser::debug() {
    cout << "Read " << m_tileLayers.size() << " tile layers: " << endl;
    int i = 0;
    for (auto it = m_tileLayers.begin(); it != m_tileLayers.end(); it++) {
        auto layer = *it;
        cout << "Layer " << i++ << ": " << endl;
        for (unsigned int j = 0; j < layer->getHeight(); j++) {
            for (unsigned int k = 0; k < layer->getWidth(); k++) {
                auto tile = (*layer)[j][k];
                printf("%3d[%d] ", tile.getID(), tile.getType());
            }
            printf("\n");
        }
        printf("--\n");
    }

    printf("Read %ld triggers: \n", m_triggers.size());
    i = 0;
    for (auto it = m_triggers.begin(); it != m_triggers.end(); it++) {
        auto trigger = *it;
        auto name = trigger->getName();
        auto type = trigger->getType();
        cout << "Trigger ";
        cout << i++ << ": {name: " << name << ", type: " << type << "}" << endl;
    }
}
