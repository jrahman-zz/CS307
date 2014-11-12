#include "TilemapParser.h"

#include <iostream>

TilemapParser::TilemapParser(string jsonStr) {
    parse(jsonStr);
}

void TilemapParser::parse(string jsonStr) {
    Json::Value root;
    Json::Reader reader;

    if (!reader.parse(jsonStr, root)) {
        throw runtime_error("Failed to parse JSON:\n"
        + reader.getFormattedErrorMessages());
    }

    checkInput(root); 
 
    m_userID = root["userID"].asInt();
    m_levelID = root["levelID"].asInt();
    m_classID = root["classID"].asInt();

    auto level = root["level"];    

    checkLevel(level);

    m_mapWidth = level["width"].asInt();
    m_mapHeight = level["height"].asInt();
    m_tileWidth = level["tilewidth"].asInt();
    m_tileHeight = level["tileheight"].asInt();

    if (m_tileHeight != m_tileWidth) {
        throw invalid_argument("Non-square tile prohibited");
    }

    Json::Value layers_elem = level["layers"];
    for (unsigned int i = 0; i < layers_elem.size(); i++) {
        Json::Value layer_elem = layers_elem[i];
    
        if (!layer_elem.isMember("type")) {
            throw invalid_argument("No type for layer");
        }

        if (!layer_elem.isMember("width")) {
            throw invalid_argument("No width for layer");
        }

        if (!layer_elem.isMember("height")) {
            throw invalid_argument("No height for layer");
        }

        string type = layer_elem["type"].asString();
        if (type == "tilelayer") {
            auto layer = parseLayer(layer_elem);
            m_tileLayers.push_back(layer);
        } else if (type == "objectgroup") {
            if (!layer_elem.isMember("name")) {
                throw invalid_argument("Unnamed object group layer");
            }
            string group_name = layer_elem["name"].asString();
            if (group_name == "TriggerLayer") {
                m_triggers = parseTriggers(layer_elem);
            } else if (group_name == "ActorLayer") {
                m_actors = parseActors(layer_elem);
            }
        }
    }
}

void TilemapParser::checkInput(Json::Value root) {
    if (!root.isMember("levelID")) {
        throw invalid_argument("Missing levelID");
    }

    if (!root.isMember("classID")) {
        throw invalid_argument("Missing classID");
    }

    if (!root.isMember("userID")) {
        throw invalid_argument("Missing userID");
    }

    if (!root.isMember("level")) {
        throw invalid_argument("Missing level");
    }
}

void TilemapParser::checkLevel(Json::Value root) {
    
    if (!root.isMember("width")) {
        throw invalid_argument("Missing width");
    }
    
    if (!root.isMember("height")) {
        throw invalid_argument("Missing height");
    }
    
    if (!root.isMember("tileheight")) {
        throw invalid_argument("Missing tileheight");
    }

    if (!root.isMember("tilewidth")) {
        throw invalid_argument("Missing tilewidth");
    }

    if (!root.isMember("layers")) {
        throw invalid_argument("Missing layers");
    }
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

unsigned int TilemapParser::getUserID() const {
    return m_userID;
}

unsigned int TilemapParser::getLevelID() const {
    return m_levelID;
}

unsigned int TilemapParser::getNextLevelID() const {
    return m_nextLevelID;
}

unsigned int TilemapParser::getClassID() const {
    return m_classID;
}

shared_ptr<TileLayer> TilemapParser::parseLayer(Json::Value root) {
    if (!root.isMember("data")) {
        throw invalid_argument("No data in tilelayer");
    }

    int layer_width = root["width"].asInt();
    int layer_height = root["height"].asInt();

    if (layer_width != m_mapWidth) {
        throw invalid_argument("Layer width mismatch");
    }

    if (layer_height != m_mapHeight) {
        throw invalid_argument("layer height mismatch");
    }
    
    Json::Value data = root["data"];
    if (data.size() != m_mapHeight * m_mapWidth) {
        throw invalid_argument("Data array wrong size");
    }

    shared_ptr<TileLayer> tile_layer(new TileLayer(root));

    return shared_ptr<TileLayer>(tile_layer);
}


vector<shared_ptr<Trigger>> TilemapParser::parseTriggers(Json::Value root) {
    vector<shared_ptr<Trigger>> triggers;
    Json::Value objects = root["objects"];

    int layer_width = root["width"].asInt();
    int layer_height = root["height"].asInt();

    if (layer_width != m_mapWidth) {
        throw invalid_argument("Layer width mismatch");
    }

    if (layer_height != m_mapHeight) {
        throw invalid_argument("Layer height mismatch");
    }

    for (unsigned int j = 0; j < objects.size(); j++) {
        Json::Value object = objects[j]; 

        // We must normalize to tile coordinates before handing off to the ctor
        object["x"] = object["x"].asInt() / m_tileWidth;
        object["y"] = object["y"].asInt() / m_tileHeight;

        auto x = object["x"].asInt();
        auto y = object["y"].asInt();

        if (x < 0 || y < 0 || x >= m_mapWidth || y >= m_mapHeight) {
            throw invalid_argument("Illegal trigger position");
        }

        auto type = Trigger::typeFromString(object["type"].asString());
        auto trigger = Trigger::createFromJson(type, object);
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
        cout << "Trigger ";
        cout << i++ << ": {name: " << name << " }" << endl;
    }
}
