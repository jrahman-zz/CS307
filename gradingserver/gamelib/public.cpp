/*
 * The public-facing interface which provides C bindings to the game library.
 */

#include "game_state.h"

GameState * GameState_New(const char *tilemap) {
  return new GameState(tilemap);
}

bool GameState_retrieve_update_json(GameState *state, char *update_json_buf, int buf_size) {
  return state->retrieve_update_json(update_json_buf, buf_size);
}

