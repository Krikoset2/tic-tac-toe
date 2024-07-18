let currentPlayer = 'X';
let board = ['', '', '', '', '', '', '', '', ''];

function makeMove(index) {
    if (board[index] === '' && !checkWin()) {
        board[index] = currentPlayer;
        document.getElementById(`cell-${index}`).innerText = currentPlayer;
        if (checkWin()) {
            showWinnerOnBoard(`${currentPlayer} wygral!`);
            confettiEffect();
        } else if (board.every(cell => cell !== '')) {
            showWinnerOnBoard("Reims!");
        } else {
            currentPlayer = currentPlayer === 'X' ? 'O' : 'X';
        }
    }
}

function checkWin() {
    const winningCombinations = [
        [0, 1, 2], [3, 4, 5], [6, 7, 8],
        [0, 3, 6], [1, 4, 7], [2, 5, 8],
        [0, 4, 8], [2, 4, 6]            
    ];

    return winningCombinations.some(combination => {
        return combination.every(index => board[index] === currentPlayer);
    });
}

function showWinnerOnBoard(message) {
    const winnerDisplay = document.createElement('div');
    winnerDisplay.style.position = 'absolute';
    winnerDisplay.style.top = '50%';
    winnerDisplay.style.left = '50%';
    winnerDisplay.style.transform = 'translate(-50%, -50%)';
    winnerDisplay.style.fontSize = '48px';
    winnerDisplay.style.fontWeight = 'bold';
    winnerDisplay.style.textShadow = '2px 2px 4px rgba(0,0,0,0.5)';

    message.split('').forEach(letter => {
        const span = document.createElement('span');
        span.textContent = letter;
        span.style.color = getRandomBrightColor();
        winnerDisplay.appendChild(span);
    });

    document.querySelector('.board').appendChild(winnerDisplay);

    setTimeout(() => {
        winnerDisplay.remove();
        resetBoard();
    }, 2000);
}

function getRandomBrightColor() {
    const hue = Math.floor(Math.random() * 360);
    return `hsl(${hue}, 100%, 60%)`;
}

function resetBoard() {
    board = ['', '', '', '', '', '', '', '', ''];
    currentPlayer = 'X';
    for (let i = 0; i < 9; i++) {
        const cell = document.getElementById(`cell-${i}`);
        cell.innerText = '';
    }
}

function confettiEffect() {
    confetti({
        particleCount: 200,
        spread: 100,
        origin: { y: 0.6 }
    });
}