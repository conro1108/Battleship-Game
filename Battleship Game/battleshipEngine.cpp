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
	char inCol;
	do{
		cout << "Player 1, turn " << turn << "!\n\n";
		p1print(player1);
		cout << "Please make your guess: column and row separated by space:  ";
		cin >> inCol >> row;
		col = chInt(inCol);
		player1.attack(row, col);
		p1print(player1);
		if (player1.allSunk()){
			gameOver = true;
			break;
		}

		cout << "Player 2, turn " << turn << "!\n\n";
		p2print(player2);
		cout << "Please make your guess: column and row separated by space:";
		cin >> inCol >> row;
		col = chInt(inCol);
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

int chInt(char input){
	switch (toupper(input)){
	case 'A':
		return 1;
		break;
	case 'B':
		return 2;
		break;
	case 'C':
		return 3;
		break;
	case 'D':
		return 4;
		break;
	case 'E':
		return 5;
		break;
	case 'F':
		return 6;
		break;
	case 'G':
		return 7;
		break;
	case 'H':
		return 8;
		break;
	default:
		cout << "error in char -> int conversion function";
		return 0;
	}
}
void p1print(player p1){
	cout << "Player 1 Board:\n";
	p1.printBoard();
}
void p2print(player p2){
	cout << "Player 2 Board:\n";
	p2.printBoard();
}