#include <vector>
#include <future>

using namespace std;

vector<double> rowMult (const vector<double> &ar, const vector<vector<double>> &b) {
	vector<double> tmp (b[0].size(),0);
	for(int i=0;i<b[0].size();i++) {
		for(int j=0;j<ar.size();j++){
			tmp[i] += ar[j]*b[j][i];
		}
	}
	return tmp;
}

vector<vector<double>> pMatrixMult(const vector<vector<double>> &a,const vector<vector<double>> &b) {
	vector<vector<double>> result;
	vector<future<vector<double>>> tmp;
	for(int i=0;i<a.size();++i) {
		tmp.push_back(async(std::launch::async, rowMult, ref(a[i]), ref(b)));
	}
	for(int j=0;j<tmp.size();++j) {
		result.push_back(tmp[j].get());
	}
	return result;
}
