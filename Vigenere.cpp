#include<iostream>
#include<string>
#include<bits/stdc++.h>
using namespace std;

// Ham ma hoa tung ky tu
char maHoakt(char plain, char key){
    if(!isalpha(plain)) return plain;        // Khong phai chu -> giu nguyen

    char base = isupper(plain) ? 'A' : 'a';  // Giu nguyen viet hoa/thg

    return (plain - base + (tolower(key) - 'a')) % 26 + base;
}

// Ham giai ma tung ky tu
char giaiMakt(char cipher, char key){
	if(!isalpha(cipher)) return cipher;
	char base = isupper(cipher) ? 'A' : 'a';
	return (cipher - base - (tolower(key) - 'a') + 26)%26 + base;
}
string maHoaChuoi( string plainText, string key){
	string cipherText = "";
	int keyIndex = 0;
	for(int i = 0; i<plainText.length(); i++){
		char x = plainText[i];
		if(isalpha(x)){
			cipherText += maHoakt(x, key[keyIndex % key.size()]);
			keyIndex++; // chi tang khi gap chu cai
		}
		else
			cipherText += x;
	}
	return cipherText;
}

string giaiMaChuoi(string cipherText, string key){
	string plainText = "";
	int keyIndex = 0;
	for(int i = 0; i<cipherText.length(); i++){
		char x = cipherText[i];
		if(isalpha(x)){
			plainText += giaiMakt(x, key[keyIndex % key.size()]);
			keyIndex++;
		}
		else
			plainText +=x;
	}
	return plainText;
}


main(){
	string key, plainText;
	cout<<"Nhap vao ban ro:"<<endl;
	getline(cin,plainText);
	cout<<"Nhap vao khoa k:"<<endl;
	getline(cin,key);
	cout<<"Ma hoa:"<<maHoaChuoi(plainText,key)<<endl;
	cout<<"Giai Ma:"<<giaiMaChuoi(maHoaChuoi(plainText, key), key);
}
