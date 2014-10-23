#pragma once

#include <vector>
#include "actor.h"

class GameState {
  private:
    std::vector<Actor *> actors;
  
  public:
    GameState(const char *tilemap_json);
    ~GameState();

    bool retrieve_update_json(char *update_json_buf, int buf_size);
};
