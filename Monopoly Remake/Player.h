#ifndef __PLAYER_H_INCLUDED__
#define __PLAYER_H_INCLUDED__

#include <vector>
//#include <string>
using namespace std;

class Player {
	public:
		Player(int id, int x, int y, int symbol, float money, char c);
		bool isActive;
		bool isTercyduk;
		bool hasSecurityCard;
		int id, x, y, symbol;
		int money;
		char identification;
		int currentPlaceIndex;
		int totalLap;
		//vector<string> myPlaces;
		vector<int> idPlaces;
	
	public:
		void setPosition(int x, int y);
		void setCurrentPlaceIndex(int plus);
		void updateMoney(int r);
};

#endif
