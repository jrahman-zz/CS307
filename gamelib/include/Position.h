#ifndef POSITION_H
#define POSITION_H

#include "json/json.h"

using namespace std;

class Position {
public:
    Position(unsigned int x, unsigned int y);
    Position(const Position& rhs);
    Position();
    ~Position();

    Json::Value toJson() const;

    unsigned int getX() const;
    unsigned int getY() const;
    void setX(unsigned int x);
    void setY(unsigned int y);

    bool operator==(const Position& other) const {
        return other.m_x == m_x && other.m_y == m_y;
    }

protected:
    unsigned int m_x, m_y;

    bool m_valid;
};

namespace std {
    template <>
        class hash<Position> {
            public:
            std::size_t operator()(const Position& K) const {
                using std::size_t;
                using std::hash;
                using std::string;
                auto str = K.getX() + ":" + K.getY();
                return hash<string>()(str);
            }
        };
}

#endif
