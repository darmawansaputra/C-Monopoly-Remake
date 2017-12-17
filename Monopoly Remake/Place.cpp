#include "Place.h"
#include "Response.h"
#include "Helper.h"
#include "Player.h"

Place::Place(std::string n, std::string k, int ty, int p1[], int p2[], int xPos[], int yPos[]) {
	for(int i = 0; i < 5; i++) {
		xPositions[i] = xPos[i];
		yPositions[i] = yPos[i];
	}
	
	for(int i = 0; i < 6; i++) {
		rentPrices[i] = p1[i];
	}
	
	for(int i = 0; i < 4; i++) {
		buildPrices[i] = p2[i];
	}
	
	building = ty;
	
	name = n;
	komplek = k;
	type = 0;
	owner = -1;
	isHipotik = false;
}

int* Place::getPositionOf(int index) {
	int* ret = new int[2];
	
	ret[0] = xPositions[index];
	ret[1] = yPositions[index];
	
	return ret;
}

void Place::buildOrUpgrade(Player* p) {	
	//if build
	if(!isPurchased)
		cout<<"\nBeli bangunan: \n";
	
	//if user want to upgrade
	else
		cout<<"\nTingkatkan bangunan: \n";
	
	doBuildOrUpgrade(p);
}

void Place::sell() {
	isPurchased = false;
	owner = -1;
	type = 0;
	isHipotik = false;
}

int Place::getRentalPrice(vector<Place> places) {	
	int harga = rentPrices[type - 1];
	bool isDouble = true;
	
	for(int i = 0; i < places.size(); i++) {
		if(places.at(i).komplek == komplek && places.at(i).owner != owner) {
			isDouble = false;
			break;
		}
	}
	
	harga *= isDouble ? 2 : 1;
	
	return harga;
}

void Place::doBuildOrUpgrade(Player* p) {
	int pil;
	int i = 1;
	int ss;
	
	if(type == 0) {
		cout<<i++<<". Hanya tanah = $"<<buildPrices[0]<<endl;
		ss = 4;
	}
	else
		ss = 5 - type;
	
		
	for(int j = 1; j <= ss; j++) {
		cout<<i<<". "<<j<<" Rumah = $"<<buildPrices[1] * j;
		
		if(type == 0) {
			cout<<" dan tanah = $"<<buildPrices[0]<<" ($"<<buildPrices[1] * j + buildPrices[0]<<")";
		}
		
		i++;
		cout<<endl;
	}
		
	if(type < 6) {
		cout<<i++<<". 1 Hotel = $"<< buildPrices[2] << " dan "<<ss<<" Rumah = $"<<buildPrices[1] * ss;
		
		if(type == 0)
			cout<<" dan tanah = $"<<buildPrices[0]<<" ($"<<buildPrices[0] + buildPrices[1] * ss + buildPrices[2]<<")";
		else
			cout<<" ($"<<buildPrices[2] + buildPrices[1] * ss<<")";
			
		cout<<endl;
	}
			
	cout<<i<<". Kembali";
	
	CHOOSE:
	pil = Helper::inputValidate(i, "Masukkan pilihan: ");
		
	/*
		Proses pembelian:
		isOwned = p.id
		isPurchased = true
		type = pilihan user
	*/
		
	//Bukan pilih kembali
	if(pil != i) {
		//Get price from list base from user input
		int harga = 0;
		
		//Include harga tanahnya
		if(type == 0) {
			harga += buildPrices[0];
			
			//Rumah
			if(pil > 1 && pil <= 5)
				harga += (pil - 1) * buildPrices[1];
			
			//Hotel
			else if(pil > 5)
				harga += 4 * buildPrices[1] + buildPrices[2];
		}
		else {
			if(pil <= ss)
				harga += pil * buildPrices[1];
			else
				harga += ss * buildPrices[1] + buildPrices[2];
		}
		
		//Cek apakah uang user cukup
		//Jika tidak cukup, mulai lagi dari inputan
		if(p->money < harga) {
			cout<<endl;
			Response::get(4);
			goto CHOOSE;
		}
			
		//Jika uang mencukupi
		//Proses merubah data
		if(!isPurchased) {
			isPurchased = true;
			owner = p->id;
			p->idPlaces.push_back(p->currentPlaceIndex);
		}
			
		type = type + pil;
			
		//Decrease the money
		p->updateMoney(-harga);
			
		//Show the notif
		Response::get(8, p->money);
			
		system("pause");
	}
	//Kembali
	else {
			
	}
}

int Place::getPlayerOwner(vector<Player> players) {
	int idx;
	
	for(int i = 0; i < players.size(); i++) {
		if(owner == players.at(i).id)
			idx = i;
	}
	
	return idx;
}
