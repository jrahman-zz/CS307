#ifndef POSITION_H
#define POSITION_H

#include "json/json.h"

class Position {
public:
	Position(unsigned int x, unsigned int y);
	~Position();

	Json::Value toJson();

	unsigned int getX();
	unsigned int getY();
	void setX(unsigned int x);
	void setY(unsigned int y);

protected:
	unsigned int x, y;
};

#endif
