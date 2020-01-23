/*
 *  * order.h
 *   *
 *    *  Created on: Jan 1, 2018
 *     *      Author: james
 *      */

#ifndef PROBLEM_SET_1_ORDER_H_
#define PROBLEM_SET_1_ORDER_H_

#include <vector>
#include <algorithm>
#include <utility>
#include <iostream>
#include <ostream>

template<typename T,typename C>
T &findNth(std::vector<T> &data,int index,const C &comp) {
	auto lambda = [&comp] (T &a, T &b) {if (comp(a,b)<0) {return true;} else {return false;}};
	std::sort(data.begin(),data.end(),lambda);
	return data[index];
}


#endif /* PROBLEM_SET_1_ORDER_H_ */
