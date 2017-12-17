#include <iostream>
#include "Helper.h"
#include "Response.h"
using namespace std;

int Helper::inputValidate(int max, string custom) {
	int pil;
	
	while(1) {
		cout<<"\n"<<custom;
		cin>>pil;
		
		if(!cin.good())
			pil = 0;
			
		if(pil > 0 && pil <= max)
			break;
				
		Response::get(7);
		cin.clear();
		cin.ignore(INT_MAX, '\n');
	}
	
	return pil;
}
