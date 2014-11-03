//= require jquery
//= require jquery_ujs
//= require phaser

// Utility functions.

function default_for(arg, defaultVal) {
  return (typeof arg === 'undefined' ? defaultVal : arg)
}

function generate_list(low, high) {
  var list = [];
  while (low <= high) {
    list.push(low++);
  }
  return list;
}

function http_post_json(url, data) {
  var xhr = new XMLHttpRequest();
  xhr.open('POST', url, false);
  xhr.setRequestHeader('Content-Type', 'application/json; charset=UTF-8');
  xhr.send(data);
  return JSON.parse(xhr.responseText);
}

function load_tilemap_async(json_url) {
  return $.ajax({
    url: '/assets/tilemaps/' + json_url,
    dataType: 'text',
  });
}

// Functions inserted by play.html.haml.
var tilemap_url = get_level_tilemap();
var hero_gender = get_hero_gender();

// Load tilemap from file asynchronously.
var tilemap_promise = load_tilemap_async(tilemap_url);
tilemap_promise.success(function (tilemap_str) {
  // Initialize level session with Execution server
  //var response = http_post_json('http://google.com', tilemap_str);
  var tilemap_json = JSON.parse(tilemap_str);

  // tileset IDs implicitly defined as 'tileset1', 'tileset2', ...
  // Array members are name of corresponding tileset as referenced in the tilemap.
  var tileset_names = [];

  var game = new Phaser.Game(1152, 640, Phaser.AUTO, 'canvas-container',
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

    // Load hero spritesheet.
    var hero_spritesheet_path = '/assets/spritesheets/heroes/' + hero_gender + '/walk.png';
    game.load.spritesheet('hero-spritesheet', hero_spritesheet_path, 64, 64);
  }

  var world_tilemap;
  var tilelayers = [];
  var hero_sprite;

  function create() {
    game.stage.backgroundColor = '#000000';

    world_tilemap = game.add.tilemap('world-tilemap');

    for (var i = 0; i < tileset_names.length; i++) {
      var tileset_name = tileset_names[i];
      world_tilemap.addTilesetImage(tileset_name, 'tileset' + i);
    }

    var hero_start_x, hero_start_y;

    // Create layers.
    var layers_json = tilemap_json['layers'];
    for (var i = 0; i < layers_json.length; i++) {
      var layer_json = layers_json[i];
      var layer_json_type = layer_json['type'];
      if (layer_json_type === 'tilelayer') {
        var tilelayer = world_tilemap.createLayer(layer_json['name']);
        tilelayers.push(tilelayer);
      } else if (layer_json_type === 'objectgroup') {
        var layer_name = layer_json['name'];
        if (layer_name === 'ActorsLayer') {
          var layer_objs_json = layer_json['objects'];
          for (var j = 0; j < layer_objs_json.length; j++) {
            var layer_obj_json = layer_objs_json[j];
            if (layer_obj_json['type'] === 'position'
                && layer_obj_json['name'] === 'hero') {
              hero_start_x = Number(layer_obj_json['x']);
              hero_start_y = Number(layer_obj_json['y']);
            }
          }
        }
      }
    }

    hero_sprite = game.add.sprite(hero_start_x, hero_start_y, 'hero-spritesheet');
    hero_sprite.animations.add('walk-up', generate_list(0, 8), 15, true);
    hero_sprite.animations.add('walk-left', generate_list(9, 17), 15, true);
    hero_sprite.animations.add('walk-down', generate_list(18, 26), 15, true);
    hero_sprite.animations.add('walk-right', generate_list(27, 35), 15, true);
  }

  function update() {

  }

  function render() {

  }

  // Intercept click events on the submit button.
  $('input#submit_button').click(function(event) {
    var code = $('textarea#submission_code').val();
    console.log('code: ' + code);
  });
});
