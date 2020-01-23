/*
 *  * drivingLegal.cpp
 *   *
 *    *  Created on: Mar 1, 2018
 *     *      Author: james
 *      */

#include <vector>
#include <set>
#include <queue>
#include <unordered_map>
#include <iostream>

using namespace std;
using std::priority_queue;

struct Node{
  Node* parent;
  int disc;
  int fr;
  string color;
  int location;
  Node(int l):parent(nullptr), disc(0), fr(0),color("white"),location(l) {}
};

struct func { bool operator()(Node* x, Node* y){ return (x->fr < y->fr);}};

void depthFirstSearchVisit(const vector<vector<int>>& roadTo, Node* u, int& time, vector<Node*>& nodes){
  ++time;
  u->disc = time;
  u->color = "gray";
  vector<int> tmp(roadTo[u->location]);
  for (auto iter:tmp){
    Node* v(nodes[iter]);
    if (v->color == "white"){
      v->parent = u;
      depthFirstSearchVisit(roadTo, v, time, nodes);
    }
  }
  u->color = "black";
  ++time;
  u->fr = time;
}

vector<Node*> depthFirstSearch(const vector<vector<int>>& roadTo) {
  vector<Node*> n;
  for (auto i = 0; i < roadTo.size(); ++i) n.push_back(new Node(i));

  int time = 0;
  for (auto i = 0; i < roadTo.size(); ++i){
    Node* u(n[i]);
    if (u->color == "white") depthFirstSearchVisit(roadTo, u, time, n);
  }
  return n;
}

vector<Node*> topoSort(const vector<vector<int>>& roadTo, vector<Node*>& nodes){
  for (auto i : nodes){
    i->color = "white";
    i->parent = nullptr;
  }
  int time = 0;
  priority_queue<Node*, vector<Node*>, func> findMax;
  for (auto i = nodes.begin(); i != nodes.end(); ++i) findMax.push(*i);
  int sz = findMax.size();
  for (auto i = 0; i < sz; ++i){
    Node* u(findMax.top());
    findMax.pop();
    if (u->color == "white") depthFirstSearchVisit(roadTo, u, time, nodes);
  }
  return nodes;
}

vector<vector<int>> transpose(const vector<vector<int>>& roadTo){
  vector<vector<int>> ret;
  for (auto i = 0; i < roadTo.size(); ++i){
    vector<int> tmp;
    ret.push_back(tmp);
  }
  for (auto i = 0; i < roadTo.size(); ++i){
    for (auto j = 0; j < roadTo[i].size(); ++j){
      int val = roadTo[i][j];
      ret[val].push_back(i);
    }
  }
  return ret;
}


vector<set<int>> drivingLegal(const vector<vector<int>>& roadTo){
  vector<set<int>> clusters;
  vector<Node*> nodes( depthFirstSearch(roadTo) );
  vector<vector<int>> tNodes(transpose(roadTo));
  vector<Node*> topoNodes( topoSort(tNodes, nodes) );

  unordered_map<int,set<int>*> myMap;
  for (auto n:nodes){
    if (!n->parent){
      myMap.insert(pair<int,set<int>*>( n->location, new set<int>({n->location}) ));
    }
  }
  for (auto n:nodes){
    if (n->parent){
      Node* rover(n->parent);
      while(rover->parent) rover=rover->parent;
      set<int>* mySet((*myMap.find(rover->location)).second);
      mySet->insert(n->location);
    }
  }
  for (auto i:myMap){
    clusters.push_back(*i.second);
  }
  return clusters;
}

