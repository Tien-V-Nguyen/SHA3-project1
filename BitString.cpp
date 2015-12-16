//
//		BitString.cpp
//		SHA3 Project
//		Tien V. Nguyen - 20133954
//		School of Information and Comunication Technology
//

#include "BitString.h"
#include "StateArray.h"

using namespace std;

		bool* BitString::d2b(int x){                //Chuyen mot so nguyen sang chuoi 8 bit
			bool *b; 
			b = new bool[8];
			
			for(int i = 0; i < 8; i++){
				b[i] = x % 2;
				x = x/2;
			}
			
			return b;
			
		}
		
		void BitString::printArray(bool *A, int n){
			for(int i = 0; i < n; i++){
				cout << A[i];
			}
			cout << endl;
		}
		
		int BitString::getLen(){
			return len;
		}
		
		bool* BitString::getB(){
			return this->b;
		}
		
		
		BitString::BitString(char *c){
		
		this->b = new bool[2048];
		
		//Tính kich thuoc xau ky tu
		int	i = 0, size_c = 0;
		while(c[i]!='\0'){
			i++;
			size_c++;
		}
		if(c[0] == '\0') size_c = 0; // 0 hay 1???
		
		//Chuyen xau ky tu ve chuoi bit	
		for(i = 0; i < size_c; i++){
		
			bool *temp = d2b(c[i]);
		
			for(int j = 0 ; j < 8; j++){
				b[j + 8*i] = temp[j];
			}
		
		}
		
		this->len = 8*size_c;
		
	}
	
	BitString::~BitString(){
		if(b) delete [] b;
	}
	
	void BitString::printBitString(){
		
		for(int i = 0; i < len; i++){
			cout << b[i];
		}
		
		cout << endl << endl;
		
		return;
	}
	
	bool* BitString::pad(int x, int m){
		int j;
		j = (x - ((m+2) % x)); 
		
		bool* p;
		p = new bool[j+2];
		p[0] = 1;
		p[j+1] = 1;
		for(int i = 1; i < j + 1; i++){
			p[i] = 0;
		}
		return p;
	}
	
	void  BitString::SPONGE(int r, int d){
		
		#if TEST 
		//this->printArray();
		#endif
		
		
		
		
		
		//Let P = M||pad(r, len(M))
		bool *p;
		p = pad(r, len);
		
		
		int j = r - (len+2) % r; //So phan tu cua pad(r, len) la j+2

		bool *P;
		
		P = new bool[len+j+2];
		
		for(int i = 0; i < len; i++){
			P[i] = this->b[i];
		}
		for(int i = len; i < len + j + 2; i++){
			P[i] = p[i - len];
		}
		
//		this->printArray(P, len+j+2);
		/////////////////////
		
		//n = len(P)/r
		int n = (len+j+2)/r;
		
		//Let P = P0||P1||P2||P3||....||P(n-1)
		//Let P(i) = P(i)||0(c) (Do dai P(i) luc nay duoc mo rong = b = 1600)
		bool **Q;
		Q = new bool*[n];
		for(int i = 0; i < n; i++){
			Q[i] = new bool[1600];
		}
		
		for(int i = 0; i < n; i++){
			for(int j = 0; j < r; j++){
				Q[i][j] = P[i*r + j];
			}
			for(int j = r; j < 1600; j++){
				Q[i][j] = 0;
			}
			
		}		
//		int c = 1600 - r;

		StateArray A;
		
		bool *S;
		bool ***temp;

		S = new bool[1600];
		temp = new bool**[5];
		for(int i = 0; i < 5; i++) temp[i] = new bool*[5];
		for(int i = 0; i < 5; i++){
			for(int j = 0; j < 5; j++){
				temp[i][j] = new bool[64];
			}
		}
		
		for(int i = 0; i < 1600; i++) S[i] = 0;
		
		//---------------------------------------------------------------------------//
		for(int i = 0; i < n; i++){			//for i = 0 to n-1, let S=f(S XOR (Q(i) || 0(c))
			
			for(int j = 0; j < 1600; j++){
				S[j] = S[j] ^ Q[i][j];				
			}
			
			for(int x = 0; x < 5; x++){
				for(int y = 0; y < 5; y++){
					for(int z = 0; z < 64; z++){
						temp[x][y][z] = S[(A.getSize_State()/25)*(5*y+x)+z];
					}
				}
			}
			
			A.setA(temp);
			A.Keccak_p(24);
			
			for(int x = 0; x < 5; x++){
				for(int y = 0; y < 5; y++){
					for(int z = 0; z < 64; z++){
						 S[(A.getSize_State()/25)*(5*y+x)+z] = A.getA()[x][y][z];
					}
				}
			}		
		}
		//---------------------------------------------------------------------------//
		
		int lenZ = 0;
		do{
					for(int i = lenZ; i < lenZ + r; i++){
						this->b[i] = S[i-lenZ];
					}
					
					lenZ = lenZ + r;
					
					if(d <= lenZ){
						
						for(int i = 0; i < 5; i++){
							for(int j = 0; j < 5; j++){
								if(temp[i][j] != NULL)	 delete[] temp[i][j];
							}
						}
						for(int i = 0; i < 5; i++) if(temp[i] != NULL)	delete [] temp[i];
						if(temp) delete [] temp;
						
						this->len = d;
						return;
					} 
					else{
							for(int x = 0; x < 5; x++){
								for(int y = 0; y < 5; y++){
									for(int z = 0; z < 64; z++){
										temp[x][y][z] = S[(A.getSize_State()/25)*(5*y+x)+z];
									}
								}
							}
							
							A.setA(temp);
							A.Keccak_p(24);
							
							for(int x = 0; x < 5; x++){
								for(int y = 0; y < 5; y++){
									for(int z = 0; z < 64; z++){
										 S[(A.getSize_State()/25)*(5*y+x)+z] = A.getA()[x][y][z];
									}
								}
							}

					}
		}while(1);
		
	}
	
	void BitString::KECCAK(int c, int d){
		this->SPONGE(1600 - c, d);
	}
	
	void BitString::SHA3_224(){
		
		b[len] = 0;
		b[len+1] = 1;
		len+=2;
		this->KECCAK(448, 224);
		
		char *hex = this->bin2hex();
		cout << "SHA3-224 Hash value: " << endl;
		for(int i = 0; i < len/4; i++){
			cout << hex[i];
		}	
		cout << endl << endl;

	}
	
	void BitString::SHA3_256(){
		b[len] = 0;
		b[len+1] = 1;
		len+=2;
		this->KECCAK(512, 256);
		
		this->printBitString();
		
		char *hex = this->bin2hex();
		cout << "SHA3-256 Hash Value: " << len << endl;
		for(int i = 0; i < len/4; i++){
			cout << hex[i];
		}	
		cout << endl << endl;


	}
	
	void BitString::SHA3_384(){
		b[len] = 0;
		b[len+1] = 1;
		len+=2;
		this->KECCAK(768, 384);
		char *c = this->bin2hex();
		cout << "SHA3-384 Hash Value: " << endl;
		for(int i = 0; i < len/4; i++){
			cout << c[i];
		}	
		cout << endl << endl;


	}
	
	void BitString::SHA3_512(){
		b[len] = 0;
		b[len+1] = 1;
		len+=2;
		
		
		this->KECCAK(1024, 512);
		
//		this->printBitString();
		
		cout << "SHA3-512 Hash Value: " << endl;
		for(int i = 0; i < len/4; i++){
			cout << this->bin2hex()[i];
		}	
		cout << endl << endl;
		
	}
	
	
	char* BitString::bin2hex(){
		char *hex;
		hex = new char[128];
		int *h;
		h = new int[64];
		
		for(int i = 0; i < len/8; i++){
			h[i] = 0; 
		//	int mu = 1;
			for(int j = 0; j < 8; j++){
				h[i] = h[i] + (b[i*8 + j])*int(pow(double(2),j));
				
			}
			
			for(int h0 = 0; h0 < 16; h0++){
				for(int h1 = 0; h1 < 16; h1++){
					if((16*h0 + h1) == h[i]){
						switch(h0){
							case 0: hex[2*i] = '0'; break;
							case 1: hex[2*i] = '1'; break;
							case 2: hex[2*i] = '2'; break;
							case 3: hex[2*i] = '3'; break;
							case 4: hex[2*i] = '4'; break;
							case 5: hex[2*i] = '5'; break;
							case 6: hex[2*i] = '6'; break;
							case 7: hex[2*i] = '7'; break;
							case 8: hex[2*i] = '8'; break;
							case 9: hex[2*i] = '9'; break;
							case 10: hex[2*i] = 'a'; break;
							case 11: hex[2*i] = 'b'; break;
							case 12: hex[2*i] = 'c'; break;
							case 13: hex[2*i] = 'd'; break;
							case 14: hex[2*i] = 'e'; break;
							case 15: hex[2*i] = 'f'; break;
						}
						switch(h1){
							case 0: hex[2*i+1] = '0'; break;
							case 1: hex[2*i+1] = '1'; break;
							case 2: hex[2*i+1] = '2'; break;
							case 3: hex[2*i+1] = '3'; break;
							case 4: hex[2*i+1] = '4'; break;
							case 5: hex[2*i+1] = '5'; break;
							case 6: hex[2*i+1] = '6'; break;
							case 7: hex[2*i+1] = '7'; break;
							case 8: hex[2*i+1] = '8'; break;
							case 9: hex[2*i+1] = '9'; break;
							case 10: hex[2*i+1] = 'a'; break;
							case 11: hex[2*i+1] = 'b'; break;
							case 12: hex[2*i+1] = 'c'; break;
							case 13: hex[2*i+1] = 'd'; break;
							case 14: hex[2*i+1] = 'e'; break;
							case 15: hex[2*i+1] = 'f'; break;
						}
					}
				}
			}
		}
		
		
		return hex;
	}
	
	

