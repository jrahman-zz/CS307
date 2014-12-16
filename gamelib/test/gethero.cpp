#include <iostream>
#include <string>

#include "util.h"
#include "json/json.h"
#include "TilemapParser.h"
#include "Engine.h"
#include "Hero.h"

using namespace std;

#include "test_data_a.h"

START_TEST("gethero");
    
    Json::Value root;
    Json::Reader reader;
    if (!reader.parse(testDataA, root)) {
        cout << "Failed to parse string" << endl;
        FAIL_TEST("gethero");
    }

    TilemapParser parser(root["level"]);
    auto actors = parser.getActors();

    if (actors.size() != 3) {
        cout << "Incorrect actor count: " << actors.size() << endl;
        FAIL_TEST("gethero");
    }

    Engine engine(testDataA);
    auto hero = engine.getHero();
    if (hero == nullptr) {
        cout << "Failed to return hero" << endl;
        FAIL_TEST("gethero");
    }


    if (!hero->moveDown()) {
        cout << "Failed to move" << endl;
        FAIL_TEST("gethero");
    }
END_TEST("gethero");
