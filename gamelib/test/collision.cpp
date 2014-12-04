#include <iostream>
#include <string>

#include "util.h"

#include "TilemapParser.h"
#include "Engine.h"
#include "Hero.h"

#include "test_data_b.h"

string expected_log = R"({"classID":2,"completed":false,"levelID":1,"log":[[{"data":{"actorID":0,"rotation":270},"type":"rotate"}],[{"data":{"actorID":0,"rotation":180},"type":"rotate"}],[{"data":{"actorID":0,"position":{"x":8,"y":2}},"type":"move"},{"data":{"actorID":0,"rotation":90},"type":"rotate"}]],"nextLevel":-1,"userID":0}
)";

START_TEST("actors");
    Engine engine(testDataA);
    
    engine.startSubmission();

    auto hero = engine.getHero();
    if (hero == nullptr) {
        cout << "Failed to return hero" << endl;
        FAIL_TEST("actors");
    }

    // Building in the way, should not move
    if (hero->moveDown()) {
        cout << "moveDown() failed, movement occured when blocked" << endl;
        FAIL_TEST("actors");
    }

    // Enemy in the way
    if (hero->moveLeft()) {
        cout << "moveLeft() failed, movement occured when blocked" << endl;
        FAIL_TEST("actors");
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
        FAIL_TEST("actors");
    }

END_TEST("actors");
