/**  myHuge is a class to describe a long integer or decimal ,
include the int_part and dec_part of ,also with the sign 
(0 for positive number , 1 for negative number��.
 /**/
#include "myHuge.h"
#include "math.h"
myHuge::myHuge()
{
	zero();   //zero for default;
}

myHuge::myHuge(int num) {   //���캯����������
	zero();
	if (num < 0) {
		sign = 1;
		num = 0 - num;
	}
	string temp = to_string(num);
	if (temp[0] == '-') temp.erase(0, 1);
	intnum = temp.size();
	intpart.resize(intnum);
	int i;
	for (i = intnum - 1; i >= 0; i--) {
		intpart[i] = temp[i] - '0';
	}
}

myHuge::myHuge(double num) {  //���캯����С����
	zero();
	if (num < 0) {
		sign = 1;
		num = 0 - num;
	}
	string temp = to_string(num);
	int i;
	int ss=temp.size();
	for (i = ss - 1; i >= 0; i--) {
		if (temp[temp.size()-1] == '0') temp.erase(temp.size()-1, 1);
		else break;
	}
	intnum = temp.find('.');
	decnum = temp.size() - intnum - 1;
	intpart.resize(intnum);
	decpart.resize(decnum);
	for (i =0; i <intnum; i++) {
		intpart[i] = temp[i] - '0';
	}
	for (i = intnum+1; i<temp.size() ; i++) {
		decpart[i-intnum-1] = temp[i] - '0';
	}
}

myHuge::~myHuge()
{
}

void myHuge::zero() {   //Ĭ�Ϲ��캯��Ϊ0
	intnum = 1;
	decnum = 0;
	sign = 0;
	vector<int> temp(1, 0);
	intpart = temp;
	decpart.clear();
}

int myHuge::Intsize() {  //�����������ֳ���
	return intnum;
}

int myHuge::Decsize() { //����С�����ֳ���
	return decnum;
}

int myHuge::Sign() {  //���ط���
	return sign;
}

vector<int> myHuge::Intpart() {  //�����������ֵ�vector��
	return intpart;
}

vector<int> myHuge::Decpart() {   //����С�����ֵ�vector��
	return decpart;
}

void  myHuge::setsign(int s) {   //���÷���
	if(s==0 ||s==1)  sign = s;    //���������
	else {
		if (s > 0) s = 0;   //�����0��1  s>0:sign=0;  s<0:sign=1;
		else s = 1;
	}
}

void  myHuge::setint(vector<int> i) {  //������������
	intpart = i;
	intnum = intpart.size();
}

void  myHuge::setdec(vector<int> d) {   //����С������
	decpart = d;
	decnum = decpart.size();
}

void  myHuge::myAdd(const myHuge &x1, const myHuge& x2, myHuge& sum) {  //�ӷ�����
	int sum_decnum;
	int sum_sign;
	vector<int> sum_decpart;
	vector<int> a = x1.decpart;
	vector<int> b = x2.decpart;
	vector<int> c = x1.intpart;
	vector<int> d = x2.intpart;
	int i, j;
	if (x1.sign == x2.sign) {  //������ͬ
		sum_sign = x1.sign;
		//��С��λ��
		if (a.size() < b.size()) {   //ʹa���
			swap(a, b);
		}
		int temp;
		int c_up = 0; //��λ��
		for (i = b.size() - 1; i >= 0; i--) {
			temp = a[i] + b[i] + c_up;
			c_up = temp / 10;  //��λ��
			a[i] = temp % 10;          //�������a;
		}
		//��������
		if (c.size() < d.size()) {
			swap(c, d);   //c ���
		}
		for (i = c.size() - 1, j = d.size() - 1; j >= 0; i--, j--)
		{
			temp = c[i] + d[j] + c_up;
			c_up = temp / 10;  //��λ��
			c[i] = temp % 10;         //�������c;
		}
		for (; i >= 0; i--)
		{
			temp =c[i] + c_up;
			c_up = temp / 10;
			c[i] = temp % 10;
		}
		if (c_up > 0) {
			c.insert(c.begin(), c_up);
		}
	}
	
	else {             //�����෴
		sum_sign = x1.sign;
		int k = 0;  //k=0 |x1|>|x2|
		if (c.size() <= d.size()) {
			if (c.size() < d.size())  k = 1;
			else {
				if (c < d) k = 1;
				if (c > d) k = 0;
				if (c == d) {
					for (i = 0, j = 0; i < a.size() && j < b.size(); i++, j++) {
						if (b[j] > a[i]) { k = 1; break; }
						if (b[j] < a[i]) { k = 0; break; }
						}
					if (k == 0 && i == a.size() && j < b.size())  k = 1;
				}
			}
		}
		if (k == 1) {
			swap(a, b);   //ʼ��ʹa,c��ʾ����Ϊ����ֵ�������
			swap(c, d);
			sum_sign = x2.sign;
		}
		int c_down = 0;   //��λ��
		//��С����
		int max1 = (a.size() > b.size()) ? a.size() : b.size();
		if (a.size() < max1) {       ///
			a.insert(a.end(), max1, 0);  //��0��
		}
		if (b.size() < max1) {
			b.insert(b.end(), max1, 0);
		}
		for (i = max1 - 1; i >= 0; i--)
		{
			int temp = a[i] - b[i] - c_down;
			c_down = 0;
			if (temp < 0) {
				c_down = 1;
				temp = 10 + temp;
			}
			a[i] = temp;     //�������a��
		}

		//��������
		for (i = c.size() - 1, j = d.size() - 1; j >= 0; i--, j--) {
			int temp = c[i] - d[j] - c_down;
			c_down = 0;
			if (temp < 0) {
				c_down = 1;
				temp = 10 + temp;
			}
			c[i] = temp;   //�������c;
		}
		for (; i >= 0 && c_down>0 ; i--) {
			int temp = c[i] - c_down;
			c_down = 0;
			if (temp < 0) {
				c_down = 1;
				temp = 10 + temp;
			}
			c[i] = temp;
		}
	}

	//ȥ��С��β����0,���³��ȣ�
	int aa = a.size();
	for (i = aa - 1; i >= 0; i--) {
		if (a[a.size() - 1] == 0) a.pop_back();
		else break;
	}
	int cc = c.size();
	for (i = 0; i < cc - 1; i++) {
		if (c[0] == 0) c.erase(c.begin(),c.begin()+1);
		else break;
	}
	if (a.size() == 0 && c.size() == 1 && c[0] == 0)  sum_sign = 0;  //���������-0
	sum.setdec(a);
	sum.setint(c);
	sum.setsign(sum_sign);
}


void myHuge::mySub(const myHuge& x1, const myHuge& x2, myHuge& sub) {  //��������
	myHuge temp;
	temp.setdec(x2.decpart);
	temp.setint(x2.intpart);
	temp.setsign(1 - x2.sign);
	myAdd(x1, temp, sub);   //ͨ���ӷ���ʵ�ּ���
}

 int myHuge::compare(string str1, string str2) {//��ȷ���0�����ڷ���1��С�ڷ���-1
	if (str1.size()>str2.size()) return 1; //���ȳ����������ڳ���С������
	else if (str1.size()<str2.size()) return -1;
	else                              return str1.compare(str2); //��������ȣ���ͷ��β��λ�Ƚ�
}

string myHuge::add_str(string str1, string str2) {//�����ӷ�
	myHuge x1, x2;
	int i, j;
	vector<int> x1_int;
	vector<int> x2_int;
	if (str1[0] == '-') {
		x1.setsign(1);
		str1.erase(0, 1);
	}

	if (str2[0] == '-') {
		x2.setsign(1);
		str2.erase(0, 1);
	}
	x1_int.resize(str1.size());
	x2_int.resize(str2.size());

	for (i = 0; i < str1.size(); i++) {
		x1_int[i] = str1[i] - '0';
	}

	for (i = 0; i < str2.size(); i++) {
		x2_int[i] = str2[i] - '0';
	}
	x1.setint(x1_int);
	x2.setint(x2_int);
	myHuge y;
	myHuge::myAdd(x1, x2, y);
	string res;
	for (i = 0; i < y.Intsize(); i++) {
		res.append(1, char(y.Intpart()[i] + '0'));
	}
	return res;
}

string myHuge::mul_str(string str1, string str2) {
	string str;
	int i, j;
	string::size_type L1, L2;
	L1 = str1.size();
	L2 = str2.size();
	for (i = L2 - 1; i >= 0; i--) { //�ֹ��˷���ʽ
		string tempstr;
		int int1 = 0, c_up = 0, int3 = str2[i] - '0';  //int2Ϊ��λ��
		//if (int3 > 0) {
			 for (j = 1; j <= (int)(L2 - 1 - i); j++) tempstr = "0" + tempstr;
			 for (j = L1 - 1; j >= 0; j--) {
				int1 = (int3*(int(str1[j]) - '0') + c_up) % 10;
				c_up = (int3*(int(str1[j]) - '0') + c_up) / 10;
				tempstr = char(int1 + '0') + tempstr;
		    	}
		   	 if (c_up > 0) tempstr = char(c_up + '0') + tempstr;
	//	} 
		str = add_str(str, tempstr);
	}
	str.erase(0, str.find_first_not_of('0'));   //ȥ��ǰ���0
	if (str.empty()) str = "0";
	return str;
}

string myHuge::sub_str(string str1, string str2) {//��������
	str2 = "-" + str2;
	string res= add_str(str1, str2);
	return res;
}

string myHuge::div_str(string str1, string str2, int flag) {//����������flag==1ʱ,������; flag==0ʱ,��������
	string shang, yushu; //�̺�����
	int sign1 = 1, sign2 = 1;
	if (str2 == "0") {  //�жϳ����Ƿ�Ϊ0
		shang = "inf";
		yushu = "0";
		if (flag == 1) return shang;
		else         return yushu;
	}
	if (str1 == "0") { //�жϱ������Ƿ�Ϊ0
		shang = "0";
		yushu = "0";
	}

	int res = compare(str1, str2);  
	if (res<0) {
		shang = "0";
		yushu = str1;
	}
	else if (res == 0) {
		shang = "1";
		yushu = "0";
	}
	else {
		int L1, L2;
		L1 = str1.size();
		L2 = str2.size();
		string tempstr;
		tempstr.append(str1, 0, L2-1);
		for (int i = L2 - 1; i<L1; i++) { //�ֹ�������ʽ
			tempstr.append(1,str1[i]);
			tempstr.erase(0, tempstr.find_first_not_of('0'));
			if (tempstr.empty()) tempstr = "0";
			for (char ch ='9'; ch >= '0'; ch--) { //��9��0����
				string str;
				str.append(1, ch); 
				string mul = mul_str(str2, str);
				if (compare(mul , tempstr) <= 0) {  //�ҵ���
					shang = shang + ch;
					tempstr = sub_str(tempstr,mul);  //������
					break;
				}
			}
		}
		yushu = tempstr;
	}
	//ȥ��ǰ���0
	shang.erase(0, shang.find_first_not_of('0'));
	if (shang.empty()) shang = "0";
	if (flag == 1) return shang;
	else    return yushu;
}

int min(int x, int y) {    //��Сֵ
	return (x < y) ? x : y;
}

void myHuge::myDiv(const myHuge& x1, const myHuge& x2, myHuge& div,int n) {//myHuge������
	int i, j;
	myHuge fenzi = x1;
	myHuge fenmu = x2;
	string str1,str2;
	//�����ӣ���ĸ��ת��Ϊ����
	for (i = 0; i < fenzi.Intpart().size(); i++) {   
		str1.append(1, char(fenzi.Intpart()[i] + '0'));
	}

	for (i = 0; i < fenmu.Intpart().size(); i++) {
		str2.append(1, char(fenmu.Intpart()[i] + '0'));
	}

	if (fenzi.Decpart().size() > 0) {
		for (i = 0; i < fenzi.Decpart().size(); i++) {
			str1.append(1, char(fenzi.Decpart()[i] + '0'));
		}
	}

	if (fenmu.Decpart().size() > 0) {
		for (i = 0; i < fenmu.Decpart().size(); i++) {
			str2.append(1,char(fenmu.Decpart()[i]+'0'));
		}
	}
	//ȥ��ǰ���0��
	str1.erase(0, str1.find_first_not_of('0')); 
	str2.erase(0, str2.find_first_not_of('0'));

	string y;
	int mark_int; //��¼�������ֵ�ֵ��
	for (i=0 ; i<=n+1 ; i++ ) {    //���ٱ���nλС����
	    string  tt= div.div_str(str1, str2, 1);  //ѭ����������������
		y = y + tt;
		if (i == 0) {
			mark_int = y.size();
		}
		string temp= div.div_str(str1, str2, 0);
		str1 = temp +"0";
		if (str1 == "00")  break;
	}
    
	int int_sum = mark_int + fenmu.Decsize() - fenzi.Decsize();  //���������ĳ��ȣ�
	vector<int> newint; 
	vector<int> newdec;
	int new_sign;
	new_sign = fenzi.Sign() + fenmu.Sign();  //�������
	if (new_sign > 1)   new_sign = 0;
	div.setsign(new_sign);
	if (int_sum <= 0) {   //��������Ϊ0����С��0��С�����ֲ�0
		newint.push_back(0);
		int nn = -int_sum;
		string ling;
		ling.append(nn, '0');
		y = ling + y;
		for (i = 0; i < min(n,y.size()); i++)
			newdec.push_back(y[i] - '0');
	}
	else
	{
		for (i = 0; i < min(int_sum,y.size()); i++) {    //�������ֲ�Ϊ0
		newint.push_back(y[i] - '0');
		}
		for (; i < int_sum; i++)  newint.push_back(0);   //�������������Ҫ��0
		y.erase(0, int_sum);
		for (i = 0; i <(min(n,y.size())); i++) {
			newdec.push_back(y[i] - '0');
		}
	}
	int nnd = newdec.size();     
	//ȥ��С�����������ֶ����0
	for (i = nnd - 1; i >= 0; i--) {
		if (newdec[newdec.size() - 1] == 0) newdec.pop_back();
		else break;
	}
	if (newint.size() > 1) {   
		int sss = newint.size();
		for (i = 1; i < sss; i++) {
			if (newint[0] == 0) newint.erase(newint.begin(),newint.begin()+ 1);
		}
	}
	div.setdec(newdec);
	div.setint(newint);  //����nλС��
	return;
}

 void myHuge::myMul(const myHuge& x1, const myHuge& x2, myHuge& mul) { //�˷� 
	 int i, j;
	 myHuge c1 = x1;
	 myHuge c2 = x2;
	 if (c1.iszero() || c2.iszero()) {   //��һ��Ϊ0������0
		 myHuge temp;
		 mul = temp;
		 return;
	 }
	 string str1, str2;
	 //����������������˷��������е�����ת��Ϊ�ַ���
	 for (i = 0; i < c1.Intpart().size(); i++) {
		 str1.append(1, char(c1.Intpart()[i] + '0'));
	 }

	 for (i = 0; i < c2.Intpart().size(); i++) {
		 str2.append(1, char(c2.Intpart()[i] + '0'));
	 }

	 if (c1.Decpart().size() > 0) {
		 for (i = 0; i < c1.Decpart().size(); i++) {
			 str1.append(1, char(c1.Decpart()[i] + '0'));
		 }
	 }

	 if (c2.Decpart().size() > 0) {
		 for (i = 0; i < c2.Decpart().size(); i++) {
			 str2.append(1, char(c2.Decpart()[i] + '0'));
		 }
	 }
	 int decnum = c1.Decsize() + c2.Decsize();
	 string y = mul.mul_str(str1, str2);  //���������ɷּ���
	 vector<int> newdec(decnum);
	 vector<int> newint;
	 int new_sign;
	 new_sign = c1.Sign() + c2.Sign();
	 if (new_sign > 1) new_sign = 0;
	 mul.setsign(new_sign);
	 //�ֿ�������С����
	 if (y.size() <= decnum)
	 {
		 y.insert(y.begin(), decnum - y.size() + 1,'0');
	 }
	 for (i = y.size() - decnum, j = 0; i < y.size(); i++, j++) {
			 newdec[j] = y[i] - '0';
	  }
	 for (i = 0; i <y.size()-decnum; i++) {
			 newint.push_back(y[i] - '0');
	  }
	 int nnd = newdec.size();
	 for (i = nnd - 1; i >= 0; i--) {
		 if (newdec[newdec.size() - 1] == 0) newdec.pop_back();
		 else break;
	 }
	 mul.setint(newint);
	 mul.setdec(newdec);
}

string myHuge::myShow() {  //�������������ַ�����ʾ��
	string toshow;
	int i;
	if (sign == 1) toshow = "-";
	for (i = 0; i < intnum; i++) {
		toshow.append(1, char(intpart[i] + '0'));
	}
	if (decnum > 0) {
		toshow = toshow + ".";
		for (i = 0; i < decnum; i++) {
			toshow.append(1, char(decpart[i] + '0'));
		}
	}
	return toshow;
}

myHuge& myHuge::operator=(const myHuge& n) {   //���ء�="
	if (this != &n) {
		intpart = n.intpart;
		decpart = n.decpart;
		intnum = n.intnum;
		decnum = n.decnum;
		sign = n.sign;
	}
	return *this;
}

myHuge myHuge::operator+(const myHuge& n) { //���ء�+"
	myHuge y;
	myHuge::myAdd(*this, n, y);
	return y;
}

myHuge myHuge::operator-(const myHuge& n) { //���ء�-"
	myHuge y;
	myHuge::mySub(*this, n, y);
	return y;
}

myHuge myHuge::operator*(const myHuge& n) {  //���ء�*"
	myHuge y;
	myHuge::myMul(*this, n, y);
	return y;
}

myHuge myHuge::operator/(const myHuge& n) {  //���ء�/��
	myHuge y;
	myHuge::myDiv(*this, n, y,15);
	return y;
}

bool myHuge::iszero() {  //�ж��Ƿ�Ϊ0��
	if (intnum == 1 && intpart[0] == 0 && decnum == 0) return true;
	else return false;
}



