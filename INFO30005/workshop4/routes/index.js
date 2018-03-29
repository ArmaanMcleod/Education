var express = require('express');

var router = express.Router();

var controller = require('../controllers/controllers');

router.get('/', function(req, res){
	res.send('hello');
});

router.get('/users', controller.getAllUsers);

router.get('/users/:id', controller.getUser);

module.exports = router;