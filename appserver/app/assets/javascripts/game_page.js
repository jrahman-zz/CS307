//= require jquery
//= require bootstrap
//= require jquery_ujs
//= require ace/ace
//= require ace/worker-html
//= require phaser
//= require util

// Configure Ace editor.
var editor = ace.edit('code-editor');
editor.setTheme('ace/theme/terminal');
editor.setFontSize(18);
editor.getSession().setMode('ace/mode/python');

// Enable popovers.
$(function() {
  $('[data-toggle="popover"]').popover();
});

// Constants.
var TileSize = 64;
var CanvasTileWidth = 18;
var CanvasTileHeight = 10;

var AnimMoveSpeed = 120; // pixels per second.

// SpriteType enum.
var SpriteType = {
  HERO: 'hero',
  ENEMY: 'enemy',
  NPC: 'npc'
};

// Holds information about in-game sprite.
var SpriteEntity = function (id, type, type_id, start_x, start_y, rotation) {
  this.id = id;
  this.type = type; // Type SpriteType.
  this.type_id = type_id; // Defines type of character (dependent on sprite_type).
  this.start_x = start_x;
  this.start_y = start_y;
  this.rotation = rotation; // In degrees. In range [0, 360).
  this.sprite = null; // Created by Phaser. Type Phaser.Sprite.
};

// Util method for parsing actors from JSON.
function parse_actor_objects(objects_json, entity_map) {
  for (var j = 0; j < objects_json.length; j++) {
    var object_json = objects_json[j];
    var x = object_json['x'];
    var y = object_json['y'];
    var props_json = object_json['properties'];
    var object_id = props_json['id'];
    var rotation = props_json['rotation'];

<<<<<<< HEAD
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

    if (entity_map[object_id]) {
      console.log('WARNING: object id overlap: ' + object_id);
      continue;
    }
    entity_map[object_id] = sprite;
  }
=======
  game.load.tilemap('sample-tilemap', null, get_level_tilemap(), Phaser.Tilemap.TILED_JSON);
  game.load.image('tiles', '/assets/spritesheets/RPGpack_sheet.png');
>>>>>>> app_server
}

// Functions inserted by play.html.haml.
var tilemap_url = get_level_tilemap();
var hero_gender = get_hero_gender();

// Load tilemap from file asynchronously.
var tilemap_promise = ajax_request_async('/assets/tilemaps/' + tilemap_url);
tilemap_promise.success(function (tilemap_str) {
  // Initialize level session with Execution server.
  var tilemap_json = JSON.parse(tilemap_str);

  // tileset IDs implicitly defined as 'tileset1', 'tileset2', ...
  // Array members are name of corresponding tileset as referenced in the tilemap.
  var tileset_names = [];

  // List of layers of type 'tilelayer' from level JSON.
  var tilelayer_names = [];

  // Keys are unique ids which are shared with the game library and defined by the "id": property.
  // Values are SpriteEntity objects corresponding to the id.
  var entity_map = {};

  var game = new Phaser.Game(CanvasTileWidth * TileSize, CanvasTileHeight * TileSize,
    Phaser.AUTO, 'canvas-container',
    { preload: preload, create: create, update: update, render: render },
    false /* transparent */, true /* antialias */);

  function preload() {
    // Load world tilemap.
    game.load.tilemap('world-tilemap', null, tilemap_str, Phaser.Tilemap.TILED_JSON);

    // Load and populate tilesets.
    var tilesets_json = tilemap_json['tilesets'];
    for (var i = 0; i < tilesets_json.length; i++) {
      var tileset_json = tilesets_json[i];
      var tileset_id = 'tileset' + i; // Guaranteed unique.
      var tileset_image_path = '/' + tileset_json['image'];
      game.load.image(tileset_id, tileset_image_path);
      var tileset_name = tileset_json['name'];
      tileset_names.push(tileset_name);
    }

    // Parse ActorLayer to prepare sprite info.
    var layers_json = tilemap_json['layers'];
    for (var i = 0; i < layers_json.length; i++) {
      var layer_json = layers_json[i];
      var layer_type = layer_json['type'];
      var layer_name = layer_json['name'];

      switch (layer_type) {
        case 'tilelayer':
          tilelayer_names.push(layer_json['name']);
          break;
        case 'objectgroup':
          var objects_json = layer_json['objects'];

          switch (layer_name) {
            case 'ActorLayer':
              parse_actor_objects(objects_json, entity_map);
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
    game.load.spritesheet('hero0-spritesheet', hero_spritesheet_path, TileSize, TileSize);

    // Load NPC spritesheets.
    // TODO make this dynamic.
    // Should follow format '<type><type_id>-spritesheet'
    game.load.spritesheet('npc1-spritesheet', '/assets/spritesheets/NPCs/LinkRight.png', TileSize, TileSize);
    game.load.spritesheet('npc0-spritesheet', '/assets/spritesheets/NPCs/PWizard2.png', TileSize, TileSize);


    // Example response JSON processing.
    // TODO replace with server call and prevent submission while animating.
    game.load.onLoadComplete.addOnce(function () {
      setTimeout(onLoadComplete, 1000);
    });
    function onLoadComplete() {
      var response_json = {
        "classID":2,
        "levelID":1,
        "log": [
        [{"data":{"actorID":0,"position":{"x":1,"y":7}},"type":"move"},{"data":{"actorID":0,"rotation":180},"type":"rotate"}],
          [{"data":{"actorID":0,"dialogue":"Hi"},"type":"dialogue"},{"data":{"actorID":0,"position":{"x":0,"y":7}},"type":"move"},{"data":{"actorID":0,"rotation":90},"type":"rotate"}],
          [{"data":{"actorID":0,"position":{"x":0,"y":6}},"type":"move"},{"data":{"actorID":0,"rotation":270},"type":"rotate"}],
          [{"data":{"actorID":0,"dialogue":"Hi 2"},"type":"dialogue"},{"data":{"actorID":0,"position":{"x":0,"y":7}},"type":"move"},{"data":{"actorID":0,"rotation":270},"type":"rotate"}]
          ],
        "nextLevel":-1,
        "userID":0
      };

      var events = parse_response(response_json);

      // Note: This is nasty recursion. I'll fix this
      // when I can think straight (and work around Javascripts serial nature).
      function process(index) {
        var anims = events[index];
        var completed_count = 0;
        for (var i = 0; i < anims.length; i++) {
          var anim = anims[i];
          anim.start();

          // All animations should finish at same time, but this
          // ensures synchronization.
          anim.onComplete.addOnce(function () {
            completed_count++;
            if (completed_count == anims.length) {
              var next_index = index + 1;
              if (next_index < events.length) {
                process(next_index); // Recursive!
              }
            }
          });
        }
      }

      if (events.length > 0) {
        process(0);
      }
    }
  }

  function create() {
    game.stage.backgroundColor = '#000000';

    world_tilemap = game.add.tilemap('world-tilemap');

    for (var i = 0; i < tileset_names.length; i++) {
      var tileset_name = tileset_names[i];
      world_tilemap.addTilesetImage(tileset_name, 'tileset' + i);
    }

    // Create tilemap layers.
    for (var i = 0; i < tilelayer_names.length; i++) {
      var tilelayer_name = tilelayer_names[i];
      world_tilemap.createLayer(tilelayer_name);
    }

    for (var id in entity_map) {
      var game_sprite = entity_map[id];

      var spritesheet = game_sprite.type + game_sprite.type_id + '-spritesheet';
      var sprite = game.add.sprite(game_sprite.start_x, game_sprite.start_y, spritesheet);
      game_sprite.sprite = sprite;

      if (game_sprite.sprite_type == SpriteType.HERO) {
        sprite.animations.add('walk-up', generate_list(0, 8), 15, true);
        sprite.animations.add('walk-left', generate_list(9, 17), 15, true);
        sprite.animations.add('walk-down', generate_list(18, 26), 15, true);
        sprite.animations.add('walk-right', generate_list(27, 35), 15, true);
      }
    }
  }

  function update() {

  }

  function render() {

  }

  /**
   * Returns 2D array of form [timestep][animation_index]. Objects are type Phaser.Tween.
   */
  function parse_response(response_json) {
    var events = [];

    var log_json = response_json['log'];
    var last_x, last_y;
    for (var timestep = 0; timestep < log_json.length; timestep++) {
      var events_json = log_json[timestep];

      // All anims are created and then iterated.
      var anims = [];

      for (var i = 0; i < events_json.length; i++) {
        var event_json = events_json[i];
        var type = event_json['type'];
        var data_json = event_json['data'];

        switch (type) {
          case 'move':
            var actor_id = data_json['actorID'];
            var pos_json = data_json['position'];
            var dest_x = pos_json['x'] * TileSize;
            var dest_y = pos_json['y'] * TileSize;

            var entity = entity_map[actor_id];
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
            var delay = 500;
            var anim = game.add.tween(sprite).to(props, duration,
                Phaser.Easing.Linear.None, false /* autoStart */, delay);

            anims.push(anim);
            break;
          case 'rotate':
            var actor_id = data_json['actorID'];
            var rotation = data_json['rotation'];

            var entity = entity_map[actor_id];
            var sprite = entity.sprite;

            // TODO genericize anims to function(callback) objects and
            // implement type_id specific logic to rotate sprite orientation.
            // ex. hero:
            // switch (entity.rotation) {
            //   case 0:
            //     sprite.frame = 27;
            //     break;
            //   case 90:
            //     sprite.frame = 0;
            //     break;
            //   case 180:
            //     sprite.frame = 9;
            //     break;
            //   case 270:
            //     sprite.frame = 18;
            //     break;
            //   default:
            //     console.log('Invalid rotation value: ' + entity.rotation);
            //     break;
            // }
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

      events.push(anims);
    }

    return events;
  }

  // Intercept click events on the submit button.
  $('#submit_button').click(function(event) {
    var code = editor.getValue();
    console.log('code: ' + code);
    // TODO send code
  });
});
