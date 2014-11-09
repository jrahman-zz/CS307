#include <iostream>
#include <string>

#include "util.h"

#include "TilemapParser.h"

#include "test_data_a.h"

using namespace std;

START_TEST("init");
	TilemapParser parser;

	try {
		if (parser.parse(testDataA)) {
			cout << "Passed test" << endl;
		} else {
		    FAIL_TEST("init");
        }
	} catch (exception e) {
		cout << "Exception " << e.what() << endl;
        FAIL_TEST("init");
	}
END_TEST("init");
