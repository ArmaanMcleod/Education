var faker = require('faker')

const numNames = 10;

var users = []
for (var i = 0; i < numNames; i++) {
	var randomName = faker.name.findName();
	var randomEmail = faker.internet.email();
	var info = {"name": randomName, "email": randomEmail};
	users.push(info);
}

module.exports = users;