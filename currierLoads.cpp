#include <vector>
#include <tuple>
#include <algorithm>
#include <cmath>
#include <queue>
#include <utility>
#include <climits>
using namespace std;

int c(int u, int v, const vector<tuple<int,int,int>>& capacities){
  for (auto edge : capacities){
    if ( get<0>(edge)==u && get<1>(edge)==v ) return get<2>(edge);
  }
  return -1;
}

tuple<int, vector<int>> bfs(vector<vector<int>>& c, vector<vector<int>>& e, vector<vector<int>>& f, int t){
	int s = 0;
  	int n = c.size();
  	vector<int> p(n, -1);
  	p[s] = -2;
  	vector<int> m(n, 0);
  	m[s] = INT_MAX;
  	queue<int> q;
  	q.push(s);
  	while (q.size() > 0){
  		int u = q.front();
    		q.pop();
    		for (auto v : e[u]){
      			if (c[u][v] - f[u][v] > 0 && p[v] == -1){
        			p[v] = u;
        			m[v] = min(m[u], c[u][v] - f[u][v]);
        			if (v != t){
        				q.push(v);
        			}else{
        				return tuple<int, vector<int>>(m[t], p);
        			}
      			}
    		}
  	}
	return tuple<int, vector<int>> (0, p);
}

vector<tuple<int,int,int>> courierLoads(const vector<int>& orders, const vector<tuple<int,int,int>>& capacities){
	int numNodes = orders.size();
 	vector<vector<int>> cap(numNodes+1, vector<int>(numNodes+1, -1));
  	for (auto tup : capacities) cap[get<0>(tup)][get<1>(tup)] = get<2>(tup);
  	for (int i = 0; i < numNodes; ++i) cap[i][numNodes] = orders[i];
  	vector<vector<int>> neighbors;
  	for (int i = 0; i < numNodes; ++i){
  		vector<int> tmp;
    		for (int j = 0; j < numNodes; ++j){
      			if (cap[i][j] != -1) tmp.push_back(j);
    		}
    		tmp.push_back(numNodes);
    		neighbors.push_back(tmp);
  	}
	int maxFlow = 0;
  	vector<vector<int>> f(numNodes+1, vector<int>(numNodes+1, 0));
  	while (true){
 		auto tup = bfs(cap, neighbors, f, numNodes);
    		auto m = get<0>(tup);
    		auto P = get<1>(tup);
    		if (m == 0) break;
    		maxFlow += m;
    		auto v = numNodes;
    		while (v != 0){
          		auto u = P[v];
      			if (cap[u][v] >0){
        			f[u][v] += m;
      			}else{
        			f[v][u] -= m;
      			}
      			v = u;
    		}
    	}
  	int orderSum=0;
  	for (auto num : orders) orderSum += num;
  	vector<tuple<int,int,int>> emptyRet;
  	if (orderSum > maxFlow) return emptyRet;
  	vector<tuple<int,int,int>> ret(capacities);
  	for (auto i = 0; i < ret.size(); ++i){
    		get<2>(ret[i]) = f[get<0>(ret[i])][get<1>(ret[i])];
  	}
  	return ret;
} 
