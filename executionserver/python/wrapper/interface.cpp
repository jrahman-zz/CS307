#include <boost/python.hpp>

#include <string>

#include "Engine.h"
#include "WorldFascade.h"
#include "HeroFascade.h"
#include "Util.h"

using namespace std;
using namespace boost::python;

/*
 * http://www-spires.slac.stanford.edu/BFROOT/www/doc/workbook_backup_010108/examples/ex1/workdir/PARENT/boost/libs/python/doc/tutorial/index.html
 */

BOOST_PYTHON_MODULE(gamelib) {
	class_<Engine>("Engine", init<string>())
		.def("getWorld", &Engine::getWorld)
		.def("getHero", &Engine::getHero)
		.def("reset", &Engine::resetEngine)
		.def("getLog", &Engine::getLog);
		// TODO

	class_<HeroFascade>("Hero", no_init)
		.def("moveUp", &HeroFascade::moveUp)
		.def("moveDown", &HeroFascade::moveDown)
		.def("moveLeft", &HeroFascade::moveLeft)
		.def("moveRight", &HeroFascade::moveRight);

	enum_<Direction>("direction")
		.value("up", Direction::UP)
		.value("down", Direction::DOWN)
		.value("right", Direction::RIGHT)
		.value("left", Direction::LEFT);
};
