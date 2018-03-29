var express = require('express');

var router = express.Router();

var db = require('../models/db.js');

router.get('/', function(req, res) {
    res.send('hello');
});

router.get('/users')

