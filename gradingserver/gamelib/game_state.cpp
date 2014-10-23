#include "game_state.h"

#include <string.h>
#include "hero_actor.h"

GameState::GameState(const char *tilemap_json) {
  Actor *a = new HeroActor;
  actors.push_back(a);
}

GameState::~GameState() {
  for (Actor *a : actors) {
    delete a;
  }
  actors.clear();
}

bool retrieve_update_json(char *update_json_buf, int buf_size) {
  strcpy(update_json_buf, "1234");
  return true;
}

