#ifndef _DES_H_
 #define _DES_H_
 #include <bitset>
 #include <iostream>
 using namespace std;
 int IP[64] = {58, 50, 42, 34, 26, 18, 10, 2,
 		  60, 52, 44, 36, 28, 20, 12, 4,
 		  62, 54, 46, 38, 30, 22, 14, 6,
 		  64, 56, 48, 40, 32, 24, 16, 8,
 		  57, 49, 41, 33, 25, 17, 9, 1,
 		  59, 51, 43, 35, 27, 19, 11, 3,
 		  61, 53, 45, 37, 29, 21, 13, 5,
 		  63, 55, 47, 39, 31, 23, 15, 7};
 int Etable[48] = {32, 1, 2, 3, 4, 5,
 				  4, 5, 6, 7, 8, 9,
 				  8, 9, 10, 11, 12, 13,
 				  12, 13, 14, 15, 16, 17,
 				  16, 17, 18, 19, 20, 21,
 				  20, 21, 22, 23, 24, 25,
 				  24, 25, 26, 27, 28, 29,
 				  28, 29, 30, 31, 32, 1
 				};
 				    //                5                  10
 int sBox[8][64] = { {14,  4, 13,  1,  2, 15, 11, 18,  3, 10,  6, 12,  5,  9,  0,  7,
 					  0, 15,  7,  4, 15,  2, 13,  1, 10,  6, 12, 11,  9,  5,  3,  8,
 					  4,  1, 14,  8, 12,  6,  2, 11, 15, 12,  9,  7,  3, 10,  5,  0,
 					 15, 12,  8,  2,  4,  9,  1,  7,  5, 11,  3, 14, 10,  0,  6, 13},
 					
 					{15,  1,  8, 14,  6, 11,  3,  4,  9,  7,  2, 13, 12,  0,  5, 10,
 					  3, 13,  4,  7, 15,  2,  8, 14, 12,  0,  1, 10,  6,  9, 11,  5,
 					  0, 14,  7, 11, 10,  4, 13,  1,  5,  8, 12,  6,  9,  3,  2, 15,
 					 13,  8, 10,  1,  3, 15,  4,  2, 11,  6,  7, 12,  0,  5, 14,  9},
 					
 					{10,  0,  9, 14,  6,  3, 15,  5,  1, 13, 12,  7, 11,  4,  2,  8,
 					 13,  7,  0,  9,  3,  4,  6, 10,  2,  8,  5, 14, 12, 11, 15,  1,
 					 13,  6,  4,  9,  8, 15,  3,  0, 11,  1,  2, 12,  5, 10, 14,  7,
 					  1, 10, 13,  0,  6,  9,  8,  7,  4, 15, 14,  3, 11,  5,  2, 12},
 					
 					{ 7, 13, 14,  3,  0,  6,  9, 10,  1,  2,  8,  5, 11, 12,  4, 15,
 				     12,  8, 11,  5,  6, 15,  0,  3,  4,  7,  2, 12,  1, 10, 14,  9,
 				     10,  6,  9,  0, 12, 11,  7, 13, 15,  1,  3, 14,  5,  2,  8,  4,
 				      3, 15,  0,  6, 10,  1, 13,  8,  9,  4,  5, 11, 12,  7,  2, 14},
 				    
 				    { 2, 12,  4,  1,  7, 10, 11,  6,  8,  5,  3, 15, 13,  0, 14,  9,
 				     14, 11,  2, 12,  4,  7, 13,  1,  5,  0, 15, 10,  3,  9,  8,  6,
 				      4,  2,  1, 11, 10, 13,  7,  8, 15,  9, 12,  5,  6,  3,  0, 14,
 				     11,  8, 12,  7,  1, 14,  2, 13,  6, 15,  0,  9, 10,  4,  5,  3},
 				    
 				    {12,  1, 10, 15,  9,  2,  6,  8,  0, 13,  3,  4, 14,  7,  5, 11,
 				     10, 15,  4,  2,  7, 12,  9,  5,  6,  1, 13, 14,  0, 11,  3,  8,
 				      9, 14, 15,  5,  2,  8, 12,  3,  7,  0,  4, 10,  1, 13, 11,  6,
 				      4,  3,  2, 12,  9,  5, 15, 10, 11, 14,  1,  7,  6,  0,  8, 13},
 				    
 				    { 4, 11,  2, 14, 15,  0,  8, 13,  3, 12,  9,  7,  5, 10,  6,  1,
 				     13,  0, 11,  7,  4,  9,  1, 10, 14,  3,  5, 12,  2, 15,  8,  6,
 				      1,  4, 11, 13, 12,  3,  7, 14, 10, 15,  6,  8,  0,  5,  9,  2,
 				      6, 11, 13,  8,  1,  4, 10,  7,  9,  5,  0, 15, 14,  2,  3, 12},
 				    
 				    {13,  2,  8,  4,  6, 15, 11,  1, 10,  9,  3, 14,  5,  0, 12,  7,
 				      1, 15, 13,  8, 10,  3,  7,  4, 12,  5,  6, 11,  0, 14,  9,  2,
 				      7, 11,  4,  1,  9, 12, 14,  2,  0,  6, 10, 13, 15,  3,  5,  8,
 				      2,  1, 14,  7,  4, 10,  8, 13, 15, 12,  9,  0,  3,  5,  6, 11}};
 int PC1[56] = {57, 49, 41, 33, 25, 17, 9,
                1, 58, 50, 42, 34, 26, 18,
               10,  2, 59, 51, 43, 35, 27, 
               19, 11,  3, 60, 52, 44, 36,
               63, 55, 47, 39, 31, 23, 15,
                7, 62, 54, 46, 38, 30, 22,
               14,  6, 61, 53, 45, 37, 29,
               31, 13,  5, 28, 20, 12, 4};

 int PC2[48] = {14, 17, 11, 24,  1,  5,
                 3, 28, 15,  6, 21, 10,
                23, 19, 12,  4, 26,  8,
                16,  7, 27, 20, 13,  2,
                41, 52, 31, 37, 47, 55,
                30, 40, 51, 45, 33, 48,
                46, 42, 50, 36, 29, 32};

 int P[32] = {16,  7, 20, 21,
 	         29, 12, 28, 17,
 	          1, 15, 23, 26,
 	          5, 18, 31, 10,
 	          2,  8, 24, 14,
 	         32, 27,  3,  9,
 	         22, 11,  4, 25};

 int inverseIP[64] = {40,  8, 48, 16, 56, 24, 64, 32,
                      39,  7, 47, 15, 55, 23, 63, 31,
                      38,  6, 46, 14, 54, 22, 62, 30,
                      37,  5, 45, 13, 53, 21, 61, 29,
                      36,  4, 44, 12, 52, 20, 60, 28,
                      35,  3, 43, 11, 51, 19, 59, 27,
                      34,  2, 42, 10, 50, 18, 58, 26,
                      33,  1, 41,  9, 49, 17, 57, 25};
 class DES
 {
 private:
 	bitset<65> m; // 明文
 	bitset<65> c; // 密文
 	bitset<65> key; // 密钥
 	
 	bitset<49> k[16]; // 字密钥
 	const char* finalResult;
 	bool crpt;
 	
 public:
 	DES(string str, string inputKey, bool crpt) {
 		this->crpt = crpt;
 		charToBitset(inputKey,key);
 		generateSubKeys(key, k);
 		if(crpt) { // 加密
 			// 将char数组的明文转化为bitset[1, 64]
 			charToBitset(str, m);
 			// IP置换
 			bitset<33> IPleft;
 			bitset<33> IPright;
 			IPpermutation(m, IPleft, IPright);
 			//16轮迭代T（含交换置换W）
 			bitset<65> iterateTresult = iterateT(IPleft, IPright);
 			//逆置换IP-1
 			c = inverseIPpermutation(iterateTresult);
 		} else { // 解密
 			charToBitset(str, c);
 			bitset<33> IPleft;
 			bitset<33> IPright;
 			IPpermutation(c, IPright, IPleft);
 			bitset<65> iterateTresult = iterateT_solve(IPright, IPleft);
 			m = inverseIPpermutation(iterateTresult);
 		}
 		
 	}
 	~DES() {

 	}

 	string getResult() {
 		if(crpt) {
 			return bitsetToChar(c);
 		}
 		else {
 			return bitsetToChar(m);
 		}
 	}

 	// origin 从左向右
 	void charToBitset(string str, bitset<65> & origin) {
 		for(int i = 0; i < 8; i++) { // traverse STR
 			for(int j = 0; j < 8; j++) { // set bitset
 				if(((int)(str[i] + 128) % (1 << (8 - j))>> (7 - j) == 1)) {
 					origin.set(i*8 + j + 1);
 				} else {
 					origin.reset(i*8 + j + 1);
 				}
 			}
 		}
 	}

 	string bitsetToChar(const bitset<65> & result) {
 		string temp = "";
 		for(int i = 0; i <= 7; i++) {
 			char character;
 			character &= 0;
 			for(int j = 1; j <= 8; j++) {
 				character |= result[i*8+j] << (8 - j);
 			}
 			temp = temp + char(character - 128);
 		}
 		return temp;
 	}

 	// IP置换
 	void IPpermutation(const bitset<65> & origin, bitset<33> & left, bitset<33> & right) {
 		bitset<65> IPresult;
 		IPresult.reset();
 		for(int i = 1; i < 65; i++) {
 			if(origin[IP[i-1]] == 1) {
 				IPresult.set(i);
 			}
 		}
 		left.reset();
 		right.reset();
 		for(int i = 1; i <= 32; i++) {
 			left[i] = IPresult[i];
 			right[i] = IPresult[i + 32];
 		}
 	}


 	// 左右交换
 	bitset<65> LRexchange(const bitset<33> & left, const bitset<33> & right) {
 		bitset<65> result;
 		for(int i = 1; i <= 32; i++) {
 			result[i] = right[i];
 			result[32+i] = left[i];
 		}
 		return result;
 	}


 	// 16次迭代T
 	bitset<65> iterateT(const bitset<33> & left, const bitset<33> & right) {
 		bitset<33> lastLeft = left;
 		bitset<33> lastRight = right;
 		bitset<33> curLeft;
 		bitset<33> curRight;
 		for(int i = 1; i <= 16; i++) {
 			curLeft = lastRight;
 			curRight = lastLeft ^ feistel(lastRight, k[i-1]);
 			lastLeft = curLeft;
 			lastRight = curRight;
 		}
 		return LRexchange(curLeft, curRight);
 	}

 	bitset<65> iterateT_solve(const bitset<33> & right, const bitset<33> & left) {
 		//cout << "in iterateT" << endl;
 		bitset<33> lastA = right;
 		bitset<33> lastB = left;
 		bitset<33> curA;
 		bitset<33> curB;

 		for(int i = 16; i >= 1; i--) {
 			curA = lastB;
 			curB = lastA ^ feistel(lastB, k[i-1]);
 			lastA = curA;
 			lastB = curB;
 		}

 		return LRexchange(curA, curB);
 	}

 	bitset<33> feistel(const bitset<33> lastRight, const bitset<49> key){
 		//cout << "in feistel" << endl;
 		// 1. E拓展
 		bitset<49> eResult = eExpansion(lastRight);
 		// 2. eResult和字谜要进行异或运算
 		bitset<49> xorEResultKey = eResult^key;
 		// 3. (1)分组
 		bitset<7> sBoxInput[8];
 		seperateeExpansion(xorEResultKey, sBoxInput);
 		// 3. (2)sBox 6-4转换
 		bitset<5> sBoxResult[8];
 		sBoxOuput(sBoxInput, sBoxResult);
 		// 4. 连接
 		bitset<33> assemblyResult = assemblySBoxOuput(sBoxResult);
 		// 5. P置换
 		bitset<33> result = Ppremutation(assemblyResult);
 		return result;
 	}

 	bitset<49> eExpansion(const bitset<33> temp) {
 		bitset<49> result;
 		for(int i = 1; i <= 48; i++) {
 			result[i] = temp[Etable[i-1]];
 		}
 	}

 	// sBoxInput为8个S盒的输入 DONE
 	void seperateeExpansion(const bitset<49> eResult, bitset<7> sBoxInput[]) {
 		for(int i = 1; i <= 48; i++) {
 			sBoxInput[(i-1)/6][(i - 1)%6 + 1] = eResult[i];
 		}
 	}

 	// 经过S box 进行6-4转换
 	void sBoxOuput(const bitset<7> sBoxInput[], bitset<5> sBoxResult[]) {
 		int n = 0, m = 0;
 		int sBoxElement = 0;
 		for(int i = 0; i < 8; i++) {
 			n = sBoxInput[i][1] * 2 + sBoxInput[i][6] * 1;
 			m = sBoxInput[i][2] * 8 + sBoxInput[i][3] * 4 + sBoxInput[i][4] * 2 + sBoxInput[i][5] * 1;
 			sBoxElement = sBox[i][(n - 1)*16 + m - 1];
 			sBoxResult[i] = decimalToBinary(sBoxElement);
 		}
 	}

 	// 将S box中十进制转为4bit-二进制
 	bitset<5> decimalToBinary(const int element) {
 		bitset<5> result;
 		result[1] = element/8;
 		result[2] = (element % 8)/4;
 		result[3] = (element % 4)/2;
 		result[4] = element%2;
 		return result;
 	}

 	bitset<33> assemblySBoxOuput(const bitset<5> sBoxResult[]) {
 		bitset<33> result;
 		for(int i = 0; i < 8; i++) {
 			for(int j = 1; j <= 4; j++) {
 				result[i*4+j] = sBoxResult[i][j];
 			}
 		}
 		return result;
 	}
 	void generateSubKeys(const bitset<65> key, bitset<49> k[]) {
 		// (1) 得到C0D0
 		bitset<29> c;
 		bitset<29> d;
 		bitset<57> PC1result;
 		PC1permutation(key, PC1result, c, d);
 		// (2) 迭代循环左移
 		iterateLS(c,d,k);
 	}

 	void PC1permutation(const bitset<65> key,bitset<57>& PC1result, bitset<29>& c,
 		bitset<29>& d) {
 		for(int i = 1; i <= 56; i++) {
 			PC1result[i] = key[PC1[i-1]];	
 		}
 		for(int i = 1; i <= 28; i++) {
 			c[i] = PC1result[i];
 			d[i] = PC1result[i + 28];
 		}
 	}

 	void iterateLS(const bitset<29>& c, const bitset<29>& d, bitset<49> k[]) {
 		bitset<29> curC;
 		bitset<29> curD;
 		bitset<29> lastC = c;
 		bitset<29> lastD = d;
 		for(int i = 1; i <= 16; i++) {
 			if(i == 1 || i == 2 || i == 9 || i == 16) {
 				curC = leftShift(lastC, 1);
 				curD = leftShift(lastD, 1);
  			} else {
 				curC = leftShift(lastC, 2);
 				curD = leftShift(lastD, 2);
 			}
 			k[i-1] = PC2permutation(curC, curD);
 			lastC = curC;
 			lastD = curD;
 		}
 	}

 	bitset<29> leftShift(const bitset<29> origin, int shiftBit) {
 		bitset<29> result;
 		result = origin >> shiftBit;
 		if(shiftBit == 1) {
 			result[28] = origin[1];
 			result.reset(0);
 		} else {
 			result[28] = origin[2];
 			result[27] = origin[1];
 			result.reset(0);
 		}
 		return result;
 	}

 	bitset<49> PC2permutation(const bitset<29>& c, const bitset<29>& d) {
 		bitset<49> result;
 		bitset<57> linkCD;
 		for(int i = 1; i <= 28; i++) {
 			linkCD[i] = c[i];
 			linkCD[28+i] = d[i];
 		}
 		for(int i = 1; i <= 48; i++) {
 			result[i] = linkCD[PC2[i-1]];	
 		}
 		return result;
 	}

 	bitset<33> Ppremutation(const bitset<33> origin) {
 		bitset<33> result;
 		for(int i = 1; i < 33; i++) {
 			result[i] = origin[P[i-1]];
 		}
 		return result;
 	}
 	
 	bitset<65> inverseIPpermutation(const bitset<65>& origin) {
 		bitset<65> result;
 		for(int i = 1; i < 65; i++) {
 			result[i] = origin[inverseIP[i-1]];
 		}
 		return result;
 	}

 	
 };
 #endif