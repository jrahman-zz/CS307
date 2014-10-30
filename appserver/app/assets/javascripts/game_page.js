//= require jquery
//= require jquery_ujs
//= require phaser

var game = new Phaser.Game(1152, 640, Phaser.AUTO, 'canvas-container',
  { preload: preload, create: create, update: update, render: render },
  false /* transparent */, true /* antialias */);

function preload() {

  // game.load.tilemap('sample-tilemap', '/assets/tilemaps/sample.json',
  //   null, Phaser.Tilemap.TILED_JSON);

  game.load.tilemap('sample-tilemap', null, get_level_tile_map(), Phaser.Tilemap.TILED_JSON);
  game.load.image('tiles', '/assets/spritesheets/RPGpack_sheet.png');
}

var map;
var layer_bg, layer_objs;

function create() {
  game.stage.backgroundColor = '#000000';

  map = game.add.tilemap('sample-tilemap');
  map.addTilesetImage('RPGpack_sheet', 'tiles');

  layer_bg = map.createLayer('BackgroundLayer');
  layer_objs = map.createLayer('ObjectsLayer');
}

function update() {

}

function render() {

}
