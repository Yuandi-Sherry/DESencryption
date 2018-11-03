#ifndef _DES_H_
#define _DES_H_
#include <bitset>
#include <string>
#include <iostream>
using namespace std;

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
	string result;
	DES(string str, string inputKey, bool crpt) ;
	~DES();

	void preprocess(const string, string *,  const int & size);

	void subprocess(const string, string *,  const int & size);

	string getResult();

	// origin 从左向右
	void charToBitset(string str, bitset<65> & origin);

	string bitsetToChar(const bitset<65> & result);

	// IP置换
	void IPpermutation(const bitset<65> & origin, bitset<33> & left, bitset<33> & right);


	// 左右交换
	bitset<65> LRexchange(const bitset<33> & left, const bitset<33> & right) ;


	// 16次迭代T
	bitset<65> iterateT(const bitset<33> & left, const bitset<33> & right);

	bitset<65> iterateT_solve(const bitset<33> & right, const bitset<33> & left);

	bitset<33> feistel(const bitset<33> lastRight, const bitset<49> key);

	bitset<49> eExpansion(const bitset<33> temp);

	// sBoxInput为8个S盒的输入 DONE
	void seperateeExpansion(const bitset<49> eResult, bitset<7> sBoxInput[]) ;

	// 经过S box 进行6-4转换
	void sBoxOuput(const bitset<7> sBoxInput[], bitset<5> sBoxResult[]);

	// 将S box中十进制转为4bit-二进制
	bitset<5> decimalToBinary(const int element);

	bitset<33> assemblySBoxOuput(const bitset<5> sBoxResult[]);

	void generateSubKeys(const bitset<65> key, bitset<49> k[]);

	void PC1permutation(const bitset<65> key,bitset<57>& PC1result, bitset<29>& c,	bitset<29>& d);

	void iterateLS(const bitset<29>& c, const bitset<29>& d, bitset<49> k[]);

	bitset<29> leftShift(const bitset<29> origin, int shiftBit);

	bitset<49> PC2permutation(const bitset<29>& c, const bitset<29>& d);

	bitset<33> Ppermutation(const bitset<33> origin);
	
	bitset<65> inverseIPpermutation(const bitset<65>& origin);	
};
#endif