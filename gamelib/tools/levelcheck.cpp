#include <iostream>
#include <fstream>
#include <string>

#include "TilemapParser.h"

using namespace std;

int main(int argc, char **argv) {

    string levelJson;
    if (argc < 2) {
        cerr << argv[0] + string(" <filename>") << endl;
        return 1;
    } else {
        if (!string("-h").compare(argv[1]) || !string("--help").compare(argv[1])) {
            cerr << argv[0] + string(" <filename>") << endl;
            return 1;
        }

        string filename(argv[1]);
        // read entire file into string
        ifstream stream(filename, ifstream::binary);
        if (stream) {
            // get length of file:
            stream.seekg(0, stream.end);
            int length = stream.tellg();
            stream.seekg(0, stream.beg);
            levelJson.resize(length, ' '); // reserve space
            char* begin = &*levelJson.begin();
            stream.read(begin, length);
            stream.close();
        } else {
            cerr << "Failed to open " << filename << endl;
            return 1;
        }
    }

    // parse
    try {
        TilemapParser parser(levelJson);
    } catch (runtime_error e) {
        cerr << "Invalid level:" << endl
            << e.what() << endl;
        return 1;
    } catch (exception e) {
        cerr << "Exception thrown" << endl;
        return 1;
    }

    cout << string("File ") + argv[1] + string(" passed basic tests") << endl;
    return 0;
}
