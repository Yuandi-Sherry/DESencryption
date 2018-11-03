# DES算法原理概述

| 姓名   | 学号     | 学院                 | 班级                 |
| ------ | -------- | -------------------- | -------------------- |
| 周远笛 | 16340311 | 数据科学与计算机学院 | 软件工程（数字媒体） |

DES算法主要原理为将输入明文拆分为64bit一块，经过换位和置换输出64位密文，用同样的64bit（有效位为56bit）的密钥进行加密解密。

## 总体结构

### 加密

1. 将明文根据PKCS#5规范进行填充并分解为64bit的块
2. 对于每个块将字符串形式转换为对应的bit这里使用了C++中的bitset数据结构
3. 进行IP置换
4. 进行16轮迭代T并对结果进行交换置换
5. 进行IP逆置换
6. 将每一块的密文转回字符串并连接起来
7. 将密文存入文件

> 原因是很多明文经过转化之后不再是可输出字符，因而解密的时候如果直接将输出复制会导致无法解密，这里采用将密文存入文件的方法

### 解密

1. 从文件或内存中读取密文字符串
2. 将密文从字符串的形式转换为对应的bitset
3. 进行IP置换
4. 进行倒序的16论迭代并对结果进行交换置换
5. 进行IP逆直换
6. 将每一块明文转会字符串并连接起来
7. 根据明文的最后一位数字裁剪掉最后几字节恢复明文

## 模块分解

### 输入任意长度字符串并分解

```c
/* 
 * @Param1 输入原始字符串
 * @Param2 接收字符串分解之后每个八字节的字串
 * @Param3 字符串数组大小
 **/
void preprocess(const string, string* , const int)
```

### 子密钥生成

```c
/* 
 * @Param1 左32bit
 * @Param2 右32bit
 * @return 左右交换的连接后的结果64bit
 **/
bitset<65> LRexchange(const bitset<33> &, const bitset<33> &)
```

#### PC1置换

```C
/* 
 * @Param1 输入密钥
 * @Param2 输出PC1置换结果
 * @Param3 输出迭代中的C
 * @Param4 输出迭代中的D
 **/
void DES::PC1permutation(const bitset<65>,bitset<57>& , bitset<29>&,bitset<29>&)
```

#### 迭代左移

```c
/* 
 * @Param1 输入c
 * @Param2 输入d
 * @Param3 输出子密钥数组
 **/
void DES::iterateLS(const bitset<29>& , const bitset<29>& , bitset<49> [])
```

##### 循环左移

```c
/* 
 * @Param1 原始bitset
 * @Param2 循环左移位数
 * @return 输出bitset
 **/
bitset<29> leftShift(const bitset<29>, int)
```

##### PC2置换

```c
/* 
 * @Param1 输入c
 * @Param2 输入d
 * @return 输出置换结果
 **/
bitset<49> DES::PC2permutation(const bitset<29>&, const bitset<29>&) 
```

### IP置换

```c
/* 
 * @Param1 输入置换前bitset
 * @Param2 输出置换后左边32bit
 * @Param3 输出置换后右边32bit
 **/
IPpermutation(const bitset<65> & origin, bitset<33> & left, bitset<33> & right)
```

### 16次迭代

```c
/* 
 * @Param1 输入IP置换后左边
 * @Param2 输入IP置换后右边
 * @return 输出16次迭代后结果
 **/
bitset<65> iterateT(const bitset<33> & left, const bitset<33> & right)
```

#### 1) feistel函数

```c
/* 
 * @Param1 输入IP置换后左边
 * @Param2 输入子密钥
 * @return 输出经过feistel(包含下面1~6步的结果)
 **/
bitset<33> feistel(const bitset<33> lastRight, const bitset<49> key)
```

##### 1. E扩展

```c
/* 
 * @Param1 输入扩展前
 * @return 输出1扩展后
 **/
 bitset<49> eExpansion(const bitset<33>)
```

##### 2. eResult和子密钥进行异或运算

##### 3. 将SBox输入的内容分为8组

```c
/* 
 * @Param1 输入e扩展的结果
 * @Param2 输出分组后的每个元素为6bit的数组
 **/
 void seperateeExpansion(const bitset<49>, bitset<7>[])
```

##### 4. 输入八个S-Box进行6-4转换

```c
/* 
 * @Param1 输入分组后的e扩展结果
 * @Param2 输出经过8个sBox进行6-4转换后的结果
 **/
void sBoxOuput(const bitset<7> [], bitset<5> [])
```

##### 5. 连接

```c
/* 
 * @Param1 sBox的输出结果8个4bit
 * @return 将8个4bit连接的结果
 **/
bitset<33> DES::assemblySBoxOuput(const bitset<5> sBoxResult[])
```

##### 6. P置换

```c
/* 
 * @Param1 置换前
 * @return 置换后结果
 **/
bitset<33>Ppermutation(const bitset<33> )
```

#### 2) 左右交换

```c
/* 
 * @Param1 原来左边
 * @Param2 原来右边
 * @return 左右交换后的结果
 **/
bitset<65> LRexchange(const bitset<33> &, const bitset<33> &)
```

### IP逆置换

```c
/* 
 * @Param1 置换前
 * @return 置换后结果
 **/
bitset<65> DES::inverseIPpermutation(const bitset<65>& origin)
```

## 数据结构

本次最重要的数据结构为bitset，该数据结构的特点为可以将bit串像数组一样可以用下标进行访问，但不同之处在于bitset在输出时是从右向左输出（即最后边为第0位），但其左右移顺序并不能相反。因此在debug的过程中需要适应从右往左输出以及将子密钥生成步骤中的左移改为对bitset的右移。

## 编译运行结果

### 加密和解密

![1541224631880](C:\Users\Sherry\AppData\Roaming\Typora\typora-user-images\1541224631880.png)

并获得存储密文的文件：

![1541224690871](C:\Users\Sherry\AppData\Roaming\Typora\typora-user-images\1541224690871.png)

> 在输入错误密钥的时候有时会出现由于错误解密后仍然为乱码，字符卡住无法显示的问题，会导致之后的步骤无法正常运行。

### 直接解密

一般情况下只能获得密文文件，并不会和加密住在一起操作。

![1541224801767](C:\Users\Sherry\AppData\Roaming\Typora\typora-user-images\1541224801767.png)

结果和加密后解密相同。

