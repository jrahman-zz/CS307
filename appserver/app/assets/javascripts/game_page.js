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
var editorMarkers = [];

var savedPromptText;

// Enable popovers.
$(function() {
  $('[data-toggle="popover"]').popover();
});

function update_objective_list(objectives) {
  var activeObjective;
  $('#objective-list').html(list_from_data(objectives, function(item) {
    var html = '<div class="';
    html += (item.active ? 'active': (item.complete ? 'complete' : 'incomplete'));
    if (item.active) {
      html += ' active';
      activeObjective = item;
    }
    html += '">';
    html += item.name;
    if (item.active) {
      html += ' [active]';
    }
    html += '</div>';
    return html;
  }));

  var prompt = $('div.prompt-text');
  if (activeObjective) {
    savedPromptText = prompt.text();
    prompt.text(activeObjective.prompt).toggleClass('active', true);
    // TODO insert item.templateCode
  } else {
    prompt.text(savedPromptText).toggleClass('active', false);
  }
}

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

    update_objective_list(game_state.objectives);
  }

  function create() {
    game.stage.backgroundColor = '#000000';

    game_state.create();
  }

  function update() {

  }

  function render() {

  }

  // TODO delete this
  var index = 0;

  // Intercept click events on the submit button.
  $('#submit_button').click(function(event) {
    var code = editor.getValue();

    var response_json;
    if (index == 0) {
      response_json = {
        "classID":2,
        "levelID":1,
        "log":[
          [
            {
              "data": {
              "prompt":"Test objective prompt",
              "templateCode":"a = 4",
              "objectiveID":0
              },
              "type":"objective"
            }
          ]
        ],
        "nextLevel":-1,
        "userID":0
      };
    } else if (index == 1) {
      response_json = {
        "response": "Incorrect answer",
        "error_name": "IncorrectAnswer",
        "error_obj": null,
        "error_line_number": -1,
        "error_line_text": "",
        "error_message": "Custom error message from Don!"
      };
    } else if (index == 2) {
      response_json = {
        "classID": 2,
        "log": [[
          {
            "type": "completedobjective", 
            "data": {
              "totalobjectives": 1,
              "completedobjectives": 1
            }
          }
        ]],
        "completed": false,
        "userID": 0,
        "levelID": 1,
        "nextLevel": 2
      };
    }
    index++;

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

    function clearMarkers() {
      for (var i = 0; i < editorMarkers.length; i++) {
        editor.session.removeMarker(editorMarkers[i]);
      }
    }

    // Check for key that indicates error
    if (!response_json) {
      console.log('ERROR: null response JSON');
      return;
    }

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
        update_objective_list(game_state.objectives);

        // TODO re-enable UI
      });
    }
  });
});
