// Generic utility functions.

function list_from_data(data, html_func) {
  var html = '<ul>';
  for (var i = 0; i < data.length; i++) {
    html += '<li>';
    html += html_func(data[i]);
    html += '</li>';
  }
  html += '</ul>';
  return html;
}

function default_for(arg, defaultVal) {
  return (typeof arg === 'undefined' ? defaultVal : arg)
}

/**
 * Generates list of numbers from [low..high].
 */
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

function ajax_request_async(request_url) {
  return $.ajax({
    url: request_url,
    dataType: 'text'
  });
}

/**
 * Good ol' distance formula.
 */
function distance_between(x1, y1, x2, y2) {
  var dx = x2 - x1;
  var dy = y2 - y1;
  return Math.sqrt(dx * dx + dy * dy);
}

/**
 * Converts the given text into an array of strings whose lengths
 * are no greater than line_chars.
 */
function segment_text(text, line_chars) {
  var lines = [];
  while (text.length > 0) {
    var last_space = null;
    var i = 0;
    while (i < text.length && i < line_chars) {
      if (text.charAt(i) == ' ') {
        last_space = i;
      }
      i++;
    }

    var split_at;
    if (i == text.length) {
      split_at = text.length;
    } else  {
      split_at = (last_space === null ? line_chars : last_space);
    }
    var line = text.substring(0, split_at);
    text = text.substring(split_at + 1);

    lines.push(line);
  }
  return lines;
}
