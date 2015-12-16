//
//		BitString.h
//		SHA3 Project
//		Tien V. Nguyen - 20133954
//		School of Information and Comunication Technology
//

#ifndef _SHA3_BitString_
#define _SHA3_BitString_

#include <iostream>
#include <cstdlib>
#include <cmath>

using namespace std;

class BitString{
	private:
	
	int len;
	bool *b;
	
	public:	
	
	void printArray(bool *A, int n);
	
	bool* d2b(int x);
	
	int getLen();
	
	bool* getB();
	
	BitString(char *c);
	
	~BitString();
	
	void printBitString();
	
	bool *pad(int x, int m);
	
	void  SPONGE(int r, int d);
	
	void KECCAK(int c, int d);
	
	void SHA3_224();
	
	void SHA3_256();
	
	void SHA3_384();
	
	void SHA3_512();
	
	char *bin2hex();
	
	
	
};

#endif
