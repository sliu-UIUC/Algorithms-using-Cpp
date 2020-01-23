#include <thread>
#include <algorithm>
#include <vector>
using namespace std;

template<typename T>
void mergeHelper(vector<T> &v, int n) {
	if(n < 5) {
		vector<T> fstHalf;
		vector<T> sndHalf;
		auto tmp = v.begin();
		for(int i=0; i<v.size()/2; ++i) {
			fstHalf.push_back(*tmp);
        		++tmp;
      		}
		for(int i=v.size()/2; i<v.size(); ++i) {
			sndHalf.push_back(*tmp);
			++tmp;
		}
		thread t (mergeHelper<T>, ref(fstHalf), n+1); 
		//mergeHelper(sndHalf, n+1);
		thread t1(mergeHelper<T>, ref(sndHalf), n+1);
		t.join(); 
		t1.join();
		merge(fstHalf.begin(),fstHalf.end(),sndHalf.begin(),sndHalf.end(),v.begin());
	} else {
		sort(v.begin(), v.end());
	}
}

template<typename T>
void pmergesort(vector<T> &v) {
	vector<T> fstHalf;
	vector<T> sndHalf;
	auto tmp = v.begin();
	for(int i=0; i<v.size()/2; ++i){
		fstHalf.push_back(*tmp);
   		++tmp;
	}
	for(int i=v.size()/2; i<v.size(); ++i){
		sndHalf.push_back(*tmp);
		++tmp;
	}

	thread t (mergeHelper<T>, ref(fstHalf), 1);
	//mergeHelper(sndHalf, 1);
	thread t1 (mergeHelper<T>, ref(sndHalf), 1);
	t.join();
	t1.join();
 	merge(fstHalf.begin(), fstHalf.end(), sndHalf.begin(), sndHalf.end(), v.begin());
}
