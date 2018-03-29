/* get express */
var express = require('express');
var app = express();

/* set port */
app.set('port', process.env.PORT || 8888);

/* get route for homepage */
app.get('/', function(req, res) {
	res.send('home page');
});

/* listen and wait on port */
app.listen(app.get('port'));



