var express = require('express');

var app = express();

app.set('port', process.env.PORT || 3000);

app.set('view engine', 'ejs');

var indexRoute = require('./routes/index.js');

app.use('/', indexRoute);

app.listen(app.get('port'));






