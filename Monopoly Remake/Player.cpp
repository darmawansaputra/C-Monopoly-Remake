#include <stdio.h>
#include <fstream>
#include "Player.h"

Player::Player(int _id, int _x, int _y, int _symbol, float _money, char _c) {
	id = _id;
	x = _x;
	y = _y;
	symbol = _symbol;
	money = _money;
	identification = _c;
	currentPlaceIndex = 0;
	totalLap = 0;
	isActive = true;
	isTercyduk = false;
	hasSecurityCard = false;
}

void Player::setPosition(int _x, int _y) {
	x = _x;
	y = _y;
}

void Player::setCurrentPlaceIndex(int plus) {
	currentPlaceIndex += plus;
	
	//Reset if over
	if(currentPlaceIndex > 39) {
		currentPlaceIndex = currentPlaceIndex - 40;
		totalLap++;
		
		if(currentPlaceIndex > 0) {
			ofstream file;
			file.open("temp.txt", ios::app);
			updateMoney(20000);
			file<<"\nAnda melewati start dan mendapatkan $20000, sisa uang $"<<money;
		}
	}
}

void Player::updateMoney(int r) {
	money += r;
}
