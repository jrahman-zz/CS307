#include <iostream>
#include <string>

#include "util.h"

#include "TilemapParser.h"
#include "Engine.h"
#include "Hero.h"

#include "test_data_a.h"

string expected_log = R"({"classID":2,"completed":false,"levelID":1,"log":[],"nextLevel":-1,"userID":0}
)";

START_TEST("objective_block");
    Engine engine(testDataA);
    
    engine.startObjective();

    auto hero = engine.getHero();
    if (hero == nullptr) {
        cout << "Failed to return hero" << endl;
        FAIL_TEST("objective_block");
    }

    // Should not be allowed to move
    if (hero->moveRight()) {
        cout << "moveRight() moved hero illegally during objective" << endl;
        FAIL_TEST("objective_block");
    }

    // Let's assume the objective passed
    engine.endObjective(true);

    auto log = engine.getResult();
    auto comp = log.compare(expected_log);
    if (comp) {
        cout << "Log doesn't matched expected, " << comp << ": " << endl
            << "Found: " << log << endl
            << "Expected: " << expected_log << endl;
        FAIL_TEST("objective_block");
    }

END_TEST("objective_block");
