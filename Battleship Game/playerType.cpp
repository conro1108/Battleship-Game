#include"playerType.h"
#include<iostream>
#include<iomanip>
using namespace std;

player::player(){
	intitializeBoard();
	
	//ships created in descending order so that more room is available
	//for larger ships.
	create5Blockship();
	create3BlockShip();
	create1BlockShip();
}

//initializes board to starting state
void player::intitializeBoard(){
	for (int i = 0; i < 8; i++){
		for (int j = 0; j < 8; j++){
			gameBoard[i][j] = '~';
		}
	}
}

//prints board
void player::printBoard(){
	cout << " ";
	for (char i = 'A'; i <= 'H'; i++){
		cout << setw(4) << i;
	}
	cout << endl << endl;
	int rowNum = 1;
	for (int i = 0; i < 8; i++){
		cout << rowNum;
		for (int j = 0; j < 8; j++){
			cout << setw(4) << gameBoard[i][j];
		}
		cout << endl << endl;
		rowNum++;
	}
}

//displays location of ships, for debugging/testing purposes
void player::showShips(){
	gameBoard[mineSweeper.b1[0] - 1][mineSweeper.b1[1] - 1] = '1';

	gameBoard[crusader.b1[0] - 1][crusader.b1[1] - 1] = '3';
	gameBoard[crusader.b2[0] - 1][crusader.b2[1] - 1] = '3';
	gameBoard[crusader.b3[0] - 1][crusader.b3[1] - 1] = '3';

	gameBoard[battleShip.b1[0] - 1][battleShip.b1[1] - 1] = '5';
	gameBoard[battleShip.b2[0] - 1][battleShip.b2[1] - 1] = '5';
	gameBoard[battleShip.b3[0] - 1][battleShip.b3[1] - 1] = '5';
	gameBoard[battleShip.b4[0] - 1][battleShip.b4[1] - 1] = '5';
	gameBoard[battleShip.b5[0] - 1][battleShip.b5[1] - 1] = '5';
}

//main attack function. This takes the players guess as a parameter, first 
//checks to make sure that the guess is on the board and not a spot
//that has already been guessed, if it is an unguessed spot on the 
//8x8 board, then the coordinate is passed to the attack functions for 
//each individual ship.
void player::attack(int row, int col){
	if (gameBoard[row - 1][col - 1] == 'O' || gameBoard[row - 1][col - 1] == 'X'){
		cout << "You already hit that!\n\n";
	}
	else if ((row < 1 || row > 8) || (col < 1 || col > 8)){
		cout << "Thats not even in the ocean!\n\n";
	}
	else{
		if (!attack5(row, col) && !attack3(row, col)
			&& !attack1(row, col)){
			gameBoard[row - 1][col - 1] = 'O';
			cout << "Sorry, you missed!\n\n";
		}
	}

	if (allSunk()){
		cout << "Game over! YOU WIN!!\n\n";
	}
}

//checks guess against coordinates of the battleShip. returns true
//if a target is hit
bool player::attack5(int row, int col){
	bool hit = false;

	//if a hit is recorded, that spot on the board is set as 'X'
	if (row == battleShip.b1[0] && col == battleShip.b1[1]){
		battleShip.b1hit = true;
		gameBoard[row - 1][col - 1] = 'X';
		hit = true;
	}
	if (row == battleShip.b2[0] && col == battleShip.b2[1]){
		battleShip.b2hit = true;
		gameBoard[row - 1][col - 1] = 'X';
		hit = true;
	}
	if (row == battleShip.b3[0] && col == battleShip.b3[1]){
		battleShip.b3hit = true;
		gameBoard[row - 1][col - 1] = 'X';
		hit = true;
	}
	if (row == battleShip.b4[0] && col == battleShip.b4[1]){
		battleShip.b4hit = true;
		gameBoard[row - 1][col - 1] = 'X';
		hit = true;
	}
	if (row == battleShip.b5[0] && col == battleShip.b5[1]){
		battleShip.b5hit = true;
		gameBoard[row - 1][col - 1] = 'X';
		hit = true;
	}

	//checks conditions to see if any alerts need to be output
	if (hit){
		cout << "You hit my Battleship!\n\n";
	}
	if (battleShip.isSunk()){
		cout << "You sunk my Battleship!\n\n";
	}
	return hit;
}

//checks guess against crusader
bool player::attack3(int row, int col){
	bool hit = false;
	if (row == crusader.b1[0] && col == crusader.b1[1]){
		crusader.b1hit = true;
		gameBoard[row - 1][col - 1] = 'X';
		hit = true;
	}
	if (row == crusader.b2[0] && col == crusader.b2[1]){
		crusader.b2hit = true;
		gameBoard[row - 1][col - 1] = 'X';
		hit = true;
	}
	if (row == crusader.b3[0] && col == crusader.b3[1]){
		crusader.b3hit = true;
		gameBoard[row - 1][col - 1] = 'X';
		hit = true;
	}

	if (hit){
		cout << "You hit my Crusader!\n\n";
	}
	if (crusader.isSunk()){
		cout << "You sunk my Crusader!\n\n";
	}
	return hit;
}

//checks guess against minesweeper
bool player::attack1(int row, int col){
	if (row == mineSweeper.b1[0] && col == mineSweeper.b1[1]){
		mineSweeper.b1hit = true;
		gameBoard[row - 1][col - 1] = 'X';
		cout << "You hit my Minesweeper!\n\n";
	}
	if (mineSweeper.isSunk()){
		cout << "You sunk my Minesweeper!\n\n";
	}
	return mineSweeper.b1hit;
}

void player::create1BlockShip(){
	int rowRoll;
	int colRoll;
	bool overlap;
	do{
		overlap = false;
		//assign values btwn 1-8
		rowRoll = rand() % 8 + 1;
		colRoll = rand() % 8 + 1;
		mineSweeper.b1[0] = rowRoll;
		mineSweeper.b1[1] = colRoll;
		if (overlap3(mineSweeper.b1[0], mineSweeper.b1[1]) ||
			overlap5(mineSweeper.b1[0], mineSweeper.b1[1])){
			overlap = true;
			continue;
		}
	} while (overlap);
}

void player::create3BlockShip(){
	int rowRoll;
	int colRoll;
	int vertRoll;
	bool isVertical;

	//randomly designates ship alignment as vertical or horiz
	vertRoll = rand() % 2;
	if (vertRoll){
		isVertical = true;
	}
	else{
		isVertical = false;
	}

	//instead of rolling 1-8 on both rolls, only rolls 2-7
	//for either row or column (depending on orientation)
	//to assign middle block, in order to make sure ship 
	//stays on board.

	bool overlap;
	do {
		overlap = false;
		if (isVertical){
			rowRoll = rand() % 6 + 2;
			colRoll = rand() % 8 + 1;
		}
		else{
			rowRoll = rand() % 8 + 1;
			colRoll = rand() % 6 + 2;
		}
		//middle block is assigned randomly rolled coordinate
		crusader.b2[0] = rowRoll;
		crusader.b2[1] = colRoll;
		//after every block generated, check to make sure it doesnt intersect bShip
		//if no overlap, ship stays on the board
		if (overlap5(crusader.b2[0], crusader.b2[1])){
			overlap = true;
			continue;
		}

		//if vertical, column stays same and rows above and below added
		//if horiz, row stays some and columns R and L added
		if (isVertical){
			crusader.b1[0] = rowRoll - 1;
			crusader.b1[1] = colRoll;
			if (overlap5(crusader.b1[0], crusader.b1[1])){
				overlap = true;
				continue;
			}

			crusader.b3[0] = rowRoll + 1;
			crusader.b3[1] = colRoll;
			if (overlap5(crusader.b3[0], crusader.b3[1])){
				overlap = true;
				continue;
			}
		}
		else{
			crusader.b1[0] = rowRoll;
			crusader.b1[1] = colRoll - 1;
			if (overlap5(crusader.b1[0], crusader.b1[1])){
				overlap = true;
				continue;
			}

			crusader.b3[0] = rowRoll;
			crusader.b3[1] = colRoll + 1;
			if (overlap5(crusader.b3[0], crusader.b3[1])){
				overlap = true;
				continue;
			}
		}
	} while (overlap);
}

bool player::overlap3(int row, int col){
	if (row == crusader.b1[0] && col == crusader.b1[1]){
		return true;
	}
	if (row == crusader.b2[0] && col == crusader.b2[1]){
		return true;
	}
	if (row == crusader.b3[0] && col == crusader.b3[1]){
		return true;
	}
	return false;
}

void player::create5Blockship(){
	int rowRoll;
	int colRoll;
	int vertRoll;
	bool isVertical;

	vertRoll = rand() % 2;
	if (vertRoll == 1){
		isVertical = true;
	}
	else{
		isVertical = false;
	}

	//instead of rolling 1-8 on both rolls, only rolls 3-6
	//for either row or column (depending on orientation)
	//to assign middle block, in order to make sure ship 
	//stays on board.
	if (isVertical){
		rowRoll = rand() % 4 + 3;
		colRoll = rand() % 8 + 1;
	}
	else{
		rowRoll = rand() % 8 + 1;
		colRoll = rand() % 4 + 3;
	}

	//middle block is assigned randomly rolled coordinate
	battleShip.b3[0] = rowRoll;
	battleShip.b3[1] = colRoll;

	//if vertical, column stays same and rows above and below added
	//if horiz, row stays some and columns R and L added
	if (isVertical){
		battleShip.b1[0] = rowRoll - 2;
		battleShip.b1[1] = colRoll;

		battleShip.b2[0] = rowRoll - 1;
		battleShip.b2[1] = colRoll;

		battleShip.b4[0] = rowRoll + 1;
		battleShip.b4[1] = colRoll;

		battleShip.b5[0] = rowRoll + 2;
		battleShip.b5[1] = colRoll;
	}
	else{
		battleShip.b1[0] = rowRoll;
		battleShip.b1[1] = colRoll - 2;

		battleShip.b2[0] = rowRoll;
		battleShip.b2[1] = colRoll - 1;

		battleShip.b4[0] = rowRoll;
		battleShip.b4[1] = colRoll + 1;

		battleShip.b5[0] = rowRoll;
		battleShip.b5[1] = colRoll + 2;
	}
}

//check if 
bool player::overlap5(int row, int col){
	if (row == battleShip.b1[0] && col == battleShip.b1[1]){
		return true;
	}
	if (row == battleShip.b2[0] && col == battleShip.b2[1]){
		return true;
	}
	if (row == battleShip.b3[0] && col == battleShip.b3[1]){
		return true;
	}
	if (row == battleShip.b4[0] && col == battleShip.b4[1]){
		return true;
	}
	if (row == battleShip.b5[0] && col == battleShip.b5[1]){
		return true;
	}
	return false;
}

//returns true if every ship is sunk
bool player::allSunk(){
	if (battleShip.isSunk() && crusader.isSunk() && mineSweeper.isSunk()){
		return true;
	}
	else{
		return false;
	}
}