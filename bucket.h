/*
 *  * bucket.h
 *   *
 *    *  Created on: Jan 27, 2018
 *     *      Author: Shiyu
 *      */

#ifndef BUCKET_H_
#define BUCKET_H_

#include <vector>
#include <algorithm>
#include "math.h"

template<typename T,typename K>
double findMax (T begin, T end, K keyFunc) {
	auto tmp = keyFunc(*begin);
	for(auto iter = begin+1;iter!=end;iter++){
		if(keyFunc(*iter)>tmp ) {
			tmp = keyFunc(*iter);
		}
	}
	return tmp;
}

template<typename T,typename K>
double findMin(T begin, T end, K keyFunc) {
	double tmp = keyFunc(*begin);
		for(auto iter = begin+1;iter!=end;iter++){
			if(keyFunc(*iter)<tmp) {
				tmp = keyFunc(*iter);
			}
		}
		return tmp;
}

template <typename T> void mySwap(T& a, T& b) {
	T tmp = a;
	a = b;
	b = tmp;
}

template<typename T,typename K>
void insertionSort (T begin, T end, K keyFunc) {
	int idx = 1;
	int size = end-begin;
	while(idx<size) {
		int j = idx;
		while(j>0){
			if(keyFunc(*(begin+j))<keyFunc(*(begin+j-1))) {
				mySwap(*(begin+j), *(begin+j-1));
			}
			j--;
		}
		idx++;
	}
}

template<typename T,typename K>
void bucketSort(T begin,T end,K keyFunc){
        int size = end-begin;
        std::vector<std::vector<typename T::value_type>> aux(size+1);
        double maxNum = findMax(begin,end,keyFunc);
        double minNum = findMin(begin,end,keyFunc);
        for(auto iter=begin;iter!=end;iter++) {
                int buc = floor(((keyFunc(*iter)-minNum)/(maxNum-minNum))*size);
                aux[buc].push_back(*iter);
        }

        for(int i=0; i<=size;i++){
                if(aux[i].size()>1) insertionSort(aux[i].begin(),aux[i].end(),keyFunc);
        }
        int idx = 0;
        for(int j=0;j<size+1;j++){
        	for(int n=0;n<aux[j].size();n++) {
        		*(begin+idx) = aux[j][n];
        		idx++;
        	}
        }
}

#endif /* BUCKET_H_ */
