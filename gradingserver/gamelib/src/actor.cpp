#include "actor.h"

Actor::Actor() {
  static int Counter = 0;
  id = Counter;
  Counter++;
}
