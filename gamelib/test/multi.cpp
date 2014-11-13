#include <iostream>
#include <string>

#include "util.h"

#include "TilemapParser.h"
#include "Engine.h"
#include "Hero.h"

#include "test_data_a.h"

string expected_log = R"({"classID":2,"completed":false,"levelID":1,"log":[[{"data":{"actorID":0,"position":{"x":14,"y":2}},"type":"move"},{"data":{"actorID":0,"rotation":270},"type":"rotate"}],[{"data":{"actorID":0,"position":{"x":14,"y":1}},"type":"move"},{"data":{"actorID":0,"rotation":90},"type":"rotate"}]],"nextLevel":4294967295,"userID":0}
)";

string expected_log2 = R"({"classID":2,"completed":false,"levelID":1,"log":[[{"data":{"actorID":0,"position":{"x":14,"y":2}},"type":"move"},{"data":{"actorID":0,"rotation":270},"type":"rotate"}],[{"data":{"actorID":0,"position":{"x":14,"y":3}},"type":"move"}]],"nextLevel":4294967295,"userID":0}
)";

START_TEST("multi");
    Engine engine(testDataA);
    auto hero = engine.getHero();

    if (hero == nullptr) {
        cout << "Failed to return hero" << endl;
        FAIL_TEST("multi");    
    }

    engine.startSubmission();
    if (!hero->moveDown()) {
        cout << "moveDown() failed" << endl;
        FAIL_TEST("multi");
    }

    if (!hero->moveUp()) {
        cout << "moveUp() failed" << endl;
        FAIL_TEST("multi");
    }

    auto log = engine.getResult();
    auto comp = log.compare(expected_log);
    if (comp) {
        cout << "Log doesn't matched expected, " << comp << ": " << endl
            << "Found: " << log << endl
            << "Expected: " << expected_log << endl;
        FAIL_TEST("multi");
    }

    engine.endSubmission();
    engine.startSubmission();

    if (!hero->moveDown()) {
        cout << "moveDown() failed" << endl;
        FAIL_TEST("multi");
    }

    if (!hero->moveDown()) {
        cout << "moveDown() failed" << endl;
        FAIL_TEST("multi");
    }

    auto log2 = engine.getResult();
    auto comp2 = log2.compare(expected_log2);
    if (comp2) {
        cout << "Log doesn't match expected, " << comp << ": " << endl
            << "Found: " << log2 << endl
            << "Expected: " << expected_log2 << endl;
        FAIL_TEST("multi");
    }

    engine.endSubmission();
END_TEST("multi");
