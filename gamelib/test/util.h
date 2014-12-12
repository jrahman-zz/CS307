#define START_TEST(name) using namespace std;   \
int main(int argc, char **argv) {               \
    cout << "Starting test " << (name) << endl

#define END_TEST(name) cout << "Passed test " << (name) << endl; \
    return 0;                                   \
}

#define FAIL_TEST(name) cout << "Failed test " << (name) << endl; \
    return 1
