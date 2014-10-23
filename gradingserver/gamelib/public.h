/*
 * The public-facing interface which provides C bindings to the game library.
 */

#pragma once

#include "game_state.h"

extern "C" {
  // Create new GameState object.
  GameState * GameState_New(const char *tilemap_json);

  // Retrieve updates from GameState object as JSON.
  // json_buf must be sufficiently large to hold returned JSON text.
  // Returns true on success, false if buf_size was insufficient.
  bool GameState_retrieve_update_json(GameState *state, char *update_json_buf, int buf_size);
}

