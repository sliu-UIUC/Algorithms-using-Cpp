/*
 *  * shortestCycle.h
 *   *
 *    *  Created on: Feb 18, 2018
 *     *      Author: james
 *      */

#ifndef SHORTESTCYCLE_H_
#define SHORTESTCYCLE_H_

#include <vector>
#include <algorithm>
#include <cmath>
#include <iostream>
#include <cmath>
#include <cstdlib>
#include <unordered_map>

using namespace std;

int shortestCycleHelper(int s, int c, const vector<vector<int>> &connects, vector<std::unordered_map<int, int>> &container) {
	auto r = container[c].find(s);
	if (r!= container[c].end()) {
		return r -> second;
	} else {
		int bestSolution = 100000000;
		int tmp = s& ~(1<<c);
		for (int j = 1; j < connects.size(); ++j){
			if (j!= c && s & (1<<j)) {
				bestSolution = min(bestSolution, shortestCycleHelper(tmp,j,connects,container) + connects[j][c]);
			}
		}
		container[c][s] = bestSolution;
		return bestSolution;
	}
}

int shortestCycle(const vector<vector<int>> &connects) {
	int size = connects.size();
	vector<std::unordered_map<int, int>> tmp(size);
	for(int i = 1; i < size; ++i) {
		tmp[i][1<<i] = connects[0][i];
	}
	int s = 0;
	for(int i = 1; i < size; ++i){
		s |= 1<<i;
	}
	int bestSolution = 1000000000;

	for (int i = 1; i < size; ++i) {
		bestSolution = min(bestSolution, shortestCycleHelper(s, i, connects,tmp) + connects[i][0]);
	}
	return bestSolution;
};

#endif /* SHORTESTCYCLE_H_ */
