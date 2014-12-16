#include <boost/python.hpp>
#include <boost/python/overloads.hpp>

#include <string>

#include "Engine.h"
#include "WorldFascade.h"
#include "HeroFascade.h"
#include "Util.h"

using namespace std;
using namespace boost::python;

// Required for default argument overloading
BOOST_PYTHON_MEMBER_FUNCTION_OVERLOADS(heroMoveUp, HeroFascade::moveUp, 0, 1);
BOOST_PYTHON_MEMBER_FUNCTION_OVERLOADS(heroMoveDown, HeroFascade::moveDown, 0, 1);
BOOST_PYTHON_MEMBER_FUNCTION_OVERLOADS(heroMoveLeft, HeroFascade::moveLeft, 0, 1);
BOOST_PYTHON_MEMBER_FUNCTION_OVERLOADS(heroMoveRight, HeroFascade::moveRight, 0, 1);

/*
 * http://www-spires.slac.stanford.edu/BFROOT/www/doc/workbook_backup_010108/examples/ex1/workdir/PARENT/boost/libs/python/doc/tutorial/index.html
 */

BOOST_PYTHON_MODULE(gamelib) {
	class_<Engine>("Engine", init<string>())
		.def("getWorld", &Engine::getWorld)
		.def("getHero", &Engine::getHero)
		.def("reset", &Engine::resetEngine)
		.def("getResult", &Engine::getResult)
		.def("startSubmission", &Engine::startSubmission)
        .def ("endSubmission", &Engine::endSubmission)
        .def("startObjective", &Engine::startObjective)
        .def("endObjective", &Engine::endObjective); 

    class_<HeroFascade, shared_ptr<HeroFascade>>("Hero", no_init)
		.def("moveUp", &HeroFascade::moveUp, heroMoveUp())
		.def("moveDown", &HeroFascade::moveDown, heroMoveDown())
		.def("moveLeft", &HeroFascade::moveLeft, heroMoveLeft())
		.def("moveRight", &HeroFascade::moveRight, heroMoveRight());
        // TODO, expand with interaction later

	enum_<Direction>("direction")
		.value("up", Direction::UP)
		.value("down", Direction::DOWN)
		.value("right", Direction::RIGHT)
		.value("left", Direction::LEFT);
};
