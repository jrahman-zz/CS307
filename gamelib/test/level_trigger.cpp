#include <iostream>
#include <string>

#include "util.h"

#include "TilemapParser.h"
#include "Engine.h"
#include "Hero.h"

#include "test_data_b.h"

string expected_log = R"({"classID":2,"completed":true,"levelID":1,"log":[[{"data":{"actorID":0,"rotation":90},"type":"rotate"},{"data":{"actorID":0,"position":{"x":8,"y":2}},"type":"move"}],[{"data":{"actorID":0,"position":{"x":8,"y":1}},"type":"move"}]],"nextLevel":1,"userID":0}
)";

START_TEST("LevelExitTrigger");
    Engine engine(testDataA);
    auto hero = engine.getHero();
    if (hero == nullptr) {
        cout << "Failed to return hero" << endl;
        FAIL_TEST("LevelExitTrigger");
    }

    // Building in the way, should not move
    if (!hero->moveUp()) {
        cout << "moveUp() failed, movement failed to occur" << endl;
        FAIL_TEST("LevelExitTrigger");
    }

    // Enemy in the way
    if (!hero->moveUp()) {
        cout << "moveUp() failed, movement failed to occur" << endl;
        FAIL_TEST("LevelExitTrigger");
    }

    // Stopped since we hit the trigger
    if (hero->moveUp()) {
        cout << "moveUp() failed, movement occured following trigger" << endl;
        FAIL_TEST("LevelExitTrigger");
    }

    auto log = engine.getResult();
    auto comp = log.compare(expected_log);
    if (comp) {
        cout << "Log doesn't matched expected, " << comp << ": " << endl
            << "Found: " << log << endl
            << "Expected: " << expected_log << endl;
        FAIL_TEST("LevelExitTrigger");
    }

END_TEST("LevelExitTrigger");
