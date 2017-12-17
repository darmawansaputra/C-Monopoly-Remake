#include <ctime>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <string>
#include "Dice.h"

using namespace std;

void Dice::reset() {
	sameCount = 0;
}

int* Dice::shake(int index, int money) {
	//Dua dadu
	ofstream file;
	file.open("temp.txt", ios::app);
	
	int* res = get();
	
	int sumDice = res[0] + res[1];
	cout<<"Dadu 1 ("<<res[0]<<") + dadu 2 ("<<res[1]<<") = "<<sumDice<<endl;
	file<<"Dadu 1 ("<<res[0]<<") + dadu 2 ("<<res[1]<<") = "<<sumDice<<"\n";
	
	
	file.close();
	
	return res;
}

void Dice::visualize(int num1, int num2) {

}

int* Dice::get() {
	srand((unsigned)time(NULL));
	int* res = new int[2];
	
	res[0] = rand() % 6 + 1;
	res[1] = rand() % 6 + 1;
	
	return res;
}
