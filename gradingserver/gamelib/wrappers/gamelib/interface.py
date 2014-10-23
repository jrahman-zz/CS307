#include <boost/python.hpp>

using namespace boost::python

# https://wiki.python.org/moin/boost.python/ExportingClasses

BOOST_PYTHON_MODULE(module)
{
	class_<gamelibclass>("gamelib", init<std::string>())
		.def("class_member_func", &hello::member_func)
		.def("non_member_func", non_member_func)
}

