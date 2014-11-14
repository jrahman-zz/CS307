#include <iostream>
#include <string>

#include "util.h"

#include "TilemapParser.h"

using namespace std;

#include "test_data_c.h"

START_TEST("final");

	TilemapParser parser(data);
	cout << "Passed test" << endl;

END_TEST("final");
