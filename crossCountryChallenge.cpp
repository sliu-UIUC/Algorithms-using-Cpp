// Shiyu, Pledged 


#include <vector>
#include <tuple>
#include <cmath> 
#include <iostream>
#include <algorithm>

using namespace std; 

vector<vector<int>> createMatrix(const vector<vector<int>>& difficulties) {
	vector<vector<int>> m(difficulties);
 	int n = difficulties.size();
 	for (int i=0;i<n;++i){
    		for (int j=0;j<n;++j){
      			if (i==j || difficulties[i][j]>=1000000000) m[i][j] = -1;
			else m[i][j] = i;
    		}
  	}
  	return m;
}

tuple<vector<vector<int>>, vector<vector<int>> > crossCountryChallenge(const vector<vector<int>> &difficulties) {
	int n = difficulties.size();
  	vector<vector<int>> m(createMatrix(difficulties));
  	vector<vector<int>> d(difficulties);
  	for (int x=0; x<n; ++x){
    		vector<vector<int>> dx(d);
    		vector<vector<int>> mx(m);
    		for (int i=0;i<n;++i){
      			for (int j = 0;j<n;++j){
        			dx[i][j] = min(d[i][j], d[i][x]+d[x][j]);
        			if (d[i][j]>(d[i][x] + d[x][j])) mx[i][j] = m[x][j];
      			}
    		}
    		d = dx;
    		m = mx;
  	}
  	return tuple<vector<vector<int>>, vector<vector<int>>> (d, m);
}
