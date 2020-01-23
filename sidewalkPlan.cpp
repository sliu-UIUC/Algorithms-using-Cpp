/*
 *  *  * drivingLegal.cpp
 *   *   *
 *    *    *  Created on: Mar 2, 2018
 *     *     *      Author: james
 *      *      */

#include <algorithm>
#include <vector>
#include <cmath>
#include <tuple>
#include <limits>
#include "DisjointSet.h" 

using namespace std;

double distance(double x1, double y1, double x2, double y2){
	double xDis = pow((x2 -x1), 2);
	double yDis = pow((y2 -y1), 2);
	double totalDis = sqrt(xDis+yDis);
	return totalDis;
}

bool operator<(tuple<double,tuple<int,int>> &a, tuple<double,tuple<int,int>> &b) {return get<0>(a) < get<0>(b);}

tuple<double,vector<tuple<int,int> > > sidewalkPlan(const vector<tuple<double, double> > &buildingLocations){
	double sum = 0; //total distance 
	vector<DisjointSet<int>*> ds;
	for (auto i=0; i<buildingLocations.size(); ++i) { // make disjoint set
		auto tmp = new DisjointSet<int>(i); //for each vertex
		ds.push_back(tmp);
	}
	vector<tuple<double,tuple<int,int>>> edges;//list of edges, with each edge a tuple with the first argument
	for(int i = 0; i<ds.size();++i) { //the distance between two vertices and second argument the two vertices
		for(int j = i+1;j<ds.size();++j){
			auto v1 = buildingLocations[i];
			auto v2 = buildingLocations[j];
			double dis = distance(get<0>(v1), get<1>(v1),get<0>(v2), get<1>(v2));
			edges.push_back(make_tuple(dis, make_tuple(i, j)));
		}
	}
	sort(edges.begin(), edges.end()); //sort edges by length
	vector<tuple<int,int>> A; //A list of connected locations
	for(auto l = 0; l < edges.size();++l){
		auto location1 = get<0>(get<1>(edges[l]));
		auto location2 = get<1>(get<1>(edges[l]));
		if((ds[location1])->getMarker()!= (ds[location2])->getMarker()) {
			A.push_back(get<1>(edges[1]));
			sum += get<0>(edges[1]);
			(*ds[location1]).unionSets(*ds[location2]);
		} 
	}
	return make_tuple(sum, A);
}
