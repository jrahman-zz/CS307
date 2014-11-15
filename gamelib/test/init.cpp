#include <iostream>
#include <string>

#include "util.h"

#include "Engine.h"

#include "test_data_a.h"

using namespace std;

START_TEST("init");

	try {
		Engine engine(testDataA);
		cout << "Passed test" << endl;
	} catch (exception e) {
		cout << "Exception " << e.what() << endl;
        FAIL_TEST("init");
	}
END_TEST("init");
