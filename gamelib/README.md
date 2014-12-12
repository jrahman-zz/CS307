Basic Conventions for C++:
	Use 4 spaces, not tabs
	
	For functions/methods:
		int function(int argA, unsigned int argb) {
	
		}

	For class members:
		MyType m_mySpecialClassMember;

	For local varables and parameters:
		MyType myLocalVarOrParameter;

	Automatic type deduction:
		Use as often as is sane
		Saves significant time when refactoring
		Don't need to propegate changed type manually
		Type deduction automatically propegates when possible
		auto myVar = produceMyVar();

	In general, try to write idomatic c++11
		enum -> enum class
		T* -> shared_ptr<T>/weak_ptr<T> (If no cycle)
		Move constructors when it makes sense
		Tuples instead of one-off structs

	Good practices
		Sanity check inputs
		Provide reasonable behavior on failure
		Do not include printf()/cout in general code
			Exception for special debug methods


	Testing
		Write unit tests
		Create test_name.cpp file in tests folder
		make test to run tests
		Makefile will automatically pick up your test
