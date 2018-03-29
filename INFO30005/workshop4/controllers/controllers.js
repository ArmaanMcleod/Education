var db = require('../models/db.js');

exports.getAllUsers = function(req, res) {
	res.render('allusers', {users: db});
};

exports.getUser = function(req, res) {
	let user = db[req.params.id];
	res.render('user_template', {user: user});
};