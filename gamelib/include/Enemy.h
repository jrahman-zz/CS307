#ifndef ENEMY_H
#define ENEMY_H

#include "Moveable.h"
#include "Hero.h"
#include "json/json.h"

class Enemy : public Moveable {
public:
    Enemy(Json::Value value);
    virtual ~Enemy();

    virtual bool interact(Interactable& target);

protected:
    virtual bool interact_impl(Hero& target);
    virtual bool interact_impl(Enemy& target);
};

#endif // ENEMY_H
