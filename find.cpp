#include <iostream>
#include <algorithm>
#include <cmath>
#include <vector>
#include "order.h"

using namespace std;

int main() {
	std::vector<int> v{3,2,1,6,5,0};
	cout<<findNth(v,3, myFunc);
}
