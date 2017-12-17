#include <iostream>
#include "Card.h"
#include "Place.h"
#include "Player.h"
#include "Map.h"
using namespace std;

/*
	DANA UMUM
	1. Maju sampai START
	2. Bebas dari pos satpam atau boleh dijual
	3. Bayar perbaikan rumah, $4.500 per rumah $11.000 per hotel
	4. Bayar kartu $10.000 atau ambil Kesempatan
	5. Karena kesalahan Bank anda terima $20.000
	6. Nemu uang $5.000 di kantin
	7. Bayar uang pulsa $10.000
	8. Dapat beasiswa $15.000
	9. Bayar Dokter $5.000
	10. Bayar uang kuliah $15.000
	11. Selamat anda ulang tahun dapat $5.000 tiap pemain
	
	KESEMPATAN
	1. Maju sampai START
	2. Bebas dari pos satpam atau boleh dijual
	3. Bayar perbaikan rumah, $2.500 per rumah $10.000 per hotel
	4. Mabuk di muka umum denda $1.500
	5. Melanggar lalu lintas denda $5.000
	6. Mundur tiga petak
	7. Maju sampai PS LT 5
	8. Maju sampai JJ104, bila melalui START dapat $20.000
	9. Kembali menuju GT101
	10. Nemu uang $10.000 di kantin
	11. Menang PKM AI/GT dapat $7.500
*/

Card::Card(int t, int a, string t2) {
	type = t;
	action = a;
	teks = t2;
}

void Card::CardAction(Player* p, vector<Place> places, int curPlayer) {
	type == 1 ? DanaUmum(p, places, curPlayer) : Kesempatan(p, places, curPlayer);
}

void Card::DanaUmum(Player* p, vector<Place> places, int curPlayer) {
	//Tampilkan teksnya
	cout<<"\nDANA UMUM: "<<teks<<endl;
	
	//Maju sampai START
	if(action == 1) {
		p->totalLap++;
		moveAction(0, places, curPlayer, p);
	}
	//Bebas dari pos satpam atau boleh dijual
	else if(action == 2) {
		p->hasSecurityCard = true;
	}
	//Bayar perbaikan rumah, $4.500 per rumah $11.000 per hotel
	else if(action == 3) {
		repairAction(4500, 11000, places, p);
	}
	//Bayar kartu $10.000 atau ambil Kesempatan
	else if(action == 4) {
		//Sudah diimplementasikan di gameplay
	}
	//Karena kesalahan Bank anda terima $20.000
	else if(action == 5) {
		p->updateMoney(20000);
		cout<<"Anda mendapatkan $20000, sisa uang anda $"<<p->money<<endl;
	}
	//Nemu uang $5.000 di kantin
	else if(action == 6) {
		p->updateMoney(5000);
		cout<<"Anda mendapatkan $10000, sisa uang anda $"<<p->money<<endl;
	}
	//Bayar uang pulsa $10.000
	else if(action == 7) {
		p->updateMoney(-10000);
		cout<<"Anda membayar $10000, sisa uang anda $"<<p->money<<endl;
	}
	//Dapat beasiswa $15.000
	else if(action == 8) {
		p->updateMoney(15000);
		cout<<"Anda mendapatkan $10000, sisa uang anda $"<<p->money<<endl;
	}
	//Bayar Dokter $5.000
	else if(action == 9) {
		p->updateMoney(-5000);
		cout<<"Anda membayar $5000, sisa uang anda $"<<p->money<<endl;
	}
	//Bayar uang kuliah $15.000
	else if(action == 10) {
		p->updateMoney(-15000);
		cout<<"Anda membayar $15000, sisa uang anda $"<<p->money<<endl;
	}
	//Selamat anda ulang tahun dapat $5.000 tiap pemain
	else if(action == 11) {
		//Sudah ditangani di depan
	}
}

void Card::Kesempatan(Player* p, vector<Place> places, int curPlayer) {
	//Tampilkan teksnya
	cout<<"\nKESEMPATAN: "<<teks<<endl;
	
	//Maju sampai START
	if(action == 1) {
		p->totalLap++;
		moveAction(0, places, curPlayer, p);
	}
	//Bebas dari pos satpam
	else if(action == 2) {
		p->hasSecurityCard = true;
	}
	//Bayar perbaikan rumah, $2.500 per rumah $10.000 per hotel
	else if(action == 3) {
		repairAction(2500, 10000, places, p);
	}
	//Mabuk di muka umum denda $1.500
	else if(action == 4) {
		p->updateMoney(-1500);
		cout<<"Anda membayar $1500, sisa uang anda $"<<p->money<<endl;
	}
	//Melanggar lalu lintas denda $5.000
	else if(action == 5) {
		p->updateMoney(-5000);
		cout<<"Anda membayar $5000, sisa uang anda $"<<p->money<<endl;
	}
	//Mundur tiga petak
	else if(action == 6) {
		moveAction(p->currentPlaceIndex - 3, places, curPlayer, p);
	}
	//Maju sampai PS LT 5
	else if(action == 7) {
		moveAction(39, places, curPlayer, p);
	}
	//Maju sampai JJ104, bila melalui START dapat $20.000
	else if(action == 8) {
		if(p->currentPlaceIndex > 16)
			p->updateMoney(20000);
			
		moveAction(16, places, curPlayer, p);
	}
	//Kembali menuju GT101
	else if(action == 9) {
		moveAction(1, places, curPlayer, p);
	}
	//Nemu uang $10.000 di kantin
	else if(action == 10) {
		p->updateMoney(10000);
		cout<<"Anda mendapatkan $10000, sisa uang anda $"<<p->money<<endl;
	}
	//Menang PKM AI/GT dapat $7.500
	else if(action == 11) {
		p->updateMoney(7000);
		cout<<"Anda mendapatkan $7000, sisa uang anda $"<<p->money<<endl;
	}
}

void Card::moveAction(int index, vector<Place> places, int curPlayer, Player* p) {
	//Proses perpindahan
	ChangeMap(p->x, p->y, ' '); //Hapus dulu tandanya
	
	if(index < 0)
		index = 40 + index;
		
	p->currentPlaceIndex = index;
		
	//Change player position
	int* resPos = places.at(p->currentPlaceIndex).getPositionOf(curPlayer);
	p->setPosition(resPos[0], resPos[1]);
		
	ChangeMap(p->x, p->y, p->identification);
		
	delete[] resPos;
}

void Card::repairAction(int hRmh, int hHtl, vector<Place> places, Player* p) {
	int rmh = 0;
	int htl = 0;
	for(int i = 0; i < p->idPlaces.size(); i++) {
		int type = places.at(p->idPlaces.at(i)).type;
			
		if(type < 5)
			rmh += type;
		else
			htl++;
	}
	int ttl = rmh  * 2500 + htl * 10000;
	p->updateMoney(-ttl);
	cout<<"Anda memiliki "<<rmh<<" rumah ($"<<rmh  * hRmh<<") dan "<<htl<<" hotel ($"<<htl * hHtl<<") = $"<<ttl<<endl;
	cout<<"Sisa uang anda $"<<p->money<<endl;
}
