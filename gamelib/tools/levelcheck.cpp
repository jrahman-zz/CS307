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

void validateLevelTileLayer(Json::Value tileLayer, int index, int tilesetMaxValue) {
    assertEqual(tileLayer["x"].asInt(), 0, string("Expected layer x to be 0 at layer index "
        + to_string(index)));
    assertEqual(tileLayer["y"].asInt(), 0, string("Expected layer y to be 0 at layer index "
        + to_string(index)));

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

    assertTrue(tileLayer["visible"].asBool(), string("Tilelayer must be visible at layer index "
        + to_string(index)));
    assertGreater(tileLayer["name"].asString().length(), 0,
        string("Tilelayer name must be non-empty at layer index " + to_string(index)));
}

void validateLevelObjectLayer(Json::Value objLayer, int index) {
    string name = objLayer["name"].asString();
    if (name == "TriggerLayer") {

    } else if (name == "ActorLayer") {

    } else {
        throw runtime_error(string("Invalid object layer name: ") + name);
    }
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
    Json::Value layers = root["layers"];
    assertGreater(layers.size(), 0, "No layers");
    for (unsigned int i = 0; i < layers.size(); i++) {
        Json::Value layer = layers[i];
        string type = layer["type"].asString();

        if (type == "tilelayer") {
            assertEqual(layer["width"].asInt(), levelWidth,
                string("Expected layer width equal to level width for layer index ")
                + to_string(i));
            assertEqual(layer["height"].asInt(), levelHeight,
                string("Expected layer height equal to level height"));

            string name = layer["name"].asString();
            if (find(tilelayerNames.begin(), tilelayerNames.end(), name) != tilelayerNames.end()) {
                throw runtime_error(string("Duplicate tilelayer name: ") + name
                    + string(". Tilelayer names must be unique"));
            }
            tilelayerNames.push_back(layer["name"].asString());

            validateLevelTileLayer(layer, i, tilesetMaxValue);
        } else if (type == "objectgroup") {
            validateLevelObjectLayer(layer, i);
        } else {
            throw runtime_error(string("Invalid layer type: ") + type);
        }
    }
}

int main(int argc, char **argv) {
    Json::Value levelJson;
    string filename(argv[1]);

    if (argc < 2) {
        cerr << argv[0] + string(" <filename>") << endl;
        return 1;
    } else {
        if (!string("-h").compare(argv[1]) || !string("--help").compare(argv[1])) {
            cerr << argv[0] + string(" <filename>") << endl;
            return 1;
        }

        // Read JSON from file.
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
    cout << "Validating..." << endl;
    try {
        validateLevelJson(levelJson);
    } catch (exception &e) {
        cerr << "----- Invalid level format! -----" << endl;
        cerr << e.what() << endl;
        cerr << "-----------------------------";
        cerr << endl;
        return 1;
    }

    // Parse full map.
    /*try {
        TilemapParser parser(levelJson);
    } catch (runtime_error e) {
        cerr << "Invalid level:" << endl
            << e.what() << endl;
        return 1;
    } catch (exception e) {
        cerr << "Exception thrown" << e.what() << endl;
        return 1;
    }*/

    cout << string("Level '") + filename + string("' passed basic tests.") << endl;
    return 0;
}
