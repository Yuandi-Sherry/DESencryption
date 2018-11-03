#include <iostream>
#include <string>
#include "DES.h"
using namespace std;
int main() {
	// 加密，输入密钥，从文件读取明文
	 // 明文
	string robust;
	while(true) {
		cout << "Input" << endl 
			 << "**** 0 to encryption" << endl
			 << "**** 1 to decryption (make sure you have already encrypted your codes)" << endl
			 << "**** 2 to exit" << endl;
		cin >> robust;
		if(robust == "0") {
			cout << "ENCRYPTION MODE" << endl;
			string M;
			cout << "Please input m" << endl;
			cin >> M;
			string tempKey;
			cout << "Please input key" << endl;
			cin >> tempKey;
			while(tempKey.length() != 8) {
				cout << "Error! Please input again" << endl;
				cin >> tempKey;
			} 
			DES encryption(M, tempKey, 1);
		} else if(robust == "1") {
			cout << "DECRYPTION MODE" << endl;
			string key2;
			cout << "Please input key to DECRYPTION" << endl;
			cin >> key2;
			while(key2.length() != 8) {
				cout << "Error! Please input again" << endl;
				cin >> key2;
			} 
			DES decryption("", key2, 0);
			cout << "DECRYPTION " << decryption.result << endl;
		} else if(robust == "2"){
			break;
		} else {
			cout << "[WARNING] There's something wrong with your input, please input again." << endl;
		}
	}
	
}