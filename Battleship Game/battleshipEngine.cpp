////////////////////////////////////////////////////////////////////
//battleshipEngine drives the battleship game, containing the basic
//structure of the game and getting user input.
/////////////////////////////////////////////////////////////////
#include"playerType.h"
#include<cstdlib>
#include<iostream>
#include<time.h>
using namespace std;

int chInt(char input);
void p1print(player p1);
void p2print(player p2);

int main(){
	srand(time(NULL));
	player player1, player2;

	bool gameOver = false;
	int turn = 1;
	int row, col;
	//char inCol for column letter input by user, to be converted to int col for processing
	char inCol;

	do{
		cout << "Player 1, turn " << turn << "!\n\n";
		p1print(player1);
		cout << "Guess Column: ";

		//I intended this to give an error message if col can not be stored as a char, eg when
		//user inputs a string of chars. Stops the issue that came from this, but instead of calling
		//its own error message, it displays the "Get Row: " and shouts that error. iostream is a fucker.
		if (!(cin >> inCol)){
			cout << "Error! Column guess must be a letter between A and H\n";
			break;
		}
		else{
			col = chInt(inCol);
		}

		cout << "Guess Row: ";

		//gives an error message if input is not an int
		if(!(cin >> row)){
			cout<< "Error! Row guess must be a number between 1 and 8!\n";
			break;
		}

		player1.attack(row, col);

		p1print(player1);

		if (player1.allSunk()){
			gameOver = true;
			break;
		}

		cout << "Player 2, turn " << turn << "!\n\n";
		p2print(player2);
		cout << "Guess Column: ";

		
		if (!(cin >> inCol)){
			cout << "Error! Column guess must be a letter between A and H\n";
			break;
		}
		else{
			col = chInt(inCol);
		}

		cout << "Guess Row: ";
		if(!(cin >> row)){
			cout<< "Error! Row guess must be a number between 1 and 8!\n";
			break;
		}

		player2.attack(row, col);
		p2print(player2);
		if (player2.allSunk()){
			gameOver = true;
			break;
		}

	} while (!gameOver);
	system("pause");
	return 0;
}

//function to convert user guess for column into int for processing.
//works if user inputs char(a-h) or int(1-8). returns -1 for unexpected input,
//which will result in an "That isnt on the ocean" message when player::attack is called
int chInt(char input){
	switch (toupper(input)){
	case 'A':
	//toupper('1') returns 49
	case 49:
		return 1;
		break;
	case 'B':
	case 50:
		return 2;
		break;
	case 'C':
	case 51:
		return 3;
		break;
	case 'D':
	case 52:
		return 4;
		break;
	case 'E':
	case 53:
		return 5;
		break;
	case 'F':
	case 54:
		return 6;
		break;
	case 'G':
	case 55:
		return 7;
		break;
	case 'H':
	case 56:
		return 8;
		break;
	default:
		return -1;
	}
}

//these print functions were a quick and dirty way to attach a player
//label to the board for clarity during gameplay
void p1print(player p1){
	cout << "Player 1 Board:\n";
	p1.printBoard();
}
void p2print(player p2){
	cout << "Player 2 Board:\n";
	p2.printBoard();
}