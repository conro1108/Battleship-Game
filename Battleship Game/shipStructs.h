#ifndef ship_type
#define ship_type
//target coordinates stored in [row, col] format

//I think ships would be better off as a single class, with a vector
//containing coordinates, instead of an array for each target block
struct ship1{
	ship1(){
		b1hit = false;
	}

	//target block coordinate
	int b1[2];

	bool b1hit;
	bool isSunk(){
		return b1hit;
	}
};

struct ship3{
	ship3(){
		b1hit = false;
		b2hit = false;
		b3hit = false;
	}

	//coordinates of target blocks
	int b1[2];
	int b2[2];
	int b3[2];

	bool b1hit;
	bool b2hit;
	bool b3hit;

	bool isSunk(){
		if (b1hit == true && b2hit == true && b3hit == true){
			return true;
		}
		else{
			return false;
		}
	}
};

struct ship5{
	ship5(){
		b1hit = false;
		b2hit = false;
		b3hit = false;
		b4hit = false;
		b5hit = false;
	}

	//target block coordinates
	int b1[2];
	int b2[2];
	int b3[2];
	int b4[2];
	int b5[2];

	bool b1hit;
	bool b2hit;
	bool b3hit;
	bool b4hit;
	bool b5hit;

	bool isSunk(){
		if (b1hit == true && b2hit == true && b3hit == true
			&& b4hit == true && b5hit == true){
			return true;
		}
		else{
			return false;
		}
	}
};
#endif