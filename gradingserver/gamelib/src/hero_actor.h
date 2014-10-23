#pragma once

#include "actor.h"

class HeroActor: public Actor {
  private:
    double health;

  public:
    HeroActor();
    ~HeroActor();

    virtual void update();
};
