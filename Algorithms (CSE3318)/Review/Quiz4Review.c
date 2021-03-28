struct tree_node{
	int count;
	char symbol;
	struct tree_node * left;
	struct tree_node * right;
}

//(sink down, swim up, insert, removeMin, buildMinHeap)

void sinkDown(struct tree_node** A,int p,int N){ //O(lgN)
    int left = 2*p; // index of left child of p
    int right = (2*p)+1; // index of right child of p
    int index=p;
    if ((left<=N)&&(A[left]->count < A[index]->count))
        index = left;
    if ((right<=N)&&(A[right]->count < A[index]->count))
        index = right;
    if (index!=p) {
        struct tree_node t1 = A[p];
        struct tree_node t2 = A[index];
        struct treeNode tt = t1;
        t1 = t2;
        t2 = tt;
        sinkDown(A,index,N);
    }
}

void swimUp(struct tree_node** A,int i){ //O(lg(N))
    while ((i>1)&&(A[i]->count<A[i/2]->count)){
        struct tree_node t1 = A[i];
        struct tree_node t2 = A[i/2];
        struct treeNode tt = t1;
        t1 = t2;
        t2 = tt;
        i = i/2 
    }
}

void insert(struct tree_node** A,struct tree_node* newKey,int* N){ //O(lg(N))
    (*N) = (*N)+1;
    int i = (*N);
    A[i] = newKey;
    while ((i>1)&&(A[i]->count < A[i/2]->count)) {
        struct tree_node t1 = A[i];
        struct tree_node t2 = A[i/2];
        struct treeNode tt = t1;
        t1 = t2;
        t2 = tt;
        i = i/2 
    }
}

struct tree_node* removeMin(struct tree_node** A, int* N){ // Θ(lgN)
    struct tree_node* min = A[1];
    A[1] = A[(*N)];
    (*N)=(*N)-1;
    sinkDown(A,1,N); 
    return min
}

void buildMinHeap(struct tree_node** A,int N){ //Θ(N)
    for (int p = N/2; p>=1; p--)
        sinkDown(A,p,N);
}
