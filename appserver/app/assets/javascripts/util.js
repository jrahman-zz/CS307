// Generic utility functions.

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