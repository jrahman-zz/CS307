import ctypes

lib = ctypes.cdll.LoadLibrary('./libgame.so')

tilemap_json = ctypes.c_char_p('json blah blah blah')
state = lib.GameState_new(tilemap_json)

json_buf = ctypes.create_string_buffer(256)
lib.GameState_retrieve_update_json(state, json_buf, 256)

print 'Received: ' + repr(json_buf.value)
