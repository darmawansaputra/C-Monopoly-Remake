#include <iostream>
#include <math.h>
#include <sstream>
#include "Map.h"
#include "Place.h"

using namespace std;

char map[45][116] = {
	"[===========^=========^=========^=========^=========^=========^=========^=========^=========^=========^===========]",
	"|   BEBAS   |  HH101  |  KESEM  |  HH102  |  HH103  | LAP MER |  HH104  |  HH105  | R GELAP |  HH106  |  TERCYDUK |",
	"|           |         |         |         |         |         |         |         |         |         |           |",
	"|   PARKIR  | $22.000 |  PATAN  | $22.000 | $24.000 | $20.000 | $26.000 | $26.000 | $15.000 | $28.000 |   SATPAM  |",
	"<===========#=========%=========%=========%=========%=========%=========%=========%=========%=========#===========>",
	"|   JJ106   |                                                                                         |  PS LT 1  |",
	"|           |                                                                                         |           |",
	"|  $20.000  |                                                            [=======================]    |  $30.000  |",
	"<===========>                                                            |                       |    <===========>",
	"|   JJ105   |                                                            |                       |    |  PS LT 2  |",
	"|           |                                                            |      KARTU            |    |           |",
	"|  $18.000  |                                                            |      DANA UMUM        |    |  $30.000  |",
	"<===========>                                                            |                       |    <===========>",
	"|   DANA    |                                                            |                       |    |   DANA    |",
	"|           |                                                            (=======================)    |           |",
	"|   UMUM    |                                                                                         |   UMUM    |",
	"<===========>                                                                                         <===========>",
	"|   JJ104   |                                                                                         |  PS LT 3  |",
	"|           |                                                                                         |           |",
	"|  $18.000  |                                                                                         |  $32.000  |",
	"<===========>                 [==^==] [====] [====] [====] [====] [====] |     |    |                 <===========>",
	"|  HALL D4  |                 |  |  | |    | |    | |    | |    | |    | |     (====>                 |  AN NAHL  |",
	"|           |                 |     | |    | |    | |    | <====) |    | |          |                 |           |",
	"|  $20.000  |                 |     | (====) |    | (====) |      (====) (==== =====)                 |  $20.000  |",
	"<===========>                                               / Darmawan Saputra 2017 /                 <===========>",
	"|   JJ103   |                                                                                         |   KESEM   |",
	"|           |                                                                                         |           |",
	"|  $16.000  |                                                                                         |   PATAN   |",
	"<===========>                                                                                         <===========>",
	"|   JJ102   |                                                                                         |  PS LT 4  |",
	"|           |    [=======================]                                                            |           |",
	"|  $14.000  |    |                       |                                                            |  $35.000  |",
	"<===========>    |                       |                                                            <===========>",
	"|   R BAAK  |    |      KARTU            |                                                            | PJK KELUAR|",
	"|           |    |      KESEMPATAN       |                                                            |           |",
	"|  $15.000  |    |                       |                                                            |  $10.000  |",
	"<===========>    |                       |                                                            <===========>",
	"|   JJ101   |    (=======================)                                                            |  PS LT 5  |",
	"|           |                                                                                         |           |",
	"|  $14.000  |                                                                                         |  $40.000  |",
	"<===========#=========^=========^=========^=========^=========^=========^=========^=========^=========#===========>",
	"|   POS     |  GT305  |  GT304  |  KESEM  |  GT303  | R P SAF |PJK MASUK|  GT302  |  DANA   |  GT301  |   START   |",
	"|           |         |         |         |         |         |         |         |         |         |   :*@!~   |",
	"|   SATPAM  | $12.000 | $10.000 |  PATAN  | $10.000 | $20.000 | $20.000 |  $6.000 |  UMUM   |  $6.000 |  +$20.000 |",
	"(===========%=========%=========%=========%=========%=========%=========%=========%=========%=========%===========)"
	};
	
char menu[5][61] = {
"     [==^==] [====] [====] [====] [====] [====] |     |    |",
"     |  |  | |    | |    | |    | |    | |    | |     (====>",
"     |     | |    | |    | |    | <====) |    | |          |",
"     |     | (====) |    | (====) |      (====) (==== =====)",
"                      All Right Reserved by Darmawan Saputra"
};
	
char cardPlace[24][33] = {
	"[==============================]",
	"|       KARTU HAK MILIK        |",
	"|          KOMPLEK             |",
	"<==============================>",
	"|                              |",
	"|                              |",
	"|                              |",
	"|  Harga Sewa                  |",
	"|  Hanya Tanah       $         |",
	"|  1 Rumah           $         |",
	"|  2 Rumah           $         |",
	"|  3 Rumah           $         |",
	"|  4 Rumah           $         |",
	"|  1 Hotel           $         |",
	"|                              |",
	"|  Memiliki 1 kompleks tanah   |",
	"|  Harga sewa 2x lipat         |",
	"|                              |",
	"|                              |",
	"|  Harga 1 Rumah     $         |",
	"|  Harga 1 Hotel     $         |",
	"|  Harga Hipotik     $         |",
	"|                              |",
	"(==============================)",
};

void Replace(char t) {
	if(t == '=')
		cout<<char(205);
	else if(t == '|')
		cout<<char(186);
	else if(t == '#')
		cout<<char(206);
	else if(t == '^')
		cout<<char(203);
	else if(t == '<')
		cout<<char(204);
	else if(t == '>')
		cout<<char(185);
	else if(t == '%')
		cout<<char(202);
	else if(t == '[')
		cout<<char(201);
	else if(t == ']')
		cout<<char(187);
	else if(t == '(')
		cout<<char(200);
	else if(t == ')')
		cout<<char(188);
	//Player 1
	else if(t == ':')
		cout<<char(176);
	//Player 2
	else if(t == '*')
		cout<<char(177);
	//Player 3
	else if(t == '@')
		cout<<char(178);
	//Player 4
	else if(t == '!')
		cout<<char(219);
	//Player 5
	else if(t == '~')
		cout<<char(240);
	else
		cout<<t;
}

void ShowMenu() {
	cout<<endl<<endl;
	for(int i = 0; i < 5; i++) {
		for(int j = 0; j < 61; j++)
			Replace(menu[i][j]);
			
		cout<<endl;
	}
}

/*
	status:
	0 = not showing card
	1 = showing card
*/
void PrintMap(bool status, Place p) {
	if(!status) {
		PrintMap();
	}
	else {
		int x = 0;
		int y = 0;
		
		for(int i = 0; i < 45; i++) {
			for(int j = 0; j < 153; j++) {
				if(j < 116)
					Replace(map[i][j]);
				else if(i > 24)
					break;
				else if(j > 120) {
					int centerOfName = (16 - ceil(p.name.length() / 2));
					
					//Nama komplek
					if(x == 2 && (y == 19 || y == 20))
						cout<<p.komplek.at(y++ - 19);
						
					//Nama petak
					else if(x == 5 && y >= centerOfName && y < centerOfName + p.name.length())
						cout<<p.name.at(y++ - centerOfName);
					
					//Harga
					else if((x >= 8 && x <= 13) || (x >= 19 && x <= 21)) {
						stringstream str;
						if(x <= 13)
							str<<p.rentPrices[x - 8];
						else
							str<<p.buildPrices[x - 18];
						
						int len = str.str().length();
						
						if(y >= 22 && y < 22 + len)
							cout<<str.str().at(y++ - 22);
						else
							Replace(cardPlace[x][y++]);
					}
					
					// 
					
					else
						Replace(cardPlace[x][y++]);
				}
				else
					cout<<" ";
					
			}
			y = 0;
			x++;
			cout<<endl;
		}
	}
}

void PrintMap() {
	for(int i = 0; i < 45; i++) {
		for(int j = 0; j < 116; j++)
			Replace(map[i][j]);
			
		cout<<endl;
	}
}

void ChangeMap(int x, int y, char c) {
	map[y][x] = c;
}
