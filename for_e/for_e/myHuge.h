#pragma once
#include<vector>
#include<string>
#include<iostream>
using namespace std;
class myHuge
{
private:
	int intnum;  //整数长度
	int decnum;  //小数长度
	int sign;     //符号位，0:x>=0,1:x<0
	vector<int> intpart;  //整数部分
	vector<int> decpart;  //小数部分
public:
	myHuge();
	myHuge(int num);   //整数生成myHuge
	myHuge(double num);  //小数生成myHuge
	~myHuge();

	void zero();     //为0；

	//返回类的参数内容
	int Intsize();
	int Decsize();
	int Sign();
	vector<int> Intpart();
	vector<int> Decpart();

	//从外部改变类的参数；
	void setsign(int s);
	void setint(vector<int> i);
	void setdec(vector<int> d);

	//四则运算重载
	myHuge& operator=(const myHuge& n);
	myHuge operator+(const myHuge& n);
	myHuge operator-(const myHuge& n);
	myHuge operator*(const myHuge& n);
	myHuge operator/(const myHuge& n);

	//判断是否为0
	bool iszero();

	int compare(string str1, string str2);

	//字符串算整数四则运算，便于调用
	string add_str(string str1, string str2);
	string sub_str(string str1, string str2);
	string mul_str(string str1, string str2);
	string div_str(string str1, string str2, int flag);

	//类中所用的四则运算
	static void myAdd(const myHuge& x1, const myHuge& x2, myHuge& sum);
	static void mySub(const myHuge& x1, const myHuge& x2, myHuge& sub);
	static void myMul(const myHuge& x1, const myHuge& x2, myHuge& mul);
	static void myDiv(const myHuge& x1, const myHuge& x2, myHuge& div,int n);  //n为保留小数位数

	//以字符串形式显示数的内容
	string myShow();
};
