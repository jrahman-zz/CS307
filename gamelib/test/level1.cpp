#include <iostream>
#include <string>

#include "util.h"

#include "TilemapParser.h"
#include "Engine.h"
#include "Hero.h"

#include "test_data_e.h"

string expected_log = R"({"classID":4,"completed":false,"levelID":7,"log":[[{"data":{"actorID":0,"position":{"x":4,"y":9}},"type":"move"},{"data":{"actorID":0,"rotation":270},"type":"rotate"}],[{"data":{"actorID":0,"position":{"x":3,"y":9}},"type":"move"},{"data":{"actorID":0,"rotation":180},"type":"rotate"}],[{"data":{"actorID":0,"position":{"x":3,"y":8}},"type":"move"},{"data":{"actorID":0,"rotation":90},"type":"rotate"}]],"nextLevel":-1,"userID":5}
)";

START_TEST("level1");
    Engine engine(testDataA);
    
    engine.startSubmission();

    auto hero = engine.getHero();
    if (hero == nullptr) {
        cout << "Failed to return hero" << endl;
        FAIL_TEST("level1");
    }

    // Building in the way, should not move
    if (!hero->moveUp()) {
        cout << "moveUp() failed, movement failed to occur" << endl;
        FAIL_TEST("level1");
    }

    // Enemy in the way
    if (!hero->moveLeft()) {
        cout << "moveLeft() failed, movement failed to occur" << endl;
        FAIL_TEST("level1");
    }

    if (!hero->moveUp()) {
        cout << "moveUp() failed, movement didn't occur when not blocked" << endl;
    }

    engine.endSubmission();

    auto log = engine.getResult();
    auto comp = log.compare(expected_log);
    if (comp) {
        cout << "Log doesn't matched expected, " << comp << ": " << endl
            << "Found: " << log << endl
            << "Expected: " << expected_log << endl;
        FAIL_TEST("level1");
    }

END_TEST("level1");
