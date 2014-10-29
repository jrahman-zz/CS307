#include <boost/python.hpp>

#include "Engine.h"
#include "WorldFascade.h"
#include "HeroFascade.h"
#include "Util.h"

using namespace boost::python

/*
 * See http://boost.cppll.jp/BDTJ_1_29/libs/python/doc/tutorial/index.html
 */

BOOST_PYTHON_MODULE(gamelib) {
	class_<Engine>("Engine", init<std::string>)
		.def("getWorld", &Engine::getWorld)
		.def("getHero", &Engine::getHero)
		.def("reset", &Engine::resetEngine)
		.def("getLog", &Engine::getEngine);

	class_<HeroFascade>("Hero")
		.def("moveUp", &HeroFascade::moveUp)
		.def("moveDown", &HeroFascade::moveDown)
		.def("moveLeft", &HeroFascade::moveLeft)
		.def("moveRight", &HeroFascade::moveRight);

	class_<WorldFascade>("World")
		.def("isOpen", &WorldFascade::isOpen);

	enum_<Direction>("direction")
		.value("up", UP)
		.value("down", DOWN)
		.value("right", RIGHT)
		.value("left", LEFT)
}
