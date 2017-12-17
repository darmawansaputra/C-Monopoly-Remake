#ifndef __RESPONSE_H_INCLUDED__
#define __RESPONSE_H_INCLUDED__
#include <iostream>
#include <string>
using namespace std;
class Response {
	public:
		static void get(int req);
		static void get(int req, int x);
		static void get(int req, int x, int y);
		static void call(string str);
};

#endif
