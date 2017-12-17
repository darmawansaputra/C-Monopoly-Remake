#ifndef __GAMEPLAY_H_INCLUDED__
#define __GAMEPLAY_H_INCLUDED__

#include <vector>
#include <string>
#include "Place.h"
#include "Player.h"
#include "Card.h"
using namespace std;

class Gameplay {
	public:
		Gameplay(int x);	
		int totalPlayer;
		int currentTotalPlayer;
		int currentPlayerIndex;
		int* playerOrder;
		int sameDice;
		vector<Player> players;
		vector<Place> places;
		vector<Card> danaUmum;
		vector<Card> kesempatan;
		
	public:
		void setPlayerOrder(int* order);
		void nextPlayerTurn();
		void initializeGame();
		void savePlayer(int index, Player player);
		void changePlayerPosition(int* res, Player* player);
		Place getPlace(int index);
		Player* getPlayer(int index);
		int generateDialog(Player* player);
		void showPlayerProfile(Player player);
		void doAction(int type, int pil, bool after, Player *p);
		int* securityProcess(Player* player);
		void showPlayerStat(Player* p);
		void helper(string s);
		void printTheWinner();
		void moneyDown();
		void playerLose(int index);
		
	private:
		void initializePlaces();
		void initializePlayers();
		void initializeMaps();
		void initializeCard();
		void doOrderPlayer();
};

#endif
