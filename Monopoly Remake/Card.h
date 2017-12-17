#ifndef __CARD_H_INCLUDED__
#define __CARD_H_INCLUDED__

#include <string>
#include "Player.h"
#include "Place.h"

using namespace std;

class Card {
	public:
		Card(int t, int a, string t2);
		int type; //1. Dana Umum, 2. Kesempatan
		int action; //Kode aksi dari kartu
		
		string teks;
		
	public:
		void CardAction(Player* p, vector<Place> places, int curPlayer);
		void moveAction(int index, vector<Place> places, int curPlayer, Player* p);
	
	private:
		void Kesempatan(Player* p, vector<Place> places, int curPlayer);
		void DanaUmum(Player* p, vector<Place> places, int curPlayer);
		void repairAction(int hRmh, int hHtl, vector<Place> places, Player* p);
};

#endif
