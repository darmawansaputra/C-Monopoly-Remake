#include "Response.h"
#include <iostream>
#include <sstream>
using namespace std;

/*
	List of code response:
	1 = bayar sewa
	2 = upgrade bangunan salah input
	3 = berhasil beli
	4 = gagal beli karena uang tidak cukup
	5 = gagal upgrade karena uang tidak cukup
	6 = bayar pajak
	7 = salah input aksi
*/
	
void Response::get(int req) {
	stringstream str;
	if(req == 2)
		str<<"Pilihan upgrade salah, coba yang benar!";
	else if(req == 4)
		str<<"Pembelian bangunan gagal, karena uang tidak mencukupi";
	else if(req == 5)
		str<<"Upgrade bangunan gagal, karena uang tidak mencukupi";
	else if(req == 7)
		str<<"\nPilihan anda salah, pilih dengan benar!";
		
	Response::call(str.str());
}

void Response::get(int req, int x) {
	stringstream str;
	if(req == 3)
		str<<"Pembelian bangunan berhasil, sisa uang anda $"<<x;
	else if(req == 8)
		str<<"\nPembelian bangunan berhasil, sisa uang anda $"<<x<<endl;
		
	Response::call(str.str());
}

void Response::get(int req, int x, int y) {
	stringstream str;
	if(req == 1)
		str<<"\nAnda berhenti di bangunan lawan dan membayar sebesar $"<<x<<", sisa uang anda $"<<y;
	else if(req == 6)
		str<<"\nAnda terkena pajak sebesar $"<<x<<", sisa uang anda $"<<y<<"\n";
		
	Response::call(str.str());
}

void Response::call(string str) {
	cout<<str;
}
