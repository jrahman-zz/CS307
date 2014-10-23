/*
 * The public-facing interface which provides C bindings to the game library.
 */

#include <stdio.h>
#include "game_state.h"

extern "C" {

  // Create new GameState object with the given tilemap as a JSON string.
  GameState * GameState_new(const char *tilemap_json) {
    printf("HALLLLELUJAH\n");
    return new GameState(tilemap_json);
  }

  // Retrieve updates from GameState object as JSON.
  // update_json_buf must be sufficiently large to hold returned JSON text.
  // Returns true on success, false if buf_size was insufficient.
  int GameState_retrieve_update_json(GameState *state, char *update_json_buf, int buf_size) {
    return state->retrieve_update_json(update_json_buf, buf_size);
  }
}
