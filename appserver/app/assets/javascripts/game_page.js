//= require jquery
//= require bootstrap
//= require jquery_ujs
//= require ace/ace
//= require ace/worker-html
//= require phaser

//= require game_state
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

// Functions inserted by play.html.haml.
var tilemap_url = get_level_tilemap();
var hero_gender = get_hero_gender();

// Load tilemap from file asynchronously.
var tilemap_promise = ajax_request_async('/assets/tilemaps/' + tilemap_url);
tilemap_promise.success(function (tilemap_str) {
  "use strict";
  
  // Initialize level session with Execution server.
  var tilemap_json = JSON.parse(tilemap_str);

  var game = new Phaser.Game(CanvasTileWidth * TileSize, CanvasTileHeight * TileSize,
    Phaser.AUTO, 'canvas-container',
    { preload: preload, create: create, update: update, render: render },
    false /* transparent */, true /* antialias */);

  var game_state = new GameState(game, TileSize);

  function preload() {
    // Load world tilemap.
    game.load.tilemap('world-tilemap', null, tilemap_str, Phaser.Tilemap.TILED_JSON);

    game_state.load(tilemap_json);

    // Example response JSON processing.
    // TODO replace with server call and prevent submission while animating.
    game.load.onLoadComplete.addOnce(function () {
      setTimeout(function() {
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

        game_state.process_response(response_json, function() {
          console.log('Done!');
        });
      }, 1000);
    });
  }

  function create() {
    game.stage.backgroundColor = '#000000';

    game_state.create();
  }

  function update() {

  }

  function render() {

  }

  // Intercept click events on the submit button.
  $('#submit_button').click(function(event) {
    var code = editor.getValue();

    $.ajax({
        type: 'POST',
        // make sure you respect the same origin policy with this url:
        // http://en.wikipedia.org/wiki/Same_origin_policy
        url: 'http://128.211.191.198:3900/submissions/submit',
        data: { 
            'code': code
        },
        success: function(msg){
            alert('wow: ' + msg);
        }
    });
  });
});
