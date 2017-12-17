#include <iostream>
#include <string>
//#include <cstdlib>
#include <fstream>
#include "Player.h"
#include "Place.h"
#include "Map.h"
#include "Dice.h"
#include "Gameplay.h"

using namespace std;

void clearTemp() {
	//Init file to remove temp.txt contents
	ofstream file;
	file.open("temp.txt");
	file.close();
}

void clearScreen() {
	if (system("CLS")) system("clear");
}

void printTemp() {
	ifstream file("temp.txt");
	string line;

	while(getline(file, line)) {
		cout<<line<<endl;
	}
	file.close();
}

int main(int argc, char** argv) {
	string str;
	
	clearTemp();
	
	//To read file temp
	/*ifstream file("temp.txt");
	string line;*/
	
	//Init object
	Dice dice;
	
	//Total player dari pilihan
	Gameplay sys(0);
	sys.initializeGame();
	
	//Selama total player aktif > 1
	while(sys.currentTotalPlayer > 1) {
		//Printing map
		PrintMap();
		
		//Print temp
		//printTemp();
		
		//Current player
		Player player = sys.getPlayer(sys.currentPlayerIndex);
		
		/*
			DATA PEMAIN
			Sisa Uang
			
			Petak Yang Dimiliki
			GT 1 / GT 2 / GT 4 atau TIDAK ADA
		*/
		
		sys.showPlayerStat(player);
		
		//Proses dadu
		int* res;
		
		//Jika tidak tercyduk
		if(!player.isTercyduk) {
			do {
				cout<<"\nKetik sembarang utk mengocok dadu: ";
				cin>>str;
				
				if(str.compare("/help") == 0 || str.compare("/surrender") == 0 || str.compare("/hipotik") == 0 || str.compare("/info") == 0 || str.compare("/sell") == 0) {
					sys.helper(str);
				}
			}
			while(str.compare("/help") == 0 || str.compare("/surrender") == 0 || str.compare("/hipotik") == 0 || str.compare("/info") == 0 || str.compare("/sell") == 0);
			
			res = dice.shake(sys.currentPlayerIndex, player.money);
		}
		else
			res = sys.securityProcess(&player);
		
		if(!player.isTercyduk) {
			//Proses perpindahan
			ChangeMap(player.x, player.y, ' '); //Hapus dulu tandanya
		}
		
		if(!player.isTercyduk && res[0] == res[1]) {
			sys.sameDice++;
			
			if(sys.sameDice == 3) {
				player.isTercyduk = true;
				player.currentPlaceIndex = 10;
				
				//Change player position
				res[0] = 0;
				res[1] = 0;
				sys.changePlayerPosition(res, &player);
				
				//Proses perpindahan
				ChangeMap(player.x, player.y, player.identification); //Tambah tanda player
				
				cout<<"\nAnda ditahan di pos satpam karena terlalu hoki dalam mengocok dadu\n";
				system("pause");
			}
		}
		
		if(!player.isTercyduk) {			
			//Change player position
			sys.changePlayerPosition(res, &player);
			
			//Proses perpindahan
			ChangeMap(player.x, player.y, player.identification); //Tambah tanda player
			
			//Clear screen
			clearScreen();
			
			//Printing map
			int p = player.currentPlaceIndex;
			PrintMap(sys.places.at(p).building == 1, sys.places.at(player.currentPlaceIndex));
			
			//Print temp
			printTemp();
			
			//Generate action of place
			int act = sys.generateDialog(&player);
		}
			
		//Save ke array
		sys.savePlayer(sys.currentPlayerIndex, player);
		
		//Clear screen
		clearScreen();
		
		//Kondisi dimana jika 2 mata dadu sama
		if(res[0] == res[1] && !player.isTercyduk) {
			continue;
		}
				
		//clear temp
		clearTemp();
		
		//Berpindah ke pemain berikutnya
		sys.nextPlayerTurn();
	}
	
	return 0;
}
