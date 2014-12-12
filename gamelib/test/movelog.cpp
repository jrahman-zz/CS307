#include "ActionLog.h"
#include "Position.h"
#include "MoveLogEntry.h"
#include "TimeKeeper.h"

#include "json/json.h"

#include <memory>
#include <iostream>

#include "util.h"

using namespace std;

auto master = R"([[{"data":{"actorID":0,"position":{"x":0,"y":1}},"timestamp":0,"type":"move"}],[],[],[{"data":{"actorID":0,"position":{"x":2,"y":3}},"timestamp":3,"type":"move"},{"data":{"actorID":1,"position":{"x":1,"y":1}},"timestamp":3,"type":"move"}]])";


START_TEST("movelog");
    shared_ptr<LogEntry> moveA(new MoveLogEntry(0, Position(0, 1)));
    shared_ptr<LogEntry> moveB(new MoveLogEntry(1, Position(1, 1)));
    shared_ptr<LogEntry> moveC(new MoveLogEntry(0, Position(2, 3)));

    shared_ptr<TimeKeeper> timekeeper(new TimeKeeper());
    ActionLog log(timekeeper);
    if (!log.onLog(moveA)) {
        cout << "Failed to add moveA" << endl;
        FAIL_TEST("movelog");
    }
    
    timekeeper->incrementClock();
    timekeeper->incrementClock();

    if (!log.onLog(moveB)) {
        cout << "Failed to add moveB" << endl;
        FAIL_TEST("movelog");
    }

    if (!log.onLog(moveC)) {
        cout << "Failed to add moveC" << endl;
        FAIL_TEST("movelog");
    }

    auto json = log.getJsonLog();
    Json::FastWriter writer;
    auto str = writer.write(json);
    
    if (!str.compare(master)) {
        cout << "Failed to match expected output" << endl;
        cout << "Expected:" << endl;
        cout << master << endl;
        cout << "Observed:" << endl;
        cout << str << endl;
        FAIL_TEST("movelog");
    }
END_TEST("movelog"); 
