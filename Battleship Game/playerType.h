#ifndef p_type
#define p_type
#include"shipStructs.h"
class player{
public:
	player();
	void intitializeBoard();
	void printBoard();
	void showShips();

	void attack(int row, int col);
	bool attack5(int row, int col);
	bool attack3(int row, int col);
	bool attack1(int row, int col);

	void create1BlockShip();
	void create3BlockShip();
	void create5Blockship(); 

	bool overlap5(int row, int col);
	bool overlap3(int row, int col);
	bool allSunk();

private:
	//named ships after pieces in original board game
	ship1 mineSweeper;

	ship3 crusader;

	ship5 battleShip;

	char gameBoard[8][8];
};
#endif