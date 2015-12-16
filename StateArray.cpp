//
//		StateArray.cpp
//		SHA3 Project
//		Tien V. Nguyen - 20133954
//		School of Information and Comunication Technology
//


#include "StateArray.h"
#include "BitString.h"
	
//	#define TEST 0
	
	bool* StateArray::d2b(int x){                //Chuyen mot so nguyen sang chuoi 8 bit
		bool *b; 
		b = new bool[8];
		
		for(int i = 7; i >= 0; i--){
			b[i] = x % 2;
			x = x/2;
		}
		
		return b;
		
	}

	int StateArray::getSize_State(){
		return size_State;
	}
	
	bool*** StateArray::getA(){
		return a;
	}
	
	void StateArray::setA(bool ***temp){
		for(int x = 0; x < 5; x++){
				for(int y = 0; y < 5; y++){
					for(int z = 0; z < 64; z++){
						this->a[x][y][z] = temp[x][y][z];
					}
				}
			}
	}
	

	StateArray::StateArray(const StateArray &obj){
		int x, y, z;
		this->size_State = obj.size_State;
		int w = this->size_State/25;
		bool ***a;
		a = new bool**[5];
		for(x = 0; x < 5; x++){
			a[x] = new bool*[5];
		}
		for(x = 0; x < 5; x++){
			for(y = 0; y < 5; y++){
				a[x][y] = new bool[w];
			}
		}
		
		this->a = obj.a;
		
		for(x = 0; x < 5; x++){
			this->a[x] = obj.a[x];
			for(y = 0; y < 5; y++){ 
				this->a[x][y] = obj.a[x][y];
				for(z = 0; z < w; z++){
					this->a[x][y][z] = obj.a[x][y][z];
				}
			}
		}
	}
	StateArray::StateArray(int size){
		
		int x, y, z;
		size_State = size;
		int w = size/25;
		
		a = new bool**[5];
		for(x = 0; x < 5; x++){
			a[x] = new bool*[5];
		}
		for(x = 0; x < 5; x++){
			for(y = 0; y < 5; y++){
				a[x][y] = new bool[w];
			}
		}
		
		for(x = 0; x < 5; x++){
			for(y = 0; y < 5; y++){
				for(z = 0; z < w; z++){
					a[x][y][z] = 0;
				}
			}
		}
	}

	StateArray::StateArray(){
		
		int x, y, z;
		size_State = 1600;
		int w = 64;
		
		a = new bool**[5];
		for(x = 0; x < 5; x++){
			a[x] = new bool*[5];
		}
		for(x = 0; x < 5; x++){
			for(y = 0; y < 5; y++){
				a[x][y] = new bool[64];
			}
		}
	
		for(x = 0; x < 5; x++){
			for(y = 0; y < 5; y++){
				for(z = 0; z < w; z++){
					this->a[x][y][z] = 0;
				}
			}
		}
	}
	
	StateArray::~StateArray(){
		
		for(int i = 0; i < 5; i++){
			for(int j = 0; j < 5; j++){
				if(a[i][j])	 delete a[i][j];
			}
		}
		for(int i = 0; i < 5; i++) if(a[i])	delete [] a[i];
//		x = 0; y = 0;
		if(a) delete [] a;
	}
	
	void StateArray::String2State(char *c){  //Convert a string to a State Array
		
		int x, y, z;
		bool b[size_State];
		for(int i = 0; i < size_State; i++) b[i] = 0;
		
		//Tính kich thuoc xau ky tu
		int	i = 0, size_c = 0;
		while(c[i]!='\0'){
			i++;
			size_c++;
		}
		
		//Chuyen xau ky tu ve chuoi bit	
		for(i = 0; i < size_c; i++){
		
			bool *temp = d2b(c[i]);
		
			for(int j = 0 ; j < 8; j++){
				b[j + 8*i] = temp[j];
			}
		
		}
		
		for(x = 0; x < 5; x++){
			for(y = 0; y < 5; y++){
				for(z = 0; z < size_State/25; z++){
					a[x][y][z] = b[(size_State/25)*(5*y+x)+z];
				}
			}
		}
		
	}
	
	bool* StateArray::String2Bits(char *c){
		int x, y, z;
		bool* b;
		b = new bool[size_State];
		for(int i = 0; i < size_State; i++) b[i] = 0;
		
		//Tính kich thuoc xau ky tu
		int	i = 0, size_c = 0;
		while(c[i]!='\0'){
			i++;
			size_c++;
		}
		
		
		
		//Chuyen xau ky tu ve chuoi bit	
		for(i = 0; i < size_c; i++){
		
			bool *temp = d2b(c[i]);
		
			for(int j = 0 ; j < 8; j++){
				b[j + 8*i] = temp[j];
			}
		
		}
		
		return b;
	}
	
	void StateArray::Bits2State(bool *b){
		
		int x, y, z;
		
		for(x = 0; x < 5; x++){
			for(y = 0; y < 5; y++){
				for(z = 0; z < size_State/25; z++){
					a[x][y][z] = b[(size_State/25)*(5*y+x)+z];
				}
			}
		}
	}
	
	bool*  StateArray::State2Bits(){
		int x, y, z;
		bool* StringBit;
		StringBit = new bool[size_State];
		for(int i = 0; i < size_State; i++) StringBit[i] = 0;
		
		for(x = 0; x < 5; x++){
			for(y = 0; y < 5; y++){
				for(z = 0; z < size_State/25; z++){
					StringBit[(size_State/25)*(5*y+x)+z] = a[x][y][z];
				}
			}
		}
		
		return StringBit;
	}
	
	void StateArray::printState(){
		int x, y, z;
		for(x = 0; x < 5; x++){
			for(y = 0; y < 5; y++){
				for(z = 0; z < size_State/25; z++){
	  				cout << this->a[x][y][z];
				}
			}
		}
		cout << endl << endl;
		return;
	}
	
	void StateArray::thetaStep(StateArray	&B)	{
		int x, y, z;
		int w;
		w = (size_State)/25;   //Do dai cua mot Lane
		
		//StateArray B;		
		
		bool **c, **d;
		
		c = new bool*[5];
		for(int i = 0; i < 5; i++) c[i] = new bool[w];	
		d = new bool*[5];
		for(int i = 0; i < 5; i++) d[i] = new bool[w];
		
		for(x = 0; x < 5; x++){
			for(z = 0; z < w; z++){
				c[x][z] = 0;
				d[x][z] = 0;
			}
		}	
		
		for(x = 0; x < 5; x++){
			for(z = 0; z < w; z++){
				c[x][z] = a[x][0][z] ^ a[x][1][z] ^ a[x][2][z]
							 ^ a[x][3][z] ^ a[x][4][z];
			}
		}
		
		for(x = 0; x < 5; x++){
			for(z = 0; z < w; z++){
				d[x][z] = c[(x+4) % 5][z] ^ c[(x+1) % 5][(z-1+w) % w];   //(x-1) = (x+4) (mod 5)
			}
		}
		
		for(x = 0; x < 5; x++){
			for(y = 0; y < 5; y++){
				for(z = 0; z < w; z++){
					B.a[x][y][z] = this->a[x][y][z] ^ d[x][z];
//					cout << B.a[x][y][z];
				}
			}
		}
		
		#ifdef TEST
		cout << "thetaStep:" << endl;
		B.bin2hex();
		system("pause");
		#endif
		
		for(x = 0; x < 5; x++){
			delete[] c[x];
			delete[] d[x];
		}
		delete[] c;
		delete[] d;
				
		return;

	}
	
	void StateArray::rhoStep(StateArray	 &C)	{
		
		int x, y, z;
		int w = (this->size_State)/25;
//		StateArray C;
//		C = StateArray();
		
		for(z = 0; z < w; z++){
			C.a[0][0][z] = this->a[0][0][z];
		}
		
		x = 1; y = 0;
		
		for(int t = 0; t < 24; t++){
			
			for(z = 0; z < w; z++){
				C.a[x][y][z] = this->a[x][y][(z - (t+1)*(t+2)/2 + 320) % w];
			}
			int temp = y; 
			y = (2*x + 3*temp) % 5;
			x = temp;
			
		}
		
		#ifdef TEST 
		cout << "rhoStep: \n";
		C.bin2hex();
		system("pause");
		#endif
		
		return;
	}
	
	void StateArray::piStep(StateArray	&D){
		
		int x, y, z;
		int w = (this->size_State)/25;
//		StateArray D;
//		D = StateArray(this->size_State);
		
		for(x = 0; x < 5; x++){
			for(y = 0; y < 5; y++){
				for(z = 0; z < w; z++){
					D.a[x][y][z] = this->a[(x+3*y)%5][x][z];
				//	D.a[y][(2*x+3*y)%5][z] = this->a[x][y][z];
				}
			}
		}
		
		#ifdef TEST
		cout << "piStep: \n";
		D.bin2hex();
		system("pause");
		#endif
		
		return;
	}
	
	void StateArray::chiStep(StateArray	&E){
		int x, y, z;
		int w = (this->size_State)/25;
		
		for(x = 0; x < 5; x++){
			for(y = 0; y < 5; y++){
				for(z = 0; z < w; z++){
					E.a[x][y][z] = (this->a[x][y][z]) ^ ((this->a[(x+1)%5][y][z] ^ 1) 
															&& (this->a[(x+2)%5][y][z]));
				//	E.a[x][y][z] = (this->a[x][y][z]) ^ ((this->a[x][(y+1)%5][z] ^ 1) 
				//											&& this->a[x][(y+2)%5][z]);
				}
			}
		}
		
		#ifdef TEST
		cout << "chiStep: \n";
		E.bin2hex();
		system("pause");
		#endif
		
		return;
	}
	
	bool StateArray::rc(int t){
		
		int k = t%255;
		
		if(k == 0) return 1;
		
		bool *R;
		R = new bool[k+8];
		for(int i = 0; i < k+8; i++) R[i] = 0;
		R[k] = 1;
		
		for(int i = 1; i <= k; i++){							//Set R = 0||R
			R[k-i] 	   = R[k-i] ^ R[k+8 - i];		//R[0] = R[0] + R[8]
			R[k-i + 4] = R[k-i + 4] ^ R[k+8 - i];	//R[4] = R[4] + R[8]
			R[k-i + 5] = R[k-i + 5] ^ R[k+8 - i];	//R[5] = R[5] + R[8]
			R[k-i + 6] = R[k-i + 6] ^ R[k+8 - i];	//R[6] = R[6] + R[8]
		}
		
		return R[0];
	}
	
	
	void StateArray::iotaStep(StateArray &F, int iota){
		
		int x, y, z;
		int w = (this->size_State)/25;
				
		for(x = 0; x < 5; x++){
			for(y = 0; y < 5; y++){
				for(z = 0; z < w; z++){
					F.a[x][y][z] = this->a[x][y][z];
				}
			}
		}
		
		bool *RC;
		
		RC = new bool[w];
		for(int i = 0; i < w; i++) RC[i] = 0;
		
		double l = log2(w);
		
		for(int j = 0; j <= l; j++){     //?????????????????????????????????? j < l or j <= l
			RC[int(pow(double(2),j)) - 1] = rc(j+7*iota);
		}
		
		for(z = 0; z < w; z++){
			F.a[0][0][z] = F.a[0][0][z] ^ RC[z];
		}
		
		#ifdef TEST
		cout << "iotaStep: \n";
		F.bin2hex();
		system("pause");
		#endif
		
		return;
		
	}
	
	void StateArray::Rnd(StateArray &G, int iota)
	{
		StateArray A, B, C, D;
		
		this->thetaStep(A);
		A.rhoStep(B);
		B.piStep(C);
		C.chiStep(D);
		D.iotaStep(G, iota);
		
		return;
	}
	
	void StateArray::Keccak_p(int n, char *c){
		
		int x, y, z;
		
		StateArray A;
		
		A.String2State(c);				//Convert the String c into a state array
		
		int w = size_State/25;
		double l = log2(double(w));
		
		for(int i = int(2*l + 12 - n); i < int(2*l + 12); i++){
			A.Rnd(A, i);//??????????????????????????????????????????
		}
		
		bool* S = A.State2Bits();
		
//		this->fromBitString = A.fromBitString;
//		this->intoBitString = S;
		
		for(x = 0; x < 5; x++){
			for(y = 0; y < 5; y++){
				for(z = 0; z < w; z++){
					this->a[x][y][z] = A.a[x][y][z];
				}
			}
		}
	}
	
	void StateArray::Keccak_p(int n){
		int x, y, z;
		
		int w = size_State/25;
		double l = log2(double(w));
		
		StateArray A;
		
		for(x = 0; x < 5; x++){
			for(y = 0; y < 5; y++){
				for(z = 0; z < w; z++){
					A.a[x][y][z] = this->a[x][y][z];
				}
			}
		}
		
		
		for(int i = int(2*l + 12 - n); i < int(2*l + 12); i++){	//Lap n vong
			A.Rnd(A, i); 										//??????????? A = Rnd(A, i)?
		}
		
		for(x = 0; x < 5; x++){
			for(y = 0; y < 5; y++){
				for(z = 0; z < w; z++){
					this->a[x][y][z] = A.a[x][y][z];
				}
			}
		}
	}
	
	void StateArray::equal(StateArray &B){
		this->size_State = B.size_State;
		for(int x = 0; x < 5; x++){
			for(int y = 0; y < 5; y++){
				for(int z = 0; z < (B.size_State)/25; z++){
					this->a[x][y][z] = B.a[x][y][z];
				}
			}
		}
	}

	void StateArray::bin2hex(){
		char *hex;
		hex = new char[400];
		int *h;
		h = new int[200];
		
		bool b[1600];
		
		for(int x = 0; x < 5; x++){
			for(int y = 0; y < 5; y++){
				for(int z = 0; z < 64; z++){
					b[64*(5*y+x)+z] = this->a[x][y][z];
				}
			}
		}
		
		for(int i = 0; i < size_State/8; i++){
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
		
		for(int i = 0; i < 400; i++){
			cout << hex[i];
		}
		cout << endl;
		
		return;
	}
