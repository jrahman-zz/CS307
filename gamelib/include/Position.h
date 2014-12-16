#ifndef POSITION_H
#define POSITION_H

#include "json/json.h"

using namespace std;

class Position {
public:
    Position(int x, int y);
    Position(const Position& rhs);
    Position();

    Json::Value toJson() const;

    int getX() const;
    int getY() const;
    void setX(int x);
    void setY(int y);

    string toString() const;

    bool operator==(const Position& other) const {
        return other.m_x == m_x && other.m_y == m_y && isValid() == other.isValid();
    }

    bool operator!=(const Position& other) const {
        return !(other == *this);
    }

protected: 
    bool isValid() const;

    int m_x, m_y;
    bool m_xValid;
    bool m_yValid;
};


#include <iostream>

namespace std {
    template <>
        class hash<Position> {
            public:
            size_t operator()(const Position& K) const {
                using std::size_t;
                using std::hash;
                using std::string;
                string str = K.toString();
                size_t h = hash<string>()(str);
                return h;
            }
        };
}

#endif
