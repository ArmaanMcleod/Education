const button = document.getElementById('button');

const rainbow = ['red', 'orange', 'yellow', 'green', 'blue', 'indigo', 'violet'];

function change() {
	document.body.style.background = rainbow[Math.floor(Math.random() * rainbow.length)];
}

button.addEventListener('click', change);