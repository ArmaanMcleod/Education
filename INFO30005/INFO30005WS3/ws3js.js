let gameState = {
  incorrectGuesses : [],
  remainingGuesses : 10,
  word: 'dragon',
  state: 'idle'
};

document.getElementById('set').onclick = function () {
	if (gameState.state != 'idle') {
		return;
	}

	for (char of gameState.word) {
		let newDiv = document.createElement('div');
		newDiv.classList.add('char');
		document.getElementById('wordTiles').appendChild(newDiv);
	}

	gameState.state = 'active';
}
 
document.getElementById('submit').onclick = function() {
	var form = document.forms[0];

	var guess = form.elements['guess'].value;

	if (validate(guess)) {
		check(guess);
	} else {
		alert('Invalid');
	}

	updateCounters();

	checkEndOfGame();

	return false;
}

function validate (guess) {
	return (guess.length === 1 && guess.match(/[a-z]/i));
}

function check (guess) {
	if (!gameState.word.includes(guess)) {
		gameState.incorrectGuesses.push(guess);
		gameState.remainingGuesses--;
		return false;
	}

	for (let i = 0; i < gameState.word.length; i++) {
		if (guess === gameState.word[i]) {
			updateWordTiles(i);
		}
	}
}

function updateWordTiles (index) { 
	document.getElementById('wordTiles').children[index].innerText = gameState.word[index];
}

function updateCounters() {
	document.getElementById('remaining').innerText = gameState.remainingGuesses;
	document.getElementById('incorrect').innerText = gameState.incorrectGuesses.join(' ');
}

function checkEndOfGame(){
//check if the player has guessed the secret word or if the game is over (no more
//remaining guesses

	if (gameState.remainingGuesses <= 0) {
		alert('You lose');
		return;
	}

	var tiles = document.getElementById('wordTiles').children;

	for (child of tiles) {
		if (child.innerText == '') {
			return;
		}
	}

	alert('You win');

	gameState.state = 'ended';

}

function reset () {  
//reset the game (set new word to be guessed, clean word tiles, incorrect 
//guesses and remaining guesses

	gameState.incorrectGuesses = [];
	gameState.remainingGuesses = 10;
	gameState.state = 'idle';

	var div = document.getElementById('div');
	while (div.firstChild) {
		div.removeChild(div.firstChild);
	}

	bt
}
