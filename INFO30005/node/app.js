const faker = require('faker');

var priceItems = [];
for (let i = 0; i < 10; i++) {
	const product = faker.commerce.productName();
	const price = faker.commerce.price();
	priceItems.push(product +" - $" + price);
}

console.log(priceItems);