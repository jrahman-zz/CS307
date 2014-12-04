//= require jquery
//= require bootstrap
//= require jquery_ujs
//= require ace/ace
//= require ace/worker-html
//= require phaser

//= require game_state
//= require util

var Range = ace.require('ace/range').Range;

// Configure Ace editor.
var editor = ace.edit('code-editor');
editor.setTheme('ace/theme/terminal');
editor.setFontSize(18);
editor.session.setMode('ace/mode/python');

var editorDoc = editor.session.getDocument();
// doc.insertLines(0, [ 'def test():', '  print "hallelujah"', '# comment']);

var editorMarkers = [];

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

// This is set by the session initialization request, then sent with every submission request.
var session_id = null;

// Load tilemap from file asynchronously.
var tilemap_promise = ajax_request_async('/assets/tilemaps/' + tilemap_url);
tilemap_promise.success(function (tilemap_str) {
  "use strict";

  // Initialize level session with Execution server.
  var tilemap_json = JSON.parse(tilemap_str);
 /* $.ajax({
    url: '/submissions/init',
    type: 'post',
    data: {
      level_id: 1,
      course_id: 1,
      level: tilemap_str
    }
  }).done(function(data) {
    session_id = data.sessionID;
  });*/

  var game = new Phaser.Game(CanvasTileWidth * TileSize, CanvasTileHeight * TileSize,
    Phaser.AUTO, 'canvas-container',
    { preload: preload, create: create, update: update, render: render },
    false /* transparent */, true /* antialias */);

  var game_state = new GameState(game, TileSize);

  function preload() {
    // Load world tilemap.
    game.load.tilemap('world-tilemap', null, tilemap_str, Phaser.Tilemap.TILED_JSON);

    game.stage.disableVisibilityChange = true;

    game_state.load(tilemap_json);
  }

  function create() {
    game.stage.backgroundColor = '#000000';

    game_state.create();
  }

  function update() {

  }

  function render() {

  }

  var index = 0;

  // Intercept click events on the submit button.
  $('#submit_button').click(function(event) {
    var code = editor.getValue();

    var response_json;
    if (index == 0) {
      response_json = {
        "response": "Error running code",
        "error_name": "NameError",
        "error_obj": "<something something>",
        "error_line_number": 2,
        "error_line_text": "Bad line of code",
        "error_message": "You tried to use a variable that you haven't defined yet. Check your spelling."
      };
    } else if (index == 1) {
      response_json = {
        "response": "Error running code",
        "error_name": "KeyError",
        "error_obj": "<something something>",
        "error_line_number": -1,
        "error_line_text": "",
        "error_message": "You tried to access a dictionary entry which does not exist."
      };
    } else if (index == 2) {
      response_json = {
        "classID":2,
        "levelID":1,
        "log":[
           [{"data":{"actorID":0,"position":{"x":4,"y":7}},"type":"move"}],
           [{"data":{"actorID":0,"position":{"x":4,"y":6}},"type":"move"}],
           [{"data":{"actorID":0,"position":{"x":4,"y":5}},"type":"move"}],
           [{"data":{"actorID":0,"position":{"x":4,"y":4}},"type":"move"}],
           [{"data":{"actorID":0,"position":{"x":4,"y":3}},"type":"move"}],
           [{"data":{"actorID":0,"rotation":0},"type":"rotate"}, {"data":{"actorID":0,"position":{"x":5,"y":3}},"type":"move"}],
          [{"data":{"actorID":0,"rotation":90},"type":"rotate"}, {"data":{"actorID":0,"position":{"x":5,"y":2}},"type":"move"}],
          [{"data":{"actorID":0,"position":{"x":5,"y":1}},"type":"move"}, {"data":{"actorID":0,"rotation":180},"type":"rotate"}],

           [{"data":{"actorID":1,"dialogue":"Sleeping beauty. You are like an old man sleeping for 12 hours straight! But, anyway you must be already getting super tired of typing in hero.moveUp() a million times. So I heard there were something called arguments in functions! And if you forgot what a function is it is just special code that is designed to do a set of instructions, but it conveniently lets you do it with 1 line of code! So try giving hero.moveRight() a number and see what happens!"},"type":"dialogue"}],
           [{"data":{"actorID":0,"rotation":0},"type":"rotate"}, {"data":{"actorID":0,"position":{"x":6, "y":1}},"type":"move"}],
           [{"data":{"actorID":0,"position":{"x":7, "y":1}},"type":"move"}],
           [{"data":{"actorID":0,"position":{"x":8, "y":1}},"type":"move"}],
           [{"data":{"actorID":0,"position":{"x":9, "y":1}},"type":"move"}],
           [{"data":{"actorID":2,"dialogue":"Second dialogue of inspiration~"},"type":"dialogue"}]
        ],
        "nextLevel":-1,
        "userID":0
      };
    }
    index++;

    function clearMarkers() {
      for (var i = 0; i < editorMarkers.length; i++) {
        editor.session.removeMarker(editorMarkers[i]);
      }
    }

    // Check for key that indicates error
    if ('response' in response_json) {
      var error_name = response_json['error_name'];
      var error_message = response_json['error_message'];
      var error_text = error_name + ': ' + error_message;
      var line = response_json['error_line_number'];

      // Add marker in editor.
      // This is 1-index based. line should be -1 or positive.
      if (line > 0) {
        var marker = editor.session.addMarker(new Range(line, 0, line, Number.MAX_VALUE),
            'ace_active-line', 'fullLine');
        editorMarkers.push(marker);
      } else {
        clearMarkers();
      }

      // Set div text.
      $('div.code-error').text(error_text);
    } else {
      clearMarkers();
      $('div.code-error').text('');
        
      game_state.process_response(response_json, function() {
        console.log('Done!');
      });
    }
    /*$.ajax({
        type: 'POST',
        // make sure you respect the same origin policy with this url:
        // http://en.wikipedia.org/wiki/Same_origin_policy
        url: 'http://128.211.191.198:3900/submissions/submit',
        data: {
            'code': code,
            'level_id': 1,
            'course_id': 1,
            'session_id': session_id
        },
        success: function(msg){
            alert('wow: ' + msg);
        }
    });*/
  });
});
