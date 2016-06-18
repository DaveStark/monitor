var express = require('express');
var app = express();
var APP_PORT = 3001;

app.get('/', function (req, res) {
  res.send('Hello World!');
});

app.listen(APP_PORT, function () {
  console.log('Example app listening on port ' + APP_PORT +'!');
});
