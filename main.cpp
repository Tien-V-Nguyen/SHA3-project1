//		
//		main.cpp
//		SHA3 Project
//		Tien V. Nguyen - 20133954
//		School of Information and Comunication Technology
//


#include <cmath>
#include <string>
#include <fstream>
#include "StateArray.h"
#include "BitString.h"

using namespace std;


int main()
{
	char c[60], ch[60];
	int i, j;

	cout << "Nhap vao chuoi ky tu: " << endl;
	cin.getline(c, 60);
	
	BitString BStr(c);
	
	BStr.SHA3_512();
	
//	BStr.SHA3_224();
	
	char filename[50];
	
	cout << "Nhap ten tep: " ;
	cin.getline(filename, 50);
	
	ifstream f;
	f.open(filename);
	if(!f.is_open()){
		cout << "Khong the mo file" << endl;
	}else{
		
		f.getline(ch, 60);
		BitString BStr2(ch);
		
		BStr2.SHA3_512();
		}
		
	f.close();				
			
	system("pause");

	return 0; 
}


