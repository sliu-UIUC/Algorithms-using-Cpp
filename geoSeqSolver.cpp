//Shiyu Liu, Pledged

#include <algorithm>
#include <cmath>
#include <iostream>
#include <cstdio>
#include <iomanip>

using namespace std;

double geometricSeq (int k, double r) {
	if(k==1) {
		return 897.0;
	} else {
		return (900-3*k)*pow(r,k-1) + geometricSeq(k-1,r);
	}
	return 0;
}

double solver(int k, double num, double start, double end) {
	double predict = (start + end)/ (2.0);
	double result = geometricSeq(k, predict);
	if((end-start)<0.00000000000005) {
		return predict;
	} else if (result < num) {
		return solver(k,num,start, predict);
	} else {
		return solver(k,num,predict,end);
	}
}

int main() {
	//cout<<geometricSeq(5000,0)<<endl;
	//cout<<geometricSeq(5000,1.2)<<endl;
	cout<<std::setprecision(13)<<solver(5000,-600000000000.0,0.0,1.2)<<endl;
}
