#include <iostream>
#include <fstream>
#include <algorithm>
#include <ctime>
#include <cstdlib>
#include <sstream>
#include <string>
#include "Gameplay.h"
#include "Map.h"
#include "Card.h"
#include "Response.h"
#include "Helper.h"
#include "Dice.h"

using namespace std;

Gameplay::Gameplay(int x) {
	totalPlayer = x;
	currentTotalPlayer = x;
	//playerOrder = new int[x];
	currentPlayerIndex = 0;
	sameDice = 0;
}

void Gameplay::setPlayerOrder(int* order) {
	playerOrder = order;
}

void Gameplay::nextPlayerTurn() {
	sameDice = 0;
	
	//Switch to next
	
	do {
		currentPlayerIndex++;
		if(currentPlayerIndex > totalPlayer - 1)
			currentPlayerIndex = 0; //Reset
	}
	while(!players.at(currentPlayerIndex).isActive);
}

void Gameplay::changePlayerPosition(int* res, Player* player) {
	player->setCurrentPlaceIndex(res[0] + res[1]);
	int* resPos = getPlace(player->currentPlaceIndex).getPositionOf(currentPlayerIndex);
	player->setPosition(resPos[0], resPos[1]);
		
	delete[] res;
	delete[] resPos;
}

void Gameplay::initializeGame() {
	initializePlayers();
	initializePlaces();
	initializeMaps();
	initializeCard();
}

void Gameplay::doOrderPlayer() {
	ShowMenu();
	cout<<"\nSELAMAT DATANG DI MONOPOLY, h3h3 ^_^\n";
	
	while(true) {
		cout<<"Masukkan jumlah pemaian yang akan bermain (2 - 5): ";
		cin>>totalPlayer;
		
		if(!cin.good()) {
			totalPlayer = 0;
		}
		
		if(totalPlayer > 1 && totalPlayer < 6)
			break;
		
		cout<<"\nMaaf inputan jumlah anda tidak valid ^_^\n";
		cin.clear();
		cin.ignore(INT_MAX,'\n');
	}
	
	currentTotalPlayer = totalPlayer;
	
	cout<<endl;
	
	string chr = "";
	int iden[] = {176, 177, 178, 219, 240};
	for(int i = 0; i < totalPlayer; i++) {
		cout<<"Player "<<i + 1<<" = "<<chr<<char(iden[i])<<endl;
		chr.append(" ");
	}
	
	cout<<"\nSELAMAT BERMAIN!!! h3h3 ^_^\n\n";
	
	/*cout<<"\nPROSES PENENTUAN URUTAN BERMAIN: \n";
	string temp;
	Dice dice;
	
	int* res;
	int ttl[totalPlayer];
	int pl[totalPlayer];
	
	for(int i = 0; i < totalPlayer; i++) {
		pl[i] = i;
		cout<<"Player "<<i + 1<<" silahkan mengetik sembarang untuk mengocok dadu: ";
		cin>>temp;
		
		res = dice.get();
		ttl[i] = res[0] + res[1];
		cout<<"("<<res[0]<<") + ("<<res[1]<<") = "<<ttl[i]<<"\n\n";
	}
	
	delete[] res;
	
	int tm;
	//diurutkan dlu
	for(int i = 0; i < totalPlayer; i++) {
		for(int j = i + 1; j < totalPlayer; j++) {
			if(ttl[j] > ttl[i]) {
				tm = ttl[i];
				ttl[i] = ttl[j];
				ttl[j] = tm;
				
				tm = pl[i];
				pl[i] = pl[j];
				pl[j] = tm;
			}
		}
	}
	
	//cout<<ttl[0]<<ttl[1]<<ttl[2]<<ttl[3];
	
	//Proses pengecekan dan input lg jika ada yg sama
	
	
	int same = 0;
	for(int i = 0; i < totalPlayer;) {
		for(int j = i + 1; j < totalPlayer; j++)
			if(ttl[i] == ttl[j])
				same++;
		
		if(same > 0) {
			int tmp[5] = {0, 0, 0, 0, 0};
			
			cout<<"SILAHKAN KOCOK DADU LAGI UNTUK MENENTUKAN URUTAN KE "<<i + 1<<" - "<<i + 1 + same<<": \n";
			
			for(int k = i; k <= i + same; k++) {
				cout<<"Player "<<k + 1<<" silahkan mengetik sembarang untuk mengocok dadu: ";
				cin>>temp;
				
				res = dice.get();
				tmp[k] = res[0] + res[1];
				cout<<"("<<res[0]<<") + ("<<res[1]<<") = "<<tmp[k]<<"\n\n";
			}
			
			//Diurutkan
			for(int m = i; m <= i + same; m++) {
				for(int n = m + 1; n <= i + same; n++) {
					if(tmp[n] > tmp[m]) {
						tm = tmp[m];
						tmp[m] = tmp[n];
						tmp[n] = tm;
						
						tm = pl[m];
						pl[m] = pl[n];
						pl[n] = tm;
					}
				}
			}
			
			cout<<ttl[i];
			
			for(int m = i + 1; m <= i + same; m++)
				if(tmp[i] != tmp[m])
					same--;
			
			if(same == 0)
				i++;
		}
		else
			i++;
			
		//Reset
		same = 0;
	}
	
	cout<<"JADI URUTANNYA: \n";
	for(int i = 0; i < totalPlayer; i++) {
		cout<<i + 1<<". Player "<<pl[i] + 1<<endl;
	}*/
	
	system("pause");
	system("cls");
}

void Gameplay::initializePlayers() {
	doOrderPlayer();
	
	//Init player
	Player p1(1, 106, 42, 176, 200000, ':');
	Player p2(2, 107, 42, 177, 200000, '*');
	Player p3(3, 108, 42, 178, 200000, '@');
	Player p4(4, 109, 42, 219, 200000, '!');
	Player p5(5, 110, 42, 240, 200000, '~');
	
	//List of players
	if(totalPlayer > 0)
		players.push_back(p1);
		
	if(totalPlayer > 1)
		players.push_back(p2);
		
	if(totalPlayer > 2)
		players.push_back(p3);
		
	if(totalPlayer > 3)
		players.push_back(p4);
		
	if(totalPlayer > 4)
		players.push_back(p5);
}

void Gameplay::initializePlaces() {
	string names[40] = {"START", "GT301", "DANA UMUM", "GT302", "PAJAK MASUK", "R P SAF", "GT303", "KESEMPATAN", "GT304", "GT305", "POS SATPAM", "JJ101", "RUANG BAAK", "JJ102", "JJ103", "HALL D4", "JJ104", "DANA UMUM", "JJ105", "JJ106", "BEBAS PARKIR", "HH101", "KESEMPATAN", "HH102", "HH103", "LAP MER", "HH104", "HH105",  "RUANG GELAP", "HH106", "TERCYDUK SATPAM", "PS LT 1", "PS LT 2", "DANA UMUM", "PS LT 3", "AN NAHL", "KESEMPATAN", "PS LT 4", "PAJAK KELUAR", "PS LT 5"};
	string komplek[40] = {"", "GT", "", "GT", "", "GT", "GT", "", "GT", "GT", "", "JJ", "JJ", "JJ", "JJ", "JJ", "JJ", "", "JJ", "JJ", "", "HH", "", "HH", "HH", "HH", "HH", "HH", "HH", "HH", "", "PS", "PS", "", "PS", "PS", "", "PS", "", "PS"};
	int buildingType[40] = {8, 1, 3, 1, 5, 1, 1, 2, 1, 1, 4, 1, 1, 1, 1, 1, 1, 3, 1, 1, 6, 1, 2, 1, 1, 1, 1, 1, 1, 1, 7, 1, 1, 3, 1, 1, 2, 1, 5, 1};
	
	int xPositions[40][5] = {
		{106, 107, 108, 109, 110}, {95, 96, 97, 98, 99}, {85, 86, 87, 88, 89}, {75, 76, 77, 78, 79},
		{65, 66, 67, 68, 69}, {55, 56, 57, 58, 59}, {45, 46, 47, 48, 49}, {35, 36, 37, 38, 39},
		{25, 26, 27, 28, 29}, {15, 16, 17, 18, 19}, {4, 5, 6, 7, 8}, {4, 5, 6, 7, 8}, {4, 5, 6, 7, 8},
		{4, 5, 6, 7, 8}, {4, 5, 6, 7, 8}, {4, 5, 6, 7, 8}, {4, 5, 6, 7, 8}, {4, 5, 6, 7, 8}, {4, 5, 6, 7, 8},
		{4, 5, 6, 7, 8}, {4, 5, 6, 7, 8}, {15, 16, 17, 18, 19}, {25, 26, 27, 28, 29}, {35, 36, 37, 38, 39},
		{45, 46, 47, 48, 49}, {55, 56, 57, 58, 59}, {65, 66, 67, 68, 69}, {75, 76, 77, 78, 79}, {85, 86, 87, 88, 89},
		{95, 96, 97, 98, 99}, {106, 107, 108, 109, 110}, {106, 107, 108, 109, 110}, {106, 107, 108, 109, 110},
		{106, 107, 108, 109, 110}, {106, 107, 108, 109, 110}, {106, 107, 108, 109, 110}, {106, 107, 108, 109, 110},
		{106, 107, 108, 109, 110}, {106, 107, 108, 109, 110}, {106, 107, 108, 109, 110}
	};
	
	int yPositions[40][5] = {
		{42, 42, 42, 42, 42}, {42, 42, 42, 42, 42}, {42, 42, 42, 42, 42}, {42, 42, 42, 42, 42},
		{42, 42, 42, 42, 42}, {42, 42, 42, 42, 42}, {42, 42, 42, 42, 42}, {42, 42, 42, 42, 42},
		{42, 42, 42, 42, 42}, {42, 42, 42, 42, 42}, {42, 42, 42, 42, 42}, {38, 38, 38, 38, 38},
		{34, 34, 34, 34, 34}, {30, 30, 30, 30, 30}, {26, 26, 26, 26, 26}, {22, 22, 22, 22, 22},
		{18, 18, 18, 18, 18}, {14, 14, 14, 14, 14}, {10, 10, 10, 10, 10}, {6, 6, 6, 6, 6},
		{2, 2, 2, 2, 2}, {2, 2, 2, 2, 2}, {2, 2, 2, 2, 2}, {2, 2, 2, 2, 2}, {2, 2, 2, 2, 2},
		{2, 2, 2, 2, 2}, {2, 2, 2, 2, 2}, {2, 2, 2, 2, 2}, {2, 2, 2, 2, 2}, {2, 2, 2, 2, 2}, {2, 2, 2, 2, 2},
		{6, 6, 6, 6, 6}, {10, 10, 10, 10, 10}, {14, 14, 14, 14, 14}, {18, 18, 18, 18, 18}, {22, 22, 22, 22, 22},
		{26, 26, 26, 26, 26}, {30, 30, 30, 30, 30}, {34, 34, 34, 34, 34}, {38, 38, 38, 38, 38}
	};
	
	int rPrices[40][6] = {
		{0, 0, 0, 0, 0, 0}, //Start
		{600, 3000, 8000, 16000, 25000, 40000}, //GT301
		{0, 0, 0, 0, 0, 0}, //DANA UMUM
		{600, 4000, 10000, 18000, 30000, 50000}, //GT302
		{0, 0, 0, 0, 0, 0}, //PAJAK MASUK
		{2000, 7000, 14000, 22000, 35000, 55000}, //R P SAF
		{1000, 6000, 15000, 24000, 40000, 60000}, //GT303
		{0, 0, 0, 0, 0, 0}, //KESEMPATAN
		{1000, 7000, 17000, 27000, 45000, 65000}, //GT304
		{1200, 8000, 19000, 30000, 50000, 70000}, //GT305
		{0, 0, 0, 0, 0, 0}, //POS SATPAM
		{1400, 8000, 21000, 36000, 60000, 85000}, //JJ101
		{1500, 9000, 23000, 39000, 65000, 90000}, //RUANG BAAK
		{1400, 10000, 25000, 42000, 70000, 95000}, //JJ102
		{1600, 11000, 27000, 45000, 75000, 100000}, //JJ103
		{2000, 13000, 29000, 51000, 75000, 110000}, //HALL D4
		{1800, 11000, 29000, 48000, 80000, 120000}, //JJ104
		{0, 0, 0, 0, 0, 0}, //DANA UMUM
		{1800, 13000, 33000, 54000, 90000, 125000}, //JJ105
		{2000, 15000, 37000, 60000, 100000, 130000}, //JJ106
		{0, 0, 0, 0, 0, 0}, //BEBAS PARKIR
		{2200, 15000, 38000, 63000, 105000, 150000}, //HH101
		{0, 0, 0, 0, 0, 0}, //KESEMPATAN
		{2200, 17000, 42000, 69000, 115000, 157000}, //HH102
		{2400, 19000, 46000, 75000, 125000, 165000}, //HH103
		{2000, 20000, 50000, 80000, 130000, 180000}, //LAP MER
		{2600, 19000, 49000, 81000, 135000, 172000}, //HH104
		{2600, 20000, 51000, 84000, 140000, 180000}, //HH105
		{1500, 21000, 53000, 87000, 145000, 187000}, //RUANG GELAP
		{2800, 22000, 55000, 90000, 150000, 195000}, //HH106
		{0, 0, 0, 0, 0, 0}, //TERCYDUK SATPAM
		{3000, 22000, 57000, 93000, 155000, 195000}, //PS LT 1
		{3000, 24000, 61000, 99000, 165000, 210000}, //PS LT 2
		{0, 0, 0, 0, 0, 0}, //DANA UMUM
		{3200, 26000, 65000, 105000, 175000, 225000}, //PS LT 3
		{2000, 26000, 67000, 107000, 170000, 230000}, //AN NAHL
		{0, 0, 0, 0, 0, 0}, //KESEMPATAN
		{3500, 27000, 69000, 111000, 185000, 240000}, //PS LT 4
		{0, 0, 0, 0, 0, 0}, //PAJAK KELUAR
		{4000, 30000, 75000, 120000, 200000, 255000} //PS LT 5
	};
	
	int bPrices[40][4] = {
		//Harga tanah, harga rumah, harga hotel, harga hipotik
		{0, 0, 0, 0}, //START
		{6000, 4000, 25000, 20000}, //GT301
		{0, 0, 0, 0}, //DANA UMUM
		{6000, 5000, 30000, 20000}, //GT302
		{0, 0, 0, 0}, //PAJAK MASUK
		{20000, 7500, 40000, 20000}, //R P SAF
		{10000, 8000, 35000, 20000}, //GT303
		{0, 0, 0, 0}, //KESEMPATAN
		{10000, 9000, 40000, 20000}, //GT304
		{12000, 10000, 45000, 20000}, //GT305
		{0, 0, 0, 0}, //POS SATPAM
		{14000, 12000, 58000, 30000}, //JJ101
		{15000, 13000, 62000, 30000}, //RUANG BAAK
		{14000, 14000, 66000, 30000}, //JJ102
		{16000, 15000, 60000, 30000}, //JJ103
		{20000, 17000, 70000, 30000}, //HALL D4
		{18000, 16000, 80000, 30000}, //JJ104
		{0, 0, 0, 0}, //DANA UMUM
		{18000, 18000, 85000, 30000}, //JJ105
		{20000, 20000, 90000, 30000}, //JJ106
		{0, 0, 0, 0}, //BEBAS PARKIR
		{22000, 21000, 100000, 40000}, //HH101
		{0, 0, 0, 0}, //KESEMPATAN		
		{22000, 23000, 105000, 40000}, //HH102
		{24000, 25000, 110000, 40000}, //HH103
		{20000, 27000, 120000, 40000}, //LAP MER
		{26000, 27000, 115000, 40000}, //HH104
		{26000, 28000, 120000, 40000}, //HH105
		{15000, 29000, 125000, 40000}, //RUANG GELAP
		{28000, 30000, 130000, 40000}, //HH106
		{0, 0, 0, 0}, //TERCYDUK SATPAM
		{30000, 31000, 130000, 50000}, //PS LT 1
		{30000, 33000, 140000, 50000}, //PS LT 2
		{0, 0, 0, 0}, //DANA UMUM
		{32000, 35000, 150000, 50000}, //PS LT 3
		{20000, 37000, 160000, 50000}, //AN NAHL
		{0, 0, 0, 0}, //KESEMPATAN
		{35000, 37000, 160000, 50000}, //PS LT 4
		{0, 0, 0, 0}, //PAJAK KELUAR
		{40000, 40000, 170000, 50000} //PS LT 5
	};
	
	for(int i = 0; i < 40; i++) {
		Place p(names[i], komplek[i], buildingType[i], rPrices[i], bPrices[i], xPositions[i], yPositions[i]);
		places.push_back(p);
	}
}

void Gameplay::initializeMaps() {
	if(totalPlayer < 5)
		ChangeMap(110, 42, ' ');
	if(totalPlayer < 4)	
		ChangeMap(109, 42, ' ');
	if(totalPlayer < 3)
		ChangeMap(108, 42, ' ');
	if(totalPlayer < 2)
		ChangeMap(107, 42, ' ');
	if(totalPlayer < 1)
		ChangeMap(106, 42, ' ');
}

// random generator function:
int myrandom (int i) { return rand()%i;}

void Gameplay::initializeCard() {
	string du[11] = {"Maju sampai START", "Bebas dari pos satpam atau boleh dijual", "Bayar perbaikan rumah, $4.500 per rumah $11.000 per hotel", "Bayar kartu $10.000 atau ambil Kesempatan", "Karena kesalahan Bank anda terima $20.000", "Nemu uang $5.000 di kantin", "Bayar uang pulsa $10.000", "Dapat beasiswa $15.000", "Bayar Dokter $5.000", "Bayar uang kuliah $15.000", "Selamat anda ulang tahun dapat $5.000 tiap pemain"};
	string ks[11] = {"Maju sampai START", "Bebas dari pos satpam atau boleh dijual", "Bayar perbaikan rumah, $2.500 per rumah $10.000 per hotel", "Mabuk di muka umum denda $1.500", "Melanggar lalu lintas denda $5.000", "Mundur tiga petak", "Maju sampai PS LT 5", "Maju sampai JJ104, bila melalui START dapat $20.000", "Kembali menuju GT101", "Nemu uang $10.000 di kantin", "Menang PKM AI/GT dapat $7.500"};
	
	srand(unsigned(time(0)));
	
	for(int i = 0; i < 11; i++) {
		Card c(1, i + 1, du[i]);
		danaUmum.push_back(c);
		
		Card d(2, i + 1, ks[i]);
		kesempatan.push_back(d);
	}
	
	//Proses mengacak kartu kesempatan dan dana umum
	random_shuffle(danaUmum.begin(), danaUmum.end(), myrandom);
	random_shuffle(kesempatan.begin(), kesempatan.end(), myrandom);
}

void Gameplay::savePlayer(int index, Player player) {
	players.at(index) = player;
}

Place Gameplay::getPlace(int index) {
	return places.at(index);
}

Player* Gameplay::getPlayer(int index) {
	return &players.at(index);
}

void Gameplay::showPlayerProfile(Player player) {
	
}

int Gameplay::generateDialog(Player* player) {
	string dialog = "";
	stringstream ss;
	//player->currentPlaceIndex = 1;
	
	int id = player->currentPlaceIndex;
	//id = 1;
	Place* p = &places.at(id);
	int max = 0;
	
	int act; //id action depends of user
	
	int pilihan;
	
	//Jika kesempatan
	if(p->building == 2) {
		dialog = "1. Ambil kartu kesempatan";
		max = 1;
		act = 1;
	}
	//Jika dana umum
	else if(p->building == 3) {
		dialog = "1. Ambil kartu dana umum";
		max = 1;
		act = 2;
	}
	//Jika bebas parkir
	else if(p->building == 6) {
		dialog = "1. Pilih tempat\n2. Tidak memilih sama sekali";
		max = 2;
		act = 3;
	}
	//Jika pos satpam
	else if(p->building == 4) {
		dialog = "1. Akhiri giliran";
		max = 1;
		act = 4;
	}
	//Jika tercyduk
	else if(p->building == 7) {
		ChangeMap(player->x, player->y, ' '); //Hapus dulu tandanya
		
		player->isTercyduk = true;
		player->currentPlaceIndex = 10;
		dialog = "Anda ditahan di pos satpam karena tidak membayar UKT\n1. Akhiri giliran";
		max = 1;
		act = 4;
		
		int* resPos = getPlace(player->currentPlaceIndex).getPositionOf(currentPlayerIndex);
		player->setPosition(resPos[0], resPos[1]);
		
		ChangeMap(player->x, player->y, player->identification); //Tambah tanda player
	
		delete[] resPos;
	}
	//Jika start
	else if(p->building == 8) {
		dialog = "1. Akhiri giliran";
		max = 1;
		act = 4;
	}
	//Jika di kotak pajak
	else if(p->building == 5) {
		dialog = "1. Akhiri giliran";
		max = 1;
		act = 5;
	}
	//Selain itu semua (petak)
	else {
		int n = 1;
		
		//Jika total lap > 0
		if(player->totalLap > 0) {
			//Jika tanah kosong
			if(!p->isPurchased) {
				dialog = "1. Beli bangunan\n";		
				max = 2;
				act = 6;
				n++;
			}
			
			//Jika berada di tanah yang digadaikan
			else if(p->isHipotik) {
				//Jika tanah sendiri
				if(p->owner == player->id) {
					ss<<"1. Bayar uang hipotik ($"<<p->buildPrices[3] + 0.1 * p->buildPrices[3]<<")\n";
				}
				
				//Jika punya orang lain
				else {
					ss<<"1. Akuisisi rumah yang digadaikan ($"<<p->buildPrices[3] + 0.2 * p->buildPrices[3]<<")\n";
				}
				
				max = 2;
				act = 9;
				n++;
			}
			
			//Jika tanah milik kita
			else if(p->isPurchased && p->owner == player->id) {
				dialog = "1. Tingkatkan bangunan\n";
				max = 2;
				act = 7;
				n++;
			}
				
			//Jika tanah milik orang lain
			else {
				int harga = p->getRentalPrice(places);
				player->updateMoney(-harga);
				
				int pw = p->getPlayerOwner(players);
				players.at(pw).updateMoney(harga);
				
				Response::get(1, harga, player->money);
				cout<<"\nPemain "<<pw + 1<<" mendapatkan $"<<harga<<" sisa uang $"<<players.at(pw).money;
				//dialog = "1. Akhiri giliran";
				max = 1;
				act = 8;
			}	
		}
		else {
			max = 1;
			act = 99;
		}
		
		ss<<n<<". Akhiri giliran";
		dialog.append(ss.str());
	}
	
	doAction(act, pilihan, false, player);
	
	cout<<"\nAnda berada di "<<p->name<<":\n"<<dialog;
	
	pilihan = Helper::inputValidate(max, "Masukkan pilihan aksi: ");
	
	doAction(act, pilihan, true, player);
}

/*
	Type of action
	1. kesempatan = after
	2. dana umum = after
	3. bebas parkir = after
	4. pos satpam (hanya lewat), masuk pos satpam, kotak start = ?
	5. pajak = before
	6. tanah kosong = after
	7. tanah sendiri = after
	8. tanah orang lain = before
	
	after
		true = after user input
*/

void Gameplay::doAction(int type, int pil, bool after, Player* pl) {
	int id = pl->currentPlaceIndex;
	Place* p = &places.at(id);
	
	if(after) {
		//Kesempatan
		if(type == 1) {
			//Ambil kartu yg paling atas
			Card c = kesempatan.at(0);
			c.CardAction(pl, places, currentPlayerIndex);
			
			system("pause");
			
			//Generate dialog lagi
			if(c.action == 6 || c.action == 7 || c.action == 8 || c.action == 9) {
				system("cls");
				PrintMap(places.at(pl->currentPlaceIndex).building == 1, places.at(pl->currentPlaceIndex));
				showPlayerStat(pl);
				
				generateDialog(pl);
			}
			
			//Hapus kartunya
			kesempatan.erase(kesempatan.begin());
			
			//Taruh di bawah sendiri
			kesempatan.push_back(c);
		}
		//Dana umum
		else if(type == 2) {
			//Ambil kartu yg paling atas
			Card c = danaUmum.at(0);
			c.CardAction(pl, places, currentPlayerIndex);
			
			//Hapus kartunya
			danaUmum.erase(danaUmum.begin());
			
			//Taruh di bawah sendiri
			danaUmum.push_back(c);
			
			//Jika ultah
			if(c.action == 11) {
				int total = 5000 * (currentTotalPlayer - 1);
				pl->updateMoney(total);
				cout<<"Anda mendapatkan $"<<total<<" dari "<<currentTotalPlayer - 1<<" pemain, sisa uang anda $"<<pl->money<<endl;
				
				for(int i = 0; i < currentTotalPlayer; i++) {
					if(players.at(i).id != pl->id) {
						players.at(i).updateMoney(-5000);
						cout<<"Pemain "<<i + 1<<" uangnya berkurang $5000, sisa uangnya $"<<players.at(i).money<<endl;
					}
				}
			}
			
			//Jika kesempatan atau bayar
			else if(c.action == 4) {
				cout<<"1. Ambil kartu kesempatan\n2. Bayar $10.000";
				int pil = Helper::inputValidate(2, "Masukkan pilihan: ");
				
				if(pil == 1) {
					doAction(1, 1, true, pl);
				}
				else {
					pl->updateMoney(-10000);
					cout<<"\nAnda membayar $10000, sisa uang anda $"<<pl->money<<endl;
					system("pause");
				}
			}
			
			if(c.action != 4)
				system("pause");
		}
		//Build or upgrade
		else if((type == 6 || type == 7) && pil == 1) {
			p->buildOrUpgrade(pl);
		}
		//Proses bayar hipotik atau akuisisi
		else if(type == 9 && pil == 1) {
			int h = 0;
			//Bayar hipotik
			if(pl->id == p->owner) {
				h = p->buildPrices[3] + 0.1 * p->buildPrices[3];
			}
			
			//Akuisisi
			else {
				h = p->buildPrices[3] + 0.2 * p->buildPrices[3];
			}
			
			if(pl->money < h) {
				cout<<"Maaf tidak dapat melakukan aksi tersebut";
				return;
			}
			
			if(pl->id == p->owner) {
				p->isHipotik = false;
				pl->updateMoney(-h);
				
				cout<<"Proses pembayaran pegadaian berhasil, sisa uang $"<<pl->money<<endl;
			}
			else {
				p->isHipotik = false;
				pl->updateMoney(-h);
				p->owner = pl->id;
				
				cout<<"Proses pembayaran akuisisi berhasil, sisa uang $"<<pl->money<<endl;
			}
			
			system("pause");
		}
		//Parkir bebas
		else if(type == 3 && pil == 1) {
			cout<<"\nDaftar tujuan parkir:\n";
			for(int i = 0; i < places.size(); i++) {
				cout<<i + 1<<". "<<places.at(i).name<<endl;
			}
			
			CH:
			int pil = Helper::inputValidate(places.size() + 1, "Masukkan tujuan parkir: ");
			if(pil == 21) {
				cout<<"\nAnda tidak boleh memilih parkir di parkir bebas lagi";
				goto CH;
			}
			else {
				if(pl->currentPlaceIndex > pil - 1)
					pl->updateMoney(20000);
					
				Card c = kesempatan.at(0);
				c.moveAction(pil - 1, places, currentPlayerIndex, pl);
				system("cls");
				PrintMap(places.at(pl->currentPlaceIndex).building == 1, places.at(pl->currentPlaceIndex));
				showPlayerStat(pl);
				
				generateDialog(pl);
			}
		}
	}
	else {
		if(type == 5) {
			int pajak = id == 4 ? 20000 : 10000;
		
			//Update player money
			pl->updateMoney(-pajak);
			
			Response::get(6, pajak, pl->money);
		}
		else if(type == 8) {
			Response::get(1);
		}
	}
		
	
	/*else if(type == 4) {
		
	}*/	
}

int* Gameplay::securityProcess(Player* player) {
	int pil;
	Dice dice;
	string ss;
	int* res = new int[2];
	
	cout<<"\nSelamat datang di pos satpam, apa yang ingin anda lakukan: \n1. Kocok dadu untuk mendapatkan mata dadu yang sama\n2. Gunakan kartu keluar pos satpam";
	
	CHOOSE:
	pil = Helper::inputValidate(2, "Masukkan pilihan: ");
	
	if(pil == 1) {
		cout<<"\nKetik sembarang untuk mengocok dadu: ";
		cin>>ss;
		
		res = dice.get();
		cout<<"Dadu 1 ("<<res[0]<<") + dadu 2 ("<<res[1]<<") = "<<res[0] + res[1]<<endl;
		
		if(res[0] == res[1]) {
			cout<<"\nSelamat anda berhasil keluar dari pos satpam";
			player->isTercyduk = false;
			return res;
		}
		else {
			cout<<"\nAnda gagal mendapatkan mata dadu yang sama\n";
		}
	}
	else {
		if(!player->hasSecurityCard) {
			cout<<"\nMaaf anda tidak memiliki kartu bebas satpam";
			goto CHOOSE;
		}
		else {
			cout<<"\nAnda berhasil keluar pos satpam dengan menggunakan kartu bebas satpam\n";
			player->isTercyduk = false;
			
			system("pause");
			return dice.shake(currentPlayerIndex, player->money);
		}
	}
	
	system("pause");
	return res;
}

void Gameplay::showPlayerStat(Player* p) {
	ofstream file;
	file.open("temp.txt", ios::app);
	
	cout<<"\nGILIRAN PEMAIN KE: "<<currentPlayerIndex + 1<<"\n";
	file<<"\nGILIRAN PEMAIN KE: "<<currentPlayerIndex + 1<<"\n";
	
	//Profile
	cout<<"SISA UANG PEMAIN: $"<<p->money<<"\n";
	file<<"SISA UANG PEMAIN: $"<<p->money<<"\n";
	
	cout<<"PETAK YANG DIMILIKI:\n";
	file<<"PETAK YANG DIMILIKI:\n";
	
	for(int i = 0; i < p->idPlaces.size(); i++) {
		cout<<places.at(p->idPlaces.at(i)).name;
		file<<places.at(p->idPlaces.at(i)).name;
		
		if(i < p->idPlaces.size() - 1) {
			cout<<" // ";
			file<<" // ";
		}
		else {
			cout<<endl;
			file<<endl;
		}
	}	
			
	file.close();
}

void Gameplay::helper(string s) {
	Player* p = &players.at(currentPlayerIndex);
	
	if(s.compare("/help") == 0) {
		cout<<"/help \t\t= Membuka daftar perintah\n/surrender \t= Menyerah dari permainan\n/info \t\t= Melihat informasi petak yang dimiliki\n/sell \t\t= Menjual petak yang dimiliki\n/hipotik \t= Menggadaikan petak yang dimiliki\n/pay \t\t= Membayar petak yang digadaikan\n";
	}
	else if(s.compare("/surrender") == 0) {
		char res;
		
		cout<<"Apakah anda yakin ingin menyerah (Y/N)? : ";
		cin>>res;
		
		if(res == 'Y') {
			playerLose(currentPlayerIndex);
			cout<<"\nPlayer "<<currentPlayerIndex + 1<<" telah menyerah dari permaianan\n";
			system("pause");
		}
	}
	else if(s.compare("/info") == 0 || s.compare("/sell") == 0 || s.compare("/hipotik") == 0 || s.compare("/pay") == 0) {
		int n = 1;
		for(int i = 0; i < p->idPlaces.size(); i++) {
			int t = places.at(p->idPlaces.at(i)).type;
			bool hip = places.at(p->idPlaces.at(i)).isHipotik;
			
			if(s.compare("/info") == 0 || (s.compare("/sell") == 0 && !hip) || (s.compare("/hipotik") == 0 && !hip) || (s.compare("/pay") == 0 && hip))
				cout<<n<<". "<<places.at(p->idPlaces.at(i)).name;
			else
				continue;
			
			cout<<" (";
			if(t < 1)
				cout<<"Hanya tanah";
			else if(t > 1 && t < 6)
				cout<<t - 1<<" Rumah";
			else
				cout<<"1 Hotel";
			
			cout<<")";
			
			if(hip && s.compare("/pay") != 0) {
				cout<<" (Sedang digadaikan)";
			}
			
			cout<<"\n";
			
			n++;
		}
		
		if(p->idPlaces.size() < 1)
			cout<<"Anda masih belum memiliki petak\n";
		else if(s.compare("/info") != 0)
			cout<<n<<". Batal";
			
		
		int pil;
		
		char res;
		if(p->idPlaces.size() > 0 && s.compare("/sell") == 0) {
			pil = Helper::inputValidate(n, "Pilih petak yang ingin dijual: ");
		
			if(pil != n) {
				Place* pl;
				int c = 0;
				for(int j = 0; j < p->idPlaces.size(); j++) {
					if(places.at(p->idPlaces.at(pil - 1)).isHipotik)
						continue;
					else
						c++;
						
					if(pil == c) {
						pl = &places.at(p->idPlaces.at(j));
						break;
					}
				}
				
				int harga = pl->buildPrices[0];
				if(pl->type > 1 && pl->type < 6)
					harga += pl->buildPrices[1] * (pl->type - 1);
				else if(pl->type > 5)
					harga += pl->buildPrices[1] * 4 + pl->buildPrices[2];
					
				cout<<"\nBank hanya membayar separuh dari harga pokok petak yang ingin dijual, harga pokok petak yang anda pilih adalah $"<<harga<<", jadi anda akan mendapatkan $"<<harga / 2<<endl;
				cout<<"Apakah anda yakin ingin menjual petak ini? (Y/N): ";
				cin>>res;
				
				if(res == 'Y') {
					p->updateMoney(harga / 2);
					p->idPlaces.erase(p->idPlaces.begin() + (pil - 1));
					pl->sell();
					
					cout<<"\nPenjulan petak berhasil, sisa uang anda $"<<p->money<<endl;
				}
			}
		}
		else if(p->idPlaces.size() > 0 && s.compare("/hipotik") == 0) {
			pil = Helper::inputValidate(n, "Pilih petak yang ingin digadaikan: ");
			
			if(pil != n) {
				Place* pl;
				int c = 0;
				for(int j = 0; j < p->idPlaces.size(); j++) {
					if(places.at(p->idPlaces.at(pil - 1)).isHipotik)
						continue;
					else
						c++;
						
					if(pil == c) {
						pl = &places.at(p->idPlaces.at(j));
						break;
					}
				}
				
				int harga = pl->buildPrices[3];
				
				cout<<"\nAnda akan menggadaikan petak ini dan mendapatkan $"<<harga<<", anda tidak dapat memungut harga sewa dari petak yang digadaikan sampai anda mengembailikan sebesar $"<<harga + 0.1 * harga<<endl;
				cout<<"Harap berhati hati, tanah yang digadaikan dapat dibeli pemain lain yang sedang singgah di tempat tersebut\n";
				cout<<"Apakah anda yakin ingin menggadaikan petak ini? (Y/N): ";
				cin>>res;
				
				if(res == 'Y') {
					p->updateMoney(harga);
					pl->isHipotik = true;
					
					cout<<"\nPenggadaian petak berhasil, sisa uang anda $"<<p->money<<endl;
				}
			}
		}
		else if(p->idPlaces.size() > 0 && s.compare("/pay") == 0) {
			pil = Helper::inputValidate(n, "Pilih petak yang ingin dibayar: ");
			
			if(pil != n) {
				Place* pl;
				int c = 0;
				for(int j = 0; j < p->idPlaces.size(); j++) {
					if(!places.at(p->idPlaces.at(pil - 1)).isHipotik)
						continue;
					else
						c++;
						
					if(pil == c) {
						pl = &places.at(p->idPlaces.at(j));
						break;
					}
				}
				
				int harga = pl->buildPrices[3] + 0.1 * pl->buildPrices[3];
				
				cout<<"\nHarga pelunasan hipotik petak ini sebesar $"<<harga<<endl;
				cout<<"Apakah anda yakin ingin membayar petak ini? (Y/N): ";
				cin>>res;
				
				if(res == 'Y') {
					if(p->money < harga) {
						cout<<"\nUang anda tidak cukup untuk melunasi hipotik"<<endl;
					}
					else {
						p->updateMoney(-harga);
						pl->isHipotik = false;
					
						cout<<"\nPelunasan hipotik petak berhasil, sisa uang anda $"<<p->money<<endl;
					}
				}
			}
		}
	}
}

void Gameplay::playerLose(int index) {
	Player* p = &players.at(index);
	currentTotalPlayer--;
	p->isActive = false;
	ChangeMap(p->x, p->y, ' '); //Hapus tandanya
	
	for(int i = 0; i < p->idPlaces.size(); i++) {
		places.at(p->idPlaces.at(i)).sell();
		p->idPlaces.erase(p->idPlaces.begin());
	}
}

void Gameplay::printTheWinner() {
	int n;
	for(int i = 0; i < players.size(); i++) {
		if(players.at(i).isActive)
			n = i;
	}
	
	cout<<"================================================================================\n\n";
	cout<<"================================================================================\n\n";
	cout<<"================================================================================\n\n";
	cout<<"========================= SELAMAT PEMENANGNYA: PLAYER "<<n + 1<<" ========================\n\n";
	cout<<"================================================================================\n\n";
	cout<<"================================================================================\n\n";
	cout<<"================================================================================";
}

void Gameplay::moneyDown() {
	cout<<"\n[WARNING]\nUang anda dibawah $0 dan tidak dapat melanjutkan permainan, sistem menyarankan anda untuk mengetikkan salah satu aksi dibawah: \n";
	cout<<"/sell\t\t = Menjual petak yang dimiliki\n/hipotik\t = Menggadaikan petak yang dimiliki\n/surrender\t = Menyerah dari permainan jika sudah tidak memiliki aset lagi\n";
}
