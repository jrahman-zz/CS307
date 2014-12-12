#ifndef CHARACTER_H
#define CHARACTER_H

#include "Moveable.h"
#include "Hero.h"
#include "json/json.h"

class Character : public Moveable {
public:
    Character(Json::Value value);
    virtual ~Character();

    virtual bool interact(Interactable& target);

protected:
    virtual bool interact_impl(Hero& target);
    virtual bool interact_impl(Enemy& target);
};

#endif // CHARACTER_H
