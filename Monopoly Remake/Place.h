#ifndef __PLACE_H_INCLUDED__
#define __PLACE_H_INCLUDED__
#include <string>
#include "Player.h"

class Place {
	public:
		Place(std::string name, std::string komplek, int ty, int p1[], int p2[], int xPos[], int yPos[]);
		std::string name;
		std::string komplek;
		int xPositions[5];
		int yPositions[5];
		
		/*
		List of Rent Prices (Array)
		Tanah, 1 Rumah, 2 Rumah, 3 Rumah, 4 Rumah, dan 1 Hotel
		*/
		int rentPrices[6];
		
		/*
		List of build prices
		Tanah, Rumah, Hotel, Hipotik
		*/
		int buildPrices[4];
		
		bool isHipotik; //if digadaikan
		bool isPurchased; //if purchased by player
		int owner; //who has this building
		
		/*
		1. Bangunan
		2. Kartu Kesempatan
		3. Kartu Dana Umum
		4. Penjara / Hanya Lewat
		5. Pajak Masuk / Keluar
		6. Parkir Bebas
		7. Tercyduk Satpam
		8. Start
		*/
		int building;
		
		/*
		0. 0 Rumah & 0 Hotel
		1. 1 Rumah
		2. 2 Rumah
		3. 3 Rumah
		4. 4 Rumah
		5. 1 Hotel
		*/
		int type;
		
	public:
		int* getPositionOf(int index);
		void buildOrUpgrade(Player* p); //tp -> 1 - 4 = x rumah, 5 = 1 hotel
		void sell();
		int getRentalPrice(vector<Place> places);
		void doBuildOrUpgrade(Player* p);
		int getPlayerOwner(vector<Player> players);
	
};

#endif
