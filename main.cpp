#include <iostream>
#include <string>
#include "DES.h"
using namespace std;
int main() {
	// 加密，输入密钥，从文件读取明文
	 // 明文
	string M;
	const char* key=""; // 密钥
	bool crpt = 1; // 1-> 加密，2->解密
	cout << "Please input m" << endl;
	cin >> M;
	while(M.length() != 8) {
		cout << "Error! Please input again" << endl;
		cin >> M;
	} 
	string tempKey;
	cout << "Please input key" << endl;
	cin >> tempKey;
	while(tempKey.length() != 8) {
		cout << "Error! Please input again" << endl;
		cin >> tempKey;
	} 
	DES jiami(M, tempKey, crpt);
	cout << "ENCRYPTION " << jiami.getResult() << endl;
	

	// 密文
	string C = jiami.getResult();
	//m = C.c_str();
	string key2;
	cout << "Please input key to DECRYPTION" << endl;
	cin >> key2;
	while(key2.length() != 8) {
		cout << "Error! Please input again" << endl;
		cin >> key2;
	} 
	
	//const char* miwen = jiami.getResult(); string

	DES jiemi(C, key2, !crpt);

	cout << "DECRYPTION " << jiemi.getResult() << endl;

	// 解密
}