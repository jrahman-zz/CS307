#include <iostream>
#include <string>

#include "util.h"
#include "json/json.h"
#include "TilemapParser.h"
#include "TileLayer.h"

#include "test_data_a.h"

using namespace std;

START_TEST("tilemap");
	try {

        Json::Value root;
        Json::Reader reader;
        if (!reader.parse(testDataA, root)) {
            cout << "Failed to parse" << endl;
            FAIL_TEST("tilemap");
        }

        TilemapParser parser(root["level"]);

        auto tilemaps = parser.getTileLayers();

        if (tilemaps.size() != 2) {
            cout << "Incorrect layer count: " << tilemaps.size() << endl;
            FAIL_TEST("tilemap");
        }

        auto layerIt = tilemaps.begin();
        auto firstLayer = *layerIt++;
        auto secondLayer = *layerIt++;

        auto mergedLayer = firstLayer->merge(secondLayer);
        auto id = (*mergedLayer)[1][0].getID();
        if (id != 21) {
            cout << "Incorrect tile ID: " << id << " should be 21" << endl;
            FAIL_TEST("tilemap");
        }
    } catch (runtime_error e) {
        cout << "Exception: " << e.what() << endl;
        FAIL_TEST("tilemap");
    } catch (exception e) {
        cout << "Unknown exception" << endl;
        FAIL_TEST("tilemap");
    }
END_TEST("tilemap");
