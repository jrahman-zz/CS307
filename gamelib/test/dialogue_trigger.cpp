#include <iostream>
#include <string>

#include "util.h"

#include "TilemapParser.h"
#include "Engine.h"
#include "Hero.h"

#include "test_data_b.h"

string expected_log = R"({"classID":2,"completed":false,"levelID":1,"log":[[{"data":{"actorID":0,"position":{"x":8,"y":2}},"type":"move"},{"data":{"actorID":0,"rotation":90},"type":"rotate"}],[{"data":{"actorID":0,"dialogue":"Hi"},"type":"dialogue"},{"data":{"actorID":0,"position":{"x":7,"y":2}},"type":"move"},{"data":{"actorID":0,"rotation":180},"type":"rotate"}],[{"data":{"actorID":0,"position":{"x":7,"y":1}},"type":"move"},{"data":{"actorID":0,"rotation":90},"type":"rotate"}],[{"data":{"actorID":0,"dialogue":"Hi"},"type":"dialogue"},{"data":{"actorID":0,"position":{"x":7,"y":2}},"type":"move"},{"data":{"actorID":0,"rotation":270},"type":"rotate"}]],"nextLevel":4294967295,"userID":0}
)";

START_TEST("DialogueTrigger");
    Engine engine(testDataA);
    auto hero = engine.getHero();
    if (hero == nullptr) {
        cout << "Failed to return hero" << endl;
        FAIL_TEST("DialogueTrigger");
    }

    if (!hero->moveUp()) {
        cout << "moveUp() failed, movement failed to occur" << endl;
        FAIL_TEST("DialogueTrigger");
    }

    if (!hero->moveLeft()) {
        cout << "moveLeft() failed, movement failed to occur" << endl;
        FAIL_TEST("DiagloueTrigger");
    }

    if (!hero->moveUp()) {
        cout << "moveUp() failed, movement failed to occur" << endl;
        FAIL_TEST("DialogueTrigger");
    }

    if (!hero->moveDown()) {
        cout << "moveDown() failed, movement failed to occur" << endl;
    }
    
    auto log = engine.getResult();
    auto comp = log.compare(expected_log);
    if (comp) {
        cout << "Log doesn't matched expected, " << comp << ": " << endl
            << "Found: " << log << endl
            << "Expected: " << expected_log << endl;
        FAIL_TEST("DialogueTrigger");
    }

END_TEST("DialogueTrigger");
