//
//		StateArray.h
//		SHA3 Project
//		Tien V. Nguyen - 20133954
//		School of Information and Comunication Technology
//

#ifndef _SHA3_StateArray_
#define _SHA3_StateArray_

#include <iostream>
#include <cstdlib>
#include <cmath>

using namespace std;

class StateArray{
	private:
	int size_State;	
	bool ***a;
	bool* fromBitString;
	bool* intoBitString;
	
	public:
	
	bool *d2b(int x);
	
	int getSize_State();
	
	bool ***getA();
	
	void setA(bool ***temp);	
	
	StateArray(int size);
	
	StateArray(const StateArray &obj);
	
	StateArray();
	
	~StateArray();

	void String2State(char *c);			//Convert a string of charaters into a state array
	
	bool* String2Bits(char *c);			//Convert a string of characters into a string of bits
	
	void Bits2State(bool *b);			//Convert a string of bits into a state array
	
	bool* State2Bits();					//Convert a state array into a string of bit
	
	void printState();	

	void thetaStep(StateArray &B);

	void rhoStep(StateArray &C);	

	void piStep(StateArray &D);	

	void chiStep(StateArray &E);	

	bool rc(int t);	

	void iotaStep(StateArray &F, int iota);

	void Rnd(StateArray &G, int iota);
	
	void Keccak_p(int n, char *c);
	
	void Keccak_p(int n);
	
	void equal(StateArray &B);
	
	void bin2hex();
};



#endif
