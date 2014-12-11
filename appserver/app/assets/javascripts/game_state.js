/**
 * SpriteType enum.
 */
var SpriteType = {
  HERO: 'hero',
  ENEMY: 'enemy',
  NPC: 'npc'
};

/**
 * Direction enum.
 */
var Direction = {
  RIGHT: 'right',
  UP: 'up',
  LEFT: 'left',
  DOWN: 'down'
};

// Constants
var AnimMoveSpeed = 120; // pixels per second.

var HeroDirectionFrameMap = {};
HeroDirectionFrameMap[Direction.RIGHT] = 27;
HeroDirectionFrameMap[Direction.UP] = 0;
HeroDirectionFrameMap[Direction.LEFT] = 9;
HeroDirectionFrameMap[Direction.DOWN] = 18;

/**
 * Attempts to map rotation angle to Direction.
 */
function direction_from(rotation) {
  switch (rotation) {
    case 0: return Direction.RIGHT;
    case 90: return Direction.UP;
    case 180: return Direction.LEFT;
    case 270: return Direction.DOWN;
  }
  return null;
}

/**
 * Holds information about objectives (challenges).
 */
var Objective = function(id, name, prompt) {
  this.id = id;
  this.name = name;
  this.prompt = prompt;
  this.templateCode = null; // Set from event log.
  this.active = false;
  this.completed = false;
};

/**
 * Holds information about in-game sprite.
 */
var SpriteEntity = function(id, type, type_class, name, start_x, start_y, rotation) {
  this.id = id;
  this.type = type; // Type SpriteType.
  this.type_class = type_class; // Defines class of character (dependent on type).
  this.name = name;
  this.start_x = start_x;
  this.start_y = start_y;
  this.rotation = rotation; // In degrees. In range [0, 360).
  this.sprite = null; // Created by Phaser. Type Phaser.Sprite.
};

SpriteEntity.prototype.apply_rotation = function(rotation) {
  this.rotation = rotation;
  var dir = direction_from(rotation);
  if (!dir) {
    console.log('Warning: Failed to map rotation to direction: ' + rotation);
    return;
  }

  this.apply_direction(dir);
}

SpriteEntity.prototype.apply_direction = function(direction) {
  switch (this.type) {
    case SpriteType.HERO:
      var new_frame = HeroDirectionFrameMap[direction];
      this.sprite.frame = new_frame;
      break;
    default:
      // Direction not implemented.
      break;
  }
}

/**
 * Event type enum.
 */
var EventType = {
  MOVE: 'move',
  ROTATE: 'rotate',
  DIALOGUE: 'dialogue',
  OBJECTIVE: 'objective',
  OBJECTIVE_COMPLETE: 'objective-complete',
  LEVEL_EXIT: 'level-exit'
};

var Event = function(type, data) {
  this.type = type; // type EventType.
  this.data = data;
};

Event.prototype.execute = function(game_state, callback) {
  var entity_map = game_state.entity_map;

  switch (this.type) {
    case EventType.MOVE:
      var actor_id = this.data['actorID'];
      var anim = this.data['anim'];

      var entity = entity_map[actor_id];
      entity.sprite.animations.play('walk-' + direction_from(entity.rotation), 15, true);
      anim.start();
      anim.onComplete.addOnce(function() {
        entity.sprite.animations.stop();
        callback();
      });
      break;
    case EventType.ROTATE:
      var actor_id = this.data['actorID'];
      var rotation = this.data['rotation'];
      var entity = entity_map[actor_id];
      // Wait 500ms, rotate, wait 500ms.
      setTimeout(function() {
        entity.apply_rotation(rotation);
        setTimeout(callback, 500);
      }, 500);
      break;
    case EventType.DIALOGUE:
      var actor_id = this.data['actorID'];
      var dialogue = this.data['dialogue'];
      var entity = entity_map[actor_id];

      var full_text = entity.name + ': ' + dialogue;
      var lines = segment_text(full_text, 78);
      game_state.animate_text(lines, callback);
      break;
    case EventType.OBJECTIVE:
      var id = this.data['objectiveId'];
      var prompt = this.data['prompt'];
      var templateCode = this.data['templateCode'];

      // Set all objectives inactive.
      for (var j = 0; j < game_state.objectives.length; j++) {
        game_state.objectives[j].active = false;
      }

      // Find objective specified by id.
      var objective;
      for (var i = 0; i < game_state.objectives.length; i++) {
        var o = game_state.objectives[i];
        if (o.id == id) {
          objective = o;
          game_state.context = i;
          break;
        }
      }

      if (objective) {
        objective.templateCode = templateCode;
        objective.active = true;
      } else {
        console.log('WARNING: unrecognized objective id: ' + id);
      }
      callback();
      break;
    case EventType.OBJECTIVE_COMPLETE:
      // Mark active objective complete and set inactive.
      var activeObjective = game_state.objectives[game_state.context];
      activeObjective.active = false;
      activeObjective.complete = true;
      game_state.context = -1;
      callback();
      break;
    case EventType.LEVEL_EXIT:
      var nextLevel = this.data['nextLevel'];
      game_state.next_level = nextLevel;
      break;
    default:
      console.log('Unrecognized event type: ' + this.type);
      break;
  }
}

/**
 * The state of the game, man. It's pretty self explanatory
 */
var GameState = function(game, tile_size) {
  this.game = game;
  this.tile_size = tile_size;

  this.world_tilemap = null;

  // tileset IDs implicitly defined as 'tileset1', 'tileset2', ...
  // Array members are name of corresponding tileset as referenced in the tilemap.
  this.tileset_names = [];

  // List of layers of type 'tilelayer' from level JSON.
  this.tilelayer_names = [];

  // Keys are unique ids which are shared with the game library and defined by the "id": property.
  // Values are SpriteEntity objects corresponding to the id.
  this.entity_map = {};

  this.dialogue_text_index = 0;
  this.dialogue_texts = null;

  this.dialogue_line_index = 0;
  this.dialogue_lines = null;
  this.dialogue_line = null;
  this.dialogue_curr = null;
  this.dialogue_char_index = 0;
  this.dialogue_callback = null;

  // List of Objective objects.
  this.objectives = [];
  // -1 if in navigation context. Otherwise, index indicating current challenge
  // in objectives array.
  this.context = -1;

  // If non-zero, indicates index of next level.
  this.next_level = -1;
};

/**
 * Util method for parsing actors from JSON.
 */
GameState.prototype.parse_actor_objects = function(objects_json) {
  for (var j = 0; j < objects_json.length; j++) {
    var object_json = objects_json[j];
    var x = object_json['x'];
    var y = object_json['y'];
    var name = object_json['name'];
    var props_json = object_json['properties'];

    var object_id = props_json['id'];
    var rotation = props_json['rotation'];

    var sprite;
    switch (object_json['type']) {
      case 'hero':
        sprite = new SpriteEntity(object_id, SpriteType.HERO, 0, name,
                                  x, y, Number(rotation));
        break;
      case 'enemy':
        sprite = new SpriteEntity(object_id, SpriteType.ENEMY, props_json['enemy_id'], name,
                                  x, y, Number(rotation));
        break;
      case 'npc':
        sprite = new SpriteEntity(object_id, SpriteType.NPC, props_json['npc_id'], name,
                                  x, y, Number(rotation));
        break;
      default:
        console.log('Unknown object type: ' + object_json['type']);
        continue;
    }

    if (this.entity_map[object_id]) {
      console.log('WARNING: object id overlap: ' + object_id);
      continue;
    }
    this.entity_map[object_id] = sprite;
  }
}

/**
 * Parses objective information from JSON.
 */
GameState.prototype.parse_trigger_objects = function(objects_json) {
  for (var i = 0; i < objects_json.length; i++) {
    var object_json = objects_json[i];
    var props_json = object_json['properties'];
    switch (object_json['type']) {
      case 'objective':
        var id = props_json['objectiveId'];
        var objective = new Objective(id, props_json['name'], props_json['prompt']);
        this.objectives.push(objective);
        break;
      default: // Don't care about other triggers. Gamelib handles logic.
        break;
    }
  }
}

/**
 * Call this within Phaser's preload function.
 */
GameState.prototype.load = function(tilemap_json) {
  // Load and populate tilesets.
  var tilesets_json = tilemap_json['tilesets'];
  for (var i = 0; i < tilesets_json.length; i++) {
    var tileset_json = tilesets_json[i];
    var tileset_id = 'tileset' + i; // Guaranteed unique.
    var tileset_image_path = '/' + tileset_json['image'];
    this.game.load.image(tileset_id, tileset_image_path);
    var tileset_name = tileset_json['name'];
    this.tileset_names.push(tileset_name);
  }

  // Parse ActorLayer to prepare sprite info.
  var layers_json = tilemap_json['layers'];
  for (var i = 0; i < layers_json.length; i++) {
    var layer_json = layers_json[i];
    var layer_type = layer_json['type'];
    var layer_name = layer_json['name'];

    switch (layer_type) {
      case 'tilelayer':
        this.tilelayer_names.push(layer_json['name']);
        break;
      case 'objectgroup':
        var objects_json = layer_json['objects'];

        switch (layer_name) {
          case 'ActorLayer':
            this.parse_actor_objects(objects_json);
            break;
          case 'TriggerLayer':
            this.parse_trigger_objects(objects_json);
            break;
          default:
            console.log('Unknown objectgroup layer name: ' + layer_name);
            break;
        }
        break;
      default:
        console.log('Unknown layer type: ' + layer_type);
        break;
    }
  }

  // Load hero spritesheet.
  var hero_spritesheet_path = '/assets/spritesheets/heroes/' + hero_gender + '/walk.png';
  this.game.load.spritesheet('hero0-spritesheet', hero_spritesheet_path, this.tile_size, this.tile_size);

  // Load NPC spritesheets.
  // TODO make this dynamic.
  // Should follow format '<type><type_class>-spritesheet'
  this.game.load.spritesheet('npc1-spritesheet', '/assets/spritesheets/NPCs/LinkRight.png', this.tile_size, this.tile_size);
  this.game.load.spritesheet('npc0-spritesheet', '/assets/spritesheets/NPCs/PWizard2.png', this.tile_size, this.tile_size);
}

/**
 * Call this within Phaser's create function.
 */
GameState.prototype.create = function() {
  this.world_tilemap = this.game.add.tilemap('world-tilemap');

  for (var i = 0; i < this.tileset_names.length; i++) {
    var tileset_name = this.tileset_names[i];
    this.world_tilemap.addTilesetImage(tileset_name, 'tileset' + i);
  }

  // Create tilemap layers.
  for (var i = 0; i < this.tilelayer_names.length; i++) {
    var tilelayer_name = this.tilelayer_names[i];
    this.world_tilemap.createLayer(tilelayer_name);
  }

  for (var id in this.entity_map) {
    var game_sprite = this.entity_map[id];

    var spritesheet = game_sprite.type + game_sprite.type_class + '-spritesheet';
    var sprite = this.game.add.sprite(game_sprite.start_x, game_sprite.start_y, spritesheet);
    game_sprite.sprite = sprite;

    if (game_sprite.type == SpriteType.HERO) {
      sprite.animations.add('walk-up', generate_list(0, 8), 15, true);
      sprite.animations.add('walk-left', generate_list(9, 17), 15, true);
      sprite.animations.add('walk-down', generate_list(18, 26), 15, true);
      sprite.animations.add('walk-right', generate_list(27, 35), 15, true);
    }
  }

  var style = { font: '18pt Courier', fill: '#04750B', stroke: '#000000', strokeThickness: 2 };
  this.dialogue_texts = [
    this.game.add.text(24, 18, '', style),
    this.game.add.text(24, 64, '', style)
  ];
}

/**
 * Returns 2D array of form [timestep][animation_index]. Elements are type function(callback).
 */
GameState.prototype.parse_response = function(response_json) {
  var nextLevel = response_json['nextLevel'];
  if (nextLevel != -1) {
    this.next_level = nextLevel;
  }

  var frames = [];

  var log_json = response_json['log'];
  var last_x, last_y;
  for (var timestep = 0; timestep < log_json.length; timestep++) {
    var events_json = log_json[timestep];

    // All anims are created and then iterated.
    var events = [];

    for (var i = 0; i < events_json.length; i++) {
      var event_json = events_json[i];
      var type = event_json['type'];
      var data_json = event_json['data'];

      var e;
      switch (type) {
        case 'move':
          var actor_id = data_json['actorID'];
          var pos_json = data_json['position'];
          var dest_x = pos_json['x'] * this.tile_size;
          var dest_y = pos_json['y'] * this.tile_size;

          var entity = this.entity_map[actor_id];
          var sprite = entity.sprite;
          if (last_x === undefined || last_y === undefined) {
            last_x = sprite.x;
            last_y = sprite.y;
          }

          var props = { x: dest_x, y: dest_y };
          var distance = distance_between(last_x, last_y, dest_x, dest_y);
          last_x = dest_x;
          last_y = dest_y;
          var duration = distance / AnimMoveSpeed * 1000;
          var delay = 100; // ms.
          var anim = this.game.add.tween(entity.sprite).to(props, duration, 
              Phaser.Easing.Linear.None, false /* autoStart */, delay);
          
          var data = { 'actorID': actor_id, 'anim': anim };
          e = new Event(EventType.MOVE, data);
          break;
        case 'rotate':
          e = new Event(EventType.ROTATE, data_json);
          break;
        case 'dialogue':
          e = new Event(EventType.DIALOGUE, data_json);
          break;
        case 'objective':
          e = new Event(EventType.OBJECTIVE, data_json);
          break;
        case 'completedobjective':
          e = new Event(EventType.OBJECTIVE_COMPLETE, null);
          break;
        default:
          console.log('Unknown log event type: ' + type);
          break;
      }
      if (e) {
        events.push(e);
      }
    }

    frames.push(events);
  }

  return frames;
}

/**
 * Process and play animations given from the response JSON.
 */
GameState.prototype.process_response = function(response_json, callback) {
  var frames = this.parse_response(response_json);

  // This recursion may be converted to use setTimeout in the future.
  function process_frames(f_index) {
    if (f_index == frames.length) {
      callback();
      return;
    }

    var events = frames[f_index];
    var completed_count = 0;
    
    function process_events(e_index) {
      var event_func = events[e_index];
      var this_ref = this;
      event_func.execute(this_ref, function () {
        completed_count++;

        if (completed_count == events.length) {
          process_frames.bind(this_ref)(f_index + 1); // Recursive call.
        } else {
          process_events.bind(this_ref)(e_index + 1); // Recursive call.
        }
      } /* callback */);
    }
    process_events.bind(this)(0);
  }

  process_frames.bind(this)(0);
}

/**
 * Animates displaying given text.
 */
GameState.prototype.animate_text = function(lines, callback) {
  this.dialogue_text_index = -1;
  this.dialogue_line_index = 0;
  this.dialogue_lines = lines;
  this.dialogue_callback = callback;
  animate_line.bind(this)();
}

function animate_line() {
  if (this.dialogue_line_index == this.dialogue_lines.length) {
    var this_ref = this;
    setTimeout(function() {
      for (var i = 0; i < this_ref.dialogue_texts.length; i++) {
        this_ref.dialogue_texts[i].setText('');
      }
      this_ref.dialogue_callback();
    }, 1000);
  } else {
    if (this.dialogue_text_index < this.dialogue_texts.length - 1) {
      this.dialogue_text_index++;
    } else {
      // Shift text.
      for (var i = 0; i < this.dialogue_texts.length - 1; i++) {
        this.dialogue_texts[i].setText(this.dialogue_texts[i+1].text);
      }
    }

    this.dialogue_line = this.dialogue_lines[this.dialogue_line_index];
    this.dialogue_curr = '';
    this.dialogue_char_index = 0;
    this.game.time.events.repeat(28, this.dialogue_lines[this.dialogue_line_index].length + 1, animate_line_tick, this);
  }
}

function animate_line_tick() {
  if (this.dialogue_char_index == this.dialogue_line.length) {
    this.dialogue_line_index++;

    this.game.time.events.add(500, animate_line, this);
  } else {
    this.dialogue_curr += this.dialogue_line[this.dialogue_char_index];
    this.dialogue_char_index++;

    this.dialogue_texts[this.dialogue_text_index].setText(this.dialogue_curr);
  }
}