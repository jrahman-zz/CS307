#include <iostream>
#include <string>

#include "util.h"

#include "Engine.h"

using namespace std;

#include "test_data_c.h"

START_TEST("final");

	Engine engine(data);
	cout << "Passed test" << endl;

END_TEST("final");
