//Shiyu, Pledged. 

template<typename T>
class DisjointSet {
    private: 
    	T data;
	DisjointSet *parent;
	int rank;

	DisjointSet *findSet() {
		if(parent != this) {
			parent = parent->findSet();	
		}
		return parent;
	};
	void linkerFunction(DisjointSet *x, DisjointSet *y){
		if((x->rank) > (y->rank)){
			y->parent = x;
		}
		else{
			x->parent = y;
			if(x->rank == y->rank){
				y->rank = y->rank+1;
			}
		} 
	};

    public:
        DisjointSet(const T &data) {
        	this->data = data;
        	this->parent = this;
        	rank = 0;
        };
        void unionSets(DisjointSet &ds) {			
        	linkerFunction(findSet(),ds.findSet());
        }
	const T &getMarker(){
		return findSet() -> data ;
	}
};

