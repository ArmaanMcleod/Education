/* get faker object */
var faker = require('faker');

const numNames = 10;

/* create fake array of users */
var users = [];
for (let i = 0; i < numNames; i++) {
    var randomName = faker.name.findName();
    var randomEmail = faker.internet.email();
    var info = {'name': randomName, 'email': randomEmail};
    users.push(info);
}

/* export users */
module.exports = users;