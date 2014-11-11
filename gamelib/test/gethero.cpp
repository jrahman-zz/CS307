#include <iostream>
#include <string>

#include "util.h"

#include "TilemapParser.h"
#include "Engine.h"
#include "Hero.h"

using namespace std;

#include "test_data_a.h"

START_TEST("actors");
	TilemapParser parser;
	parser.parse(testDataA);

	auto actors = parser.getActors();

    if (actors.size() != 3) {
        cout << "Incorrect actor count: " << actors.size() << endl;
        FAIL_TEST("actors");
    }

    Engine engine(testDataA);
    auto hero = engine.getHero();
    if (hero == nullptr) {
        cout << "Failed to return hero" << endl;
        FAIL_TEST("actors");
    }


    if (!hero->moveUp()) {
        cout << "Failed to move" << endl;
        FAIL_TEST("actors");
    }

END_TEST("actors");
