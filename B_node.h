#ifndef B_Tree_B_node_h
#define B_Tree_B_node_h

template<class Record, int order>
class B_node {
public:
    
    B_node();
    
    // number of records in this node
    // If count is nonzero then the node has count + 1 children.
    int count;
    
    Record * data;
    
    B_node<Record, order> ** branch;
    
    B_node<Record, order> * sequence;
};


using namespace std;


template<class Record, int order>
B_node<Record, order>::B_node() {
    count = 0;
    data = new int[order - 1];
    branch = new B_node<Record, order> * [order];
    sequence = NULL;
}

#endif

