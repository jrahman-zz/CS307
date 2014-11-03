#ifndef POSITION_H
#define POSITION_H

#include "json/json.h"

class Position {
public:
	Position(unsigned int x, unsigned int y);
	Position(Position& rhs);
	~Position();

	Json::Value toJson();

	unsigned int getX();
	unsigned int getY();
	void setX(unsigned int x);
	void setY(unsigned int y);

	bool operator<(const Position rhs) const {
		return m_x < rhs.m_x || (m_x == rhs.m_x && m_y < rhs.m_y);
	}

protected:
	unsigned int m_x, m_y;
};

#endif
