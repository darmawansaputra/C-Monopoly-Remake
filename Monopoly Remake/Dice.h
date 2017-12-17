#ifndef __DICE_H_INCLUDED__
#define __DICE_H_INCLUDED__

class Dice {
	//Attribute
	public:
		int sameCount;
		void visualize(int num1, int num2);
	
	//Method
	public:
		void reset();
		int* shake(int index, int money);
		int* get();
};

#endif
