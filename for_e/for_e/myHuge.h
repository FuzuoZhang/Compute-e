#pragma once
#include<vector>
#include<string>
#include<iostream>
using namespace std;
class myHuge
{
private:
	int intnum;  //��������
	int decnum;  //С������
	int sign;     //����λ��0:x>=0,1:x<0
	vector<int> intpart;  //��������
	vector<int> decpart;  //С������
public:
	myHuge();
	myHuge(int num);   //��������myHuge
	myHuge(double num);  //С������myHuge
	~myHuge();

	void zero();     //Ϊ0��

	//������Ĳ�������
	int Intsize();
	int Decsize();
	int Sign();
	vector<int> Intpart();
	vector<int> Decpart();

	//���ⲿ�ı���Ĳ�����
	void setsign(int s);
	void setint(vector<int> i);
	void setdec(vector<int> d);

	//������������
	myHuge& operator=(const myHuge& n);
	myHuge operator+(const myHuge& n);
	myHuge operator-(const myHuge& n);
	myHuge operator*(const myHuge& n);
	myHuge operator/(const myHuge& n);

	//�ж��Ƿ�Ϊ0
	bool iszero();

	int compare(string str1, string str2);

	//�ַ����������������㣬���ڵ���
	string add_str(string str1, string str2);
	string sub_str(string str1, string str2);
	string mul_str(string str1, string str2);
	string div_str(string str1, string str2, int flag);

	//�������õ���������
	static void myAdd(const myHuge& x1, const myHuge& x2, myHuge& sum);
	static void mySub(const myHuge& x1, const myHuge& x2, myHuge& sub);
	static void myMul(const myHuge& x1, const myHuge& x2, myHuge& mul);
	static void myDiv(const myHuge& x1, const myHuge& x2, myHuge& div,int n);  //nΪ����С��λ��

	//���ַ�����ʽ��ʾ��������
	string myShow();
};
