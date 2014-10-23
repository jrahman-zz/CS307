#include "hero_actor.h"

static const double DefaultHealth = 1000.0;

HeroActor::HeroActor() {
  health = DefaultHealth;
}

HeroActor::~HeroActor() {

}

void HeroActor::update() {
  // Infinite powerrrr
  health++;
}
