#include <iostream>
#include <string>

#include "util.h"

#include "TilemapParser.h"
#include "Engine.h"
#include "Hero.h"

#include "test_data_a.h"

string expected_log = R"({"classID":2,"completed":false,"levelID":1,"log":[[{"data":{"actorID":0,"position":{"x":15,"y":1}},"type":"move"},{"data":{"dialogue":"","objectiveId":42,"prompt":"Write an algorithm to solve the Traveling Salesman Problem","templateCode":"def tsp(graph, starting_point):\n    # TODO, implement the traveling salesman problem solution here\n    pass\n"},"type":"objective"}]],"nextLevel":-1,"userID":0}
)";

START_TEST("objective_start");
    Engine engine(testDataA);
    
    engine.startSubmission();

    auto hero = engine.getHero();
    if (hero == nullptr) {
        cout << "Failed to return hero" << endl;
        FAIL_TEST("objective_start");
    }

    // Activate the objective
    if (!hero->moveRight()) {
        cout << "moveRight() failed, movement failed to occur" << endl;
        FAIL_TEST("objective_start");
    }

    // Blocked since we started the objective
    if (hero->moveLeft()) {
        cout << "moveLeft() failed, movement occured after starting objective" << endl;
        FAIL_TEST("objective_start");
    }

    engine.endSubmission();

    auto log = engine.getResult();
    auto comp = log.compare(expected_log);
    if (comp) {
        cout << "Log doesn't matched expected, " << comp << ": " << endl
            << "Found: " << log << endl
            << "Expected: " << expected_log << endl;
        FAIL_TEST("objective_start");
    }

END_TEST("objective_start");
