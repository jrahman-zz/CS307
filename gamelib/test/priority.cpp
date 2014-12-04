#include <iostream>
#include <string>

#include "util.h"

#include "TilemapParser.h"
#include "Engine.h"
#include "Hero.h"

#include "test_data_d.h"

string expected_log = R"({"classID":2,"completed":false,"levelID":1,"log":[[{"data":{"actorID":1,"dialogue":"Hi first"},"type":"dialogue"},{"data":{"actorID":1,"dialogue":"Hi second"},"type":"dialogue"},{"data":{"dialogue":"","objectiveId":42,"prompt":"Write an algorithm to solve the Traveling Salesman Problem","templateCode":"def tsp(graph, starting_point):\n    # TODO, implement the traveling salesman problem solution here\n    pass\n"},"type":"objective"},{"data":{"actorID":0,"position":{"x":15,"y":1}},"type":"move"}]],"nextLevel":-1,"userID":0}
)";

START_TEST("priority");
    Engine engine(testDataD);
    
    engine.startSubmission();

    auto hero = engine.getHero();
    if (hero == nullptr) {
        cout << "Failed to return hero" << endl;
        FAIL_TEST("priority");
    }

    // Should not be allowed to move
    if (!hero->moveRight()) {
        cout << "moveRight() failed to move hero" << endl;
        FAIL_TEST("priority");
    }

    // Let's assume the objective passed
    engine.endSubmission();

    auto log = engine.getResult();
    auto comp = log.compare(expected_log);
    if (comp) {
        cout << "Log doesn't matched expected, " << comp << ": " << endl
            << "Found: " << log << endl
            << "Expected: " << expected_log << endl;
        FAIL_TEST("priority");
    }

END_TEST("priority");
