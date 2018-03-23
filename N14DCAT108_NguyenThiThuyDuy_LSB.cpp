#include <iostream>
#include <string>
#include <bitset>
#include <fstream>
#include <cmath>
#include <stdlib.h>
#include <sstream>
//Nguyen Thi Thuy Duy _ N14DCAT108
using namespace std;
string textToBin(string text){
	int len = text.length();
	string kq="";
	for (int i = 0; i< len; i++){
		bitset<8> b(text.c_str()[i]);
      	kq+= b.to_string();
	}
	return kq;
}
string binToText(string bin){
	string kq="";
	stringstream sstream(bin);
    while(sstream.good())
    {
        bitset<8> bits;
        sstream >> bits;
        char c = char(bits.to_ulong());
        kq += c;
    }
    return kq;
}

int main(){
	/*string str1, str2;
	cin >> str1;
	cout << textToBin(str1);
	cin >> str2;
	cout <<binToText(str2);*/
	int chon;
	char key;
	do {
		cout << "MENU - *CHI AP DUNG FILE *.BMP, Vi du: DUY.bmp* \n1. Ma hoa \n2. Giai ma\nNHAP LUA CHON: ";
	cin >> chon;
	if ((chon!=1) && (chon!=2) )
		return 0;
	else 
	if (chon ==1){
		string namepic, mess;
		cout << "Nhap vao ten anh -- vi du: DUY.bmp : ";
		cin >> namepic;
		fflush(stdin);
		cout << "Nhap vao thong diep can giau vao anh: ";
		getline(cin,mess);
		//cout << textToBin(mess).length();
		string bin_mess = textToBin(mess) + "00000000"; // chèn 8 bit 0 de danh dau ket thuc thong diep bang null
		int len_mess = bin_mess.length();
		//cout << len_mess;
		//cout << bin_mess;
		char * arr;
		int size;
  		std::ifstream file (namepic.c_str(),std::ifstream::binary);
  		if (file.is_open()){
    		file.seekg (0,file.end);
		size = file.tellg();
		file.seekg (0);
    		arr = new char [size];
    		file.read (arr, size);
    		//cout << size;
    		if ((size-54)>=len_mess){
    			cout <<"Co the giau tin!" << endl;
    			int tmp = 54;
    			for (int i = 0; i <len_mess; i++){
    				arr[tmp] >>=1;
    				arr[tmp] <<=1;
    				arr[tmp]+= (bin_mess[i] - 48);
    				tmp++;
    			}
    			//Giai thich Dich phai (dich luan ly) -> Dich trai de bien bit LSB thanh 0 va giu nguyen cac bit ban dau.
    			/*
    			10011011 (dich phai 1) ----> 0.1001101 (dich trai 1)----> 10011010
    			*/
    			string out_namepic = "ENC_"+namepic;
				std::ofstream outfile (out_namepic.c_str(),std::ofstream::binary);
				outfile.write(arr,size);
				delete[] arr;
				file.close();
				outfile.close();
				cout << "Giau tin thanh cong!" << endl;
    		}
    		else cout << "Khong the giau tin!" << endl;
  		}
  		else {
  			cout << "Khong the mo file" << endl;;
  			//return 0;
  		}
  	}	
		
	else if(chon==2){
		string namepic;
		string mess="";
		string kq="";
		cout << "Nhap vao ten anh -- vi du: ENC_DUY.bmp : ";
		cin >> namepic;
		char * arr;
		int size;
  		std::ifstream file (namepic.c_str(),std::ifstream::binary);
  		if (file.is_open()){
    		file.seekg (0,file.end);
		size = file.tellg();
		file.seekg (0);
    		arr = new char [size];
    		file.read (arr, size);
    		int tmp = 54;
    			for (int i = 0; i <size; i+=8){
    				if(arr[tmp]%2==0) //arr duyet theo tung byte
    					mess+="0";
    				else 
    					mess+="1";
    				tmp++;
    			}
    			//cout << mess;
    			kq+=binToText(mess);
    			cout << "Thong diep da giau trong anh: ";
    			int i = 0;
    			while (kq[i]!='\0'){ 
    				cout<<kq[i];
    				i++;
    				//Duyet den ky tu null-danh dau ket thuc thong diep thi dung
    			}
				delete[] arr;
				file.close();	
				cout << endl;	
  		}
  		else {
  			cout << "Khong the mo file" << endl;
  			//return 0;
  		}
		
		}
		cout << "Ban co muon tiep tuc khong Y/N: ";
		cin >>	key;
	}
	while (key=='Y' || key=='y');
	cout << endl;
	return 0;
}
