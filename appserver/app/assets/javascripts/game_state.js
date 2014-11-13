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
 * Holds information about in-game sprite.
 */
var SpriteEntity = function(id, type, type_class, start_x, start_y, rotation) {
  this.id = id;
  this.type = type; // Type SpriteType.
  this.type_class = type_class; // Defines class of character (dependent on type).
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
};

/**
 * Util method for parsing actors from JSON.
 */
GameState.prototype.parse_actor_objects = function(objects_json) {
  for (var j = 0; j < objects_json.length; j++) {
    var object_json = objects_json[j];
    var x = object_json['x'];
    var y = object_json['y'];
    var props_json = object_json['properties'];
    var object_id = props_json['id'];
    var rotation = props_json['rotation'];

    var sprite;
    switch (object_json['type']) {
      case 'hero':
        sprite = new SpriteEntity(object_id, SpriteType.HERO, 0, x, y, rotation);
        break;
      case 'enemy':
        sprite = new SpriteEntity(object_id, SpriteType.ENEMY, props_json['enemy_id'],
                                     x, y, rotation);
        break;
      case 'npc':
        sprite = new SpriteEntity(object_id, SpriteType.NPC, props_json['npc_id'],
                                     x, y, rotation);
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
            // Do nothing. Game library implements logic.
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
}

/**
 * Returns 2D array of form [timestep][animation_index]. Elements are type function(callback).
 */
GameState.prototype.parse_response = function(response_json) {
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
          var delay = 500; // ms.
          var anim = this.game.add.tween(entity.sprite).to(props, duration, 
              Phaser.Easing.Linear.None, false /* autoStart */, delay);

          // Closure.
          (function() {
            var anim_val = anim;
            var sprite_val = sprite;
            events.push(function (callback) {
              var anim_name = 'walk-' + direction_from(sprite_val.rotation);
              // TODO fix
              sprite_val.play('walk-' + direction_from(sprite_val.rotation), 15, true);
              anim_val.start();
              anim_val.onComplete.addOnce(function() {
                callback();
              });
            });
          })();
          break;
        case 'rotate':
          var actor_id = data_json['actorID'];
          var rotation = data_json['rotation'];

          var entity = this.entity_map[actor_id];

          // Closure to capture current rotation.
          (function() {
              var rot_value = rotation;
              events.push(function (callback) {
                // Wait 500ms, rotate, wait 500ms.
                setTimeout(function() {
                  entity.apply_rotation(rot_value);
                  setTimeout(callback, 500);
                }, 500);
              });
          })();
          break;
        case 'dialogue':
          // TODO implement
          break;
        case 'levelexit':
          // TODO implement
          break;
        default:
          console.log('Unknown log event type: ' + type);
          break;
      }
    }

    frames.push(events);
  }

  return frames;
}

/**
 * Process and play animations given from the response JSON.
 * Returns TODO indicate level switching
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
      event_func(function () {
        completed_count++;

        if (completed_count == events.length) {
          process_frames(f_index + 1); // Recursive call.
        } else {
          process_events(e_index + 1); // Recursive call.
        }
      } /* callback */);
    }
    process_events(0);
  }

  process_frames(0);
}
