#ifndef POSITIONABLE_H
#define POSITIONABLE_H

#include <memory>

#include "Loggable.h"

#include "json/json.h"
#include "Position.h"

using namespace std;

class Positionable: public Loggable {
public:
    ~Positionable();

    Position getPosition() const;
    
    int getID() const;

protected:

    /* 
     * Prohibit default construction
     */
    Positionable() = delete;

    Positionable(Json::Value value);

    void setPosition(Position position); 

    int m_ID;

    Position m_position;
};

#endif
