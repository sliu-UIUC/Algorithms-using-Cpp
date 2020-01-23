/*
 *  * radix.h
 *   *
 *    *  Created on: Jan 27, 2018
 *     *      Author: Shiyu
 *      */

#ifndef RADIX_H_
#define RADIX_H_

#include <vector>

template <typename T, typename K>
int findMax(T begin, T end, K keyFunc){ 
	int maxElem = 0;
	for(auto iter =begin; iter!=end; iter++){
		int tmp = keyFunc(*iter);
		if(tmp>maxElem) maxElem = tmp;
	}
	return maxElem;
}

template <typename T,typename K>
void countSort(T begin, T end, K keyFunc,int num){
	int size = end-begin;
	std::vector <int> aux(10);
	std::vector <typename T::value_type> tmp(size);
	for(int i = 0;i<10;i++) { //initialize the auxiliary array
		aux[i] = 0;
	}

	for(int j = 0;j!=size;j++) { //count the occurance of each digit
		int buc = (keyFunc(*(begin+j))/num)%10;
		aux[buc] ++;
	}
	for(int m =1;m<10;m++){ //increment each slot by the number of previous slot
		aux[m] +=aux[m-1];//so that each number can be copied to the correct position
	}
	for(int n = size-1; n>=0;n--) {   //add each number to the corresponding position
		int buc = (keyFunc(*(begin+n))/num)%10;
		aux[buc]--;
		tmp[aux[buc]] = *(begin+n);
	}
	for(int z = 0;z<size;z++) { //copy the sorted data to our vector
		*(begin+z) = tmp[z];
	}
}

template<typename T,typename K>
void radixSort(T begin,T end,K keyFunc) {
	int maxElem = findMax(begin, end, keyFunc);
	for(int i = 1; maxElem/i>0;i*=10){ //based on number of digits of the largest number
		countSort(begin,end,keyFunc,i);
	}
}






#endif /* RADIX_H_ */

