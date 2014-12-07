#include <algorithm>
#include <climits>
#include <fstream>
#include <iostream>
#include <string>

#include "TilemapParser.h"

using namespace std;

// Exclusive.
void assertRange(int num, int low, int high, const string &errMessage) {
    if (num <= low || num >= high) {
        throw range_error(errMessage);
    }
}

// Inclusive.
void assertRangeInclusive(int num, int low, int high, const string &errMessage) {
    if (num < low || num > high) {
        throw range_error(errMessage);
    }
}

void assertGreater(int num, int low, const string &errMessage) {
    assertRange(num, low, INT_MAX, errMessage);
}

void assertGreaterInclusive(int num, int low, const string &errMessage) {
    assertRangeInclusive(num, low, INT_MAX, errMessage);
}

void assertEqual(int num1, int num2, const string &errMessage) {
    if (num1 != num2) {
        throw runtime_error(errMessage);
    }
}

void assertEqual(const string &str1, const string &str2, const string &errMessage) {
    if (str1 != str2) {
        throw runtime_error(errMessage);
    }
}

void assertTrue(bool condition, const string &errMessage) {
    if (!condition) {
        throw runtime_error(errMessage);
    }
}

void assertFalse(bool condition, const string &errMessage) {
    assertTrue(!condition, errMessage);
}

void validateLevelTileLayer(Json::Value tileLayer, int index, int tilesetMaxValue) {
    int width = tileLayer["width"].asInt();
    int height = tileLayer["height"].asInt();
    Json::Value data = tileLayer["data"];
    assertEqual(data.size(), width * height,
        string("Malformed data for tile layer at layer index ")
        + to_string(index));
    for (unsigned int i = 0; i < data.size(); i++) {
        assertRangeInclusive(data[i].asInt(), 0, tilesetMaxValue,
            string("Tilelayer data value should be 0 or between valid tileset gids at layer index "
            + to_string(index)
            + string("\nGid range: (1, " + to_string(tilesetMaxValue) + string(")"))));
    }

    assertGreater(tileLayer["name"].asString().length(), 0,
        string("Tilelayer name must be non-empty at layer index " + to_string(index)));
}

void validateLevelObjectLayer(Json::Value objLayer, int index) {
    string name = objLayer["name"].asString();
    Json::Value objs = objLayer["objects"];
    if (name == "TriggerLayer") {
        for (unsigned int i = 0; i < objs.size(); i++) {
            Json::Value obj = objs[i];
            string type = obj["type"].asString();
            Json::Value props = obj["properties"];

            assertTrue(props.isMember("repeatable"), string("Trigger without repeatable prop"));
            assertTrue(props.isMember("stopMove"), string("Trigger without stopMove prop"));
            assertTrue(props.isMember("triggerTarget"),
                string("Trigger without triggerTarget prop"));
            if (type == "dialogue") {
                assertTrue(props.isMember("actor"), 
                    string("Dialogue trigger without actor prop"));
                assertTrue(props.isMember("dialogue"),
                    string("Dialogue trigger without dialogue prop"));
            } else if (type == "levelexit") {
                assertTrue(props.isMember("nextLevel"),
                    string("Levelexit trigger without nextLevel prop"));
            } else if (type == "objective") {
                assertTrue(props.isMember("objectiveId"),
                    string("Objective trigger objectiveId prop"));
                assertFalse(std::stoi(props["repeatable"].asString()),
                    string("Objective trigger should not be repeatable"));
            } else {
                throw runtime_error(string("Invalid trigger type: ") + type);
            }
        }
    } else if (name == "ActorLayer") {
        vector<int> actorIds;
        for (unsigned int i = 0; i < objs.size(); i++) {
            Json::Value obj = objs[i];
            string type = obj["type"].asString();
            Json::Value props = obj["properties"];

            int rotation = stoi(props["rotation"].asString());
            assertTrue(rotation == 0
                       || rotation == 90
                       || rotation == 180
                       || rotation == 270, string("Rotation must be 0, 90, 180, or 270."));

            int actorId = stoi(props["id"].asString());
            if (find(actorIds.begin(), actorIds.end(), actorId) != actorIds.end()) {
                throw runtime_error(string("Actor id collision: ")
                    + to_string(actorId));
            }
            actorIds.push_back(actorId);
            if (type == "npc") {
                assertTrue(props.isMember("npc_id"), string("NPC actor without npc_id"));
            } else if (type == "enemy") {
                assertTrue(props.isMember("enemy_id"), string("Enemy actor without enemy_id"));
            } else if (type == "hero") {

            } else {
                throw runtime_error(string("Invalid actor object type: ") + type);
            }
        }
    } else {
        throw runtime_error(string("Invalid object layer name: ") + name);
    }

    assertEqual(objLayer["draworder"].asString(), "topdown",
        string("Expected topdown draworder on object layer at index " + to_string(index)));
}

void validateLevelJson(Json::Value root) {
    // Validate basic properties.
    int levelWidth = root["width"].asInt();
    int levelHeight = root["height"].asInt();
    assertGreater(levelWidth, 0, string("Level width must be > 0"));
    assertGreater(levelHeight, 0, string("Level height must be > 0"));

    int tileWidth = root["tilewidth"].asInt();
    int tileHeight = root["tileheight"].asInt();
    assertGreater(tileWidth, 0, string("Tile width must be > 0"));
    assertGreater(tileHeight, 0, string("Tile height must be > 0"));
    assertEqual(tileWidth, tileHeight, string("Tile width must equal tile height"));

    assertEqual(root["orientation"].asString(), string("orthogonal"),
        string("Only orthogonal maps supported!"));

    // Validate tilesets.
    Json::Value tilesets = root["tilesets"];
    assertEqual(tilesets.size(), 1, string("Only one tileset supported at this time"));
    Json::Value tileset = tilesets[0];
    assertEqual(tileset["firstgid"].asInt(), 1, string("Expected firstgid for tileset to be 1"));
    assertEqual(tileset["spacing"].asInt(), 0, string("Only tileset with 0 spacing supported at this time"));
    int tilesetMargin = tileset["margin"].asInt();
    int tilesetImageWidth = tileset["imagewidth"].asInt() - 2 * tilesetMargin;
    int tilesetImageHeight = tileset["imageheight"].asInt() - 2 * tilesetMargin;
    int tilesetTileWidth = tileset["tilewidth"].asInt();
    int tilesetTileHeight = tileset["tileheight"].asInt();

    int tilesetRows = tilesetImageHeight / tilesetTileHeight;
    int tilesetCols = tilesetImageWidth / tilesetTileWidth;
    assertGreater(tilesetRows, 0, "Tileset rows must be > 0");
    assertGreater(tilesetCols, 0, "Tileset columns must be > 0");
    int tilesetMaxValue = tilesetRows * tilesetCols;

    // Validate layers.
    vector<string> tilelayerNames;
    vector<string> objectlayerNames;
    Json::Value layers = root["layers"];
    assertGreater(layers.size(), 0, "No layers");
    for (unsigned int i = 0; i < layers.size(); i++) {
        Json::Value layer = layers[i];

        string name = layer["name"].asString();
        string type = layer["type"].asString();

        if (type == "tilelayer") {
            assertEqual(layer["width"].asInt(), levelWidth,
                string("Expected layer width equal to level width for layer index ")
                + to_string(i));
            assertEqual(layer["height"].asInt(), levelHeight,
                string("Expected layer height equal to level height"));

            if (find(tilelayerNames.begin(), tilelayerNames.end(), name) != tilelayerNames.end()) {
                throw runtime_error(string("Duplicate tilelayer name: ") + name
                    + string(". Tilelayer names must be unique"));
            }
            tilelayerNames.push_back(name);

            validateLevelTileLayer(layer, i, tilesetMaxValue);
        } else if (type == "objectgroup") {
            if (find(objectlayerNames.begin(), objectlayerNames.end(), name)
                    != objectlayerNames.end()) {
                throw runtime_error(string("Duplicate objectlayer name: ") + name
                    + string(". Objectlayer names must be unique"));
            }
            validateLevelObjectLayer(layer, i);
        } else {
            throw runtime_error(string("Invalid layer type: ") + type);
        }

        assertEqual(layer["x"].asInt(), 0, string("Expected layer x to be 0 at layer index "
            + to_string(i)));
        assertEqual(layer["y"].asInt(), 0, string("Expected layer y to be 0 at layer index "
            + to_string(i)));
        assertTrue(layer["visible"].asBool(), string("Expected layer to be visible at layer index "
            + to_string(i)));
    }
}

int main(int argc, char **argv) {
    Json::Value levelJson;
    string filename;

    if (argc < 2) {
        cerr << argv[0] + string(" <filename>") << endl;
        return 1;
    } else {
        if (!string("-h").compare(argv[1]) || !string("--help").compare(argv[1])) {
            cerr << argv[0] + string(" <filename>") << endl;
            return 1;
        }

        // Read JSON from file.
        filename = string(argv[1]);
        ifstream in(filename);
        if (in) {
            in >> levelJson;
            in.close();
        } else {
            cerr << "Failed to open " << filename << endl;
            return 1;
        }
    }

    // Validate.
    cout << "Validating level '" << filename << "'" << endl;
    try {
        validateLevelJson(levelJson);
    } catch (exception &e) {
        cerr << "----- Invalid level format! -----" << endl;
        cerr << e.what() << endl;
        cerr << "---------------------------------";
        cerr << endl;
        return 1;
    }

    // Parse full map.
    try {
        TilemapParser parser(levelJson);
    } catch (exception &e) {
        cerr << "----- Invalid level format! -----" << endl;
        cerr << "Level passed validation but failed to parse with TilemapParser:" << endl;
        cerr << e.what() << endl;
        cerr << "---------------------------------";
        cerr << endl;
        return 1;
    }

    cout << string("Level '") + filename + string("' passed basic tests.") << endl;
    return 0;
}
