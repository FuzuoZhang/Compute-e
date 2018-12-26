#include<iostream>
#include <math.h>
#include<vector> 
#include<iomanip>
#include"myHuge.h"
using namespace std;

bool check(string str, int n) {   //检验某字符串是否在数值上大于3*10^n;
	if (str.size() < n + 1) return false;
	if (str.size() > n + 1) return true;
	if (str[0] > '3') return true;
	return false;
}

myHuge e_Taylor(int n) {   //n为精确的小数点位数；实际小数为n+1位；
	int k=1;
	myHuge yi(1);
	myHuge san(3);
	myHuge e(1);
	myHuge error_temp;
	myHuge error;
	myHuge jiecheng(1);
	string eee;
	string jiec;
	string chus;
	for (;;k++) {
		myHuge xinjiec;   //新阶乘；
		myHuge temp_k(k);
		myHuge temp(k + 1);
		myHuge temp_e;
		myHuge chu_temp;
		myHuge::myMul(jiecheng,temp_k,xinjiec);
		myHuge::myDiv(yi, xinjiec, chu_temp, n + 5);
		myHuge::myAdd(e, chu_temp,temp_e);
		jiecheng = xinjiec;
		myHuge::myMul(temp, jiecheng, error_temp);
		e = temp_e;
	    eee = e.myShow();
	    jiec = jiecheng.myShow();
	    chus = chu_temp.myShow();
		if (check(error_temp.myShow(),n+1)) break;
	}
	myHuge::myDiv(san, error_temp,error, n+2);
	string res = e.myShow();
	string Err = error.myShow();
	int  dian = res.find(".");
	string out = res.substr(0, dian+1) + res.substr(dian + 1, n);
	if (res[dian+1+n] > '4') out[out.size() - 1] += 1;
	if (e.Decsize() > n) {
		vector<int> temp = e.Decpart();
		temp.erase(temp.begin() + n+1, temp.end());
		if (temp[n] > 4) temp[n - 1] += 1;
		temp.pop_back();
		e.setdec(temp);
	}
	//return "e: " + out + "    error: " + Err;
	return e;
}

bool check_2(myHuge delta, int jingdu) {   //检验龙贝格精度是否满足要求 //
	vector<int> dec = delta.Decpart();
	vector<int> int_p = delta.Intpart();
	if (int_p.size() == 1 && int_p[0] == 0) {
		if (dec.size() < jingdu + 1) {
			if (dec.size() == 0) return true;
			return false;
		}
			int i;
		for (i = 0; i < jingdu; i++) {
			if (dec[i] != 0) return 0;
		}
		if (dec[jingdu] >= 5) return false;
		return true;
	}
	return false;
}

myHuge FhT(myHuge x, int k, int jingdu) {
	//计算复化梯形公式   f(t)=1/t  I：f(t)在1，x上的数值积分；  jingdu为结果保留小数位数；
	 //sum为最后的积分值，yi即为1，yx为x对应的函数值，qujian为（x-1） ,h_2为h/2；
	myHuge sum, n(1), yi(1), er(2), yx, qujian, h, h_2;
	int i;
	for (i = 1; i <= k; i++) {
		n = n*er;
	}
	
	qujian = x - yi; 
	myHuge::myDiv(qujian, n, h, jingdu + 3);//除法多保留5位小数；
	myHuge::myDiv(h, er, h_2, jingdu + 3);
	myHuge::myDiv(yi, x, yx, jingdu + 3);
	sum = yi + yx;
	myHuge j=n;
	j = j - yi;
	for (;!(j.iszero()) ; j=j-yi) {   
		myHuge xk = yi + j*h;
		myHuge temp;
		myHuge::myDiv(yi, xk, temp, jingdu + 5);
		myHuge yy = er*temp;
		sum = sum + yy;
	}
	sum = sum*h_2;
	vector<int> xiaoshu;
	xiaoshu = sum.Decpart();
	if (xiaoshu.size() > jingdu) {
		xiaoshu.erase(xiaoshu.begin()+jingdu, xiaoshu.end());   //使输出小数位数为jingdu，或者有理数；
		if (sum.Decpart()[jingdu] > 4)  xiaoshu[xiaoshu.size() - 1] += 1;
		sum.setdec(xiaoshu);
	}
	return sum;
}

myHuge mm(int m) {  //返回4的m次幂
	myHuge si(4),res(1);
	int i;
	for (i = 1; i <= m; i++) {
		res = res*si;
	}
	return res;
}

myHuge JiFen(myHuge x, int jingdu) {  //用数值积分方法求lnx;    (龙贝格） //jingdu为保留小数位数； 
	myHuge yi(1);
	vector<vector<myHuge>> T; //龙贝格上三角T表；
	vector<myHuge> T0; //第一列；
	myHuge T00=FhT(x,0,jingdu+3);  //存储精度高3；
	T0.push_back(T00);
	T.push_back(T0);
	int i = 1,j = 0;
	myHuge c1,c2, Tij;
	while (1) {
		myHuge T0i = FhT(x, i, jingdu + 3);  //增加一个梯形积分
		vector<myHuge> Ti;
		T.push_back(Ti);          //增加一列
		T[0].push_back(T0i);   
		for (j = 1; j <= i; j++) {
			         //Tij表示T(i-j)j;
			myHuge sim = mm(j);
			myHuge::myDiv(sim, sim - yi, c1, jingdu + 3);  //存储精度比精度要求高三个量级
			myHuge::myDiv(yi, sim - yi, c2, jingdu + 3);
			int lo = T[j - 1].size();
			while (T[j-1].size() > 2) {
				T[j - 1].erase(T[j - 1].begin(), T[j - 1].begin()+1);
			}
			Tij = c1*T[j - 1][1] - c2*T[j - 1][0];
			
			vector<int> decc = Tij.Decpart();
			if(decc.size()>jingdu+3)
			decc.erase(decc.begin() + jingdu + 3, decc.end());
			Tij.setdec(decc);
			T[j].push_back(Tij); 
		}
	    myHuge delta = T[i-1][0] - T[i][0];
		if (check_2(delta, jingdu)) break;    //判断是否达到精度，是则退出迭代
		i++;
	}
	myHuge res = T[i][0];
	vector<int> dec=res.Decpart();   //按照要求的小数点位数返回
	if (dec.size() > jingdu) {
		dec.erase(dec.begin()+jingdu, dec.end());
		res.setdec(dec);
	}
	return res;
}

myHuge e_LBG(int jingdu) {  //  龙贝格+插值 求e  jingdu为保留的小数位数
		int i,j;
		vector<myHuge> eneib;  //e附近的11个点
		vector<myHuge> jifen;  //上面11个点的积分值；
		for (i = 0; i < 4; i++) {   //四个插值结点
			double temp = 2.68 + 0.02*i;
			myHuge ne(temp);
			eneib.push_back(temp);
		}

		for (i = 0; i < 4; i++) {   //求插值节点的函数值
			myHuge temp = JiFen(eneib[i], jingdu + 2);
			jifen.push_back(temp);
		}

		myHuge yi(1),res(0);   //res为结果
		for (i = 0; i < 4; i++) {     //插值计算
			myHuge li(1);
			for (j = 0; j < 4; j++) {
				if (j == i) continue;
				myHuge bi;
				myHuge::myDiv(yi - jifen[j], jifen[i] - jifen[j],bi, jingdu + 2);
				li = li*bi;
				if (li.Decsize() > jingdu * 2) {
				vector<int> lll=li.Decpart();
				lll.erase(lll.begin()+jingdu*2,lll.end());
				li.setdec(lll);
				}
			}
				res = res + li*eneib[i];
		}
		if (res.Decsize() > jingdu + 1) {   //去除尾部多余的小数位 
			vector<int> rrr = res.Decpart();
			rrr.erase(rrr.begin() + jingdu + 1, rrr.end());
			if (rrr[jingdu] > 4) {
				rrr[jingdu - 1] += 1;
			}
			rrr.pop_back();
			res.setdec(rrr);
		}
		return res;
}

myHuge e_cwf(int jingdu) {   //常微分方程求解---改进欧拉法
	int x=jingdu/2+1;
	myHuge yi(1),er(2),shi(10),h(1),n;
	myHuge res(1);
	int i;
	for (i = 1; i <=x; i++) {
		myHuge temp;
		myHuge::myDiv(h, shi, temp, x);
		h = temp;
	}
	myHuge c1, c2;
	c1 = er + h;
	c2 = er - h;
	myHuge h2;
	myHuge::myDiv(c1, c2, h2, jingdu*2);  //h2即为每次迭代乘上的系数(2+h)/(2-h)
	myHuge::myDiv(yi, h, n, 1);
	for (; !(n.iszero()); n = n - yi) {  //迭代n次
			res = res*h2;
			if (res.Decsize() > 2 * jingdu) {
				vector<int> temp = res.Decpart();
				temp.erase(temp.begin() + jingdu * 2, temp.end());
				res.setdec(temp);
			}
	}
	if (res.Decsize() > 1+ jingdu) {   //去除多余小数位
		vector<int> temp = res.Decpart();
		temp.erase(temp.begin() + 1+ jingdu, temp.end());
		if (temp[jingdu] > 4) temp[jingdu - 1] += 1;
		temp.pop_back();
		res.setdec(temp);
	}
	return res;   //返回结果
}

int main() {
	int jingdu=7;   //保留小数位数； 	
	cout <<"Taylor:         "<< e_Taylor(jingdu).myShow()<< endl<<endl;  
	cout <<"数值积分+插值:   " << e_LBG(jingdu).myShow() << endl<<endl;
	cout << "常微分方程数值解:" << e_cwf(jingdu).myShow() << endl<<endl;
	system("pause");
	return 0;
}