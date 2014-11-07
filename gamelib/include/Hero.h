#ifndef HERO_H
#define HERO_H

#include "Interactable.h"
#include "Moveable.h"
#include "json/json.h"

using namespace std;

class Hero : public Moveable {
public:
    Hero(Json::Value json);
    virtual ~Hero();
 
    virtual bool interact(Interactable& obj);

protected:

    /*
     * Double dispatch
     */
    virtual bool interact_impl(Hero& hero);
    virtual bool interact_impl(Enemy& enemy);
    

};

#endif // HERO_H
