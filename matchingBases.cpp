#include <algorithm>
#include <cstdlib>
#include <vector>
#include <iostream>
#include <utility>
#include <string>

using namespace std;

bool ifMatchingBases(char a, char b){
	if((a=='C'&&b=='G')||(a=='G'&&b=='C')||(a=='U'&&b=='A')||(a=='A'&&b=='U')) return true;
	else return false;
}

int matchingHelper(const string &strand, int i, int j, vector<vector<int>> &lookup){
	int count = 0;
	if(lookup[i][j] != -1) return lookup[i][j];
	if(i <= j) return 0;
	if(ifMatchingBases(strand[i], strand[j])) count = 1 + matchingHelper(strand, i-1, j+1, lookup);
	else count = max(matchingHelper(strand, i-1,j, lookup),matchingHelper(strand, i, j+1, lookup));
	lookup[i][j] = count;
	return count;
}

int matchingBases(string strand) {
	vector<vector<int>> lookup(strand.size(), vector<int>(strand.size(),-1));
	return matchingHelper(strand,strand.size()-1,0, lookup);
}
