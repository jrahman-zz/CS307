#ifndef HERO_H
#define HERO_H

#include <string>

#include "Interactable.h"
#include "Moveable.h"
#include "json/json.h"

using namespace std;

class Hero : public Moveable {
public:
	Hero(Json::Value json);
	virtual ~Hero();

};

#endif // HERO_H
