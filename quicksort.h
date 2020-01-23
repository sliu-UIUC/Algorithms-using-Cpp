//Shiyu Liu, Pledged.

#ifndef QUICKSORT_H_
#define QUICKSORT_H_

#include <vector>



template <typename T> void swap(T& a, T& b) {
	T tmp = a;
	a = b;
	b = tmp;
}

template<typename T,typename C> T myPartition(T begin, T end, const C &lt){
    T tmp = end-1;
    T pos = begin;
    for(auto j = begin;j != end; ++j ){
    	if (lt(*j,*tmp)){
    		swap(*pos,*j);
    		pos++;
    	}
    }
    swap(*pos,*tmp);
    return pos;
}

template<typename T,typename C> void quicksort(T begin, T end,const C &lt){
	if(end-begin > 1){
		T p = myPartition(begin, end, lt);
		quicksort(begin, p, lt);
		quicksort(p+1, end, lt);
    }
}


#endif /* QUICKSORT_H_ */
