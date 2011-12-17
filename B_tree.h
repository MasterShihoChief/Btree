#ifndef B_Tree_B_tree_h
#define B_Tree_B_tree_h

#include <iostream>

#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <sstream>

#include <string.h>

#include "util.h"
#include "B_node.h"



template<class Record, int order>
class B_tree {
    
    B_node<Record, order> *root;  
    
public:
    
    int count;
    
    B_tree<Record, order>();
    
    bool DEBUG_OUT;
    
    bool search(int &target1, int &target2);
    bool search_tree_node(B_node<Record, order> *current, int &target1, int &target2);
    
    bool search_tree(int &target1,  int &target2);
    bool recursive_search_tree(B_node<Record, order> *current, int &target1, int &target2);
//    Error_code search_tree(Record &target);
//    Error_code search_node(B_node<Record, order> *current, Record &target, int &position);
    
    bool search_node(B_node<Record, order> *current, int &target, int &position);

    
    bool insert(Record &new_entry);
    
    Error_code push_down(B_node<Record, order> *current, Record &new_entry, Record &median, B_node<Record, order> * &right_branch);
    
    void push_in(B_node<Record, order> *current,
                 Record &entry, B_node<Record, order> *right_branch, int position);
    
    void split_node(
                    B_node<Record, order> *current,    //  node to be split
                    Record &extra_entry,          //  new entry to insert
                    B_node<Record, order> *extra_branch,//  sub B_tree on right of extra_entry
                    int position,                  //  index in node where extra_entry goes
                    B_node<Record, order> *&right_half, //  new node for right half of entries
                    Record &median);                     //  median entry (in neither half)
    
    bool remove(Record &target);
    
    bool recursive_remove(B_node<Record, order> *current, Record &target);
    
    void remove_data(B_node<Record, order> *current, int position);
    
    void copy_in_predecessor(B_node<Record, order> *current, int position);
    
    void restore(B_node<Record, order> *current, int position);
    
    void move_left(B_node<Record, order> *current, int position);
    
    void move_right(B_node<Record, order> *current, int position);
    
    void combine(B_node<Record, order> *current, int position);
    
    bool recursive_search_tree(B_node<Record, order> *current, Record &target);
    
    void in_order();
    
    void print_traversal(B_node<Record, order> *current,ofstream &ofile);
    
    void debug(string s);
    
    void print(ofstream &ofile);
    void pre_order_traversal(B_node<Record, order> *node);
    
    bool has_root();
    
};

using namespace std;

template<class Record, int order>
B_tree<Record, order>::B_tree() {
    DEBUG_OUT = false;
    count = 0;
}

template <class Record, int order> 
bool B_tree<Record, order>::search(int &target1, int &target2) {
    //cout << "calling search" << endl;
    bool result = search_tree_node(root, target1, target2);
  //  cout << result << endl;
    return result;
}

template <class Record, int order> 
bool B_tree<Record, order>::search_tree_node(B_node<Record, order> *current, int &target, int &target2) {
    bool result;
    int position;
    if (current == NULL) result = false;
    else {
        if (search_node(current, target, position) == 0) {  //  The target is in the current node.
            result = true;
            if (current->branch[position] != NULL) {     //  not at a leaf node
                
                return search_node(current->branch[0], target, position);
            }
            else result = true;
        }

    }
    return result;
}




template <class Record, int order> 
bool B_tree<Record, order>::has_root() {
    return root != NULL;
}




template<class Record, int order>
void B_tree<Record, order>::debug(string s) {
    if(DEBUG_OUT) {
      //  cout << s << endl;
    }
}

template<class Record, int order>
void B_tree<Record, order>::print(ofstream &ofile) {
	//cout<<"calling print traversal"<<endl;
    print_traversal(root,ofile);
    ofile << endl;
}

template<class Record, int order>
void B_tree<Record, order>::print_traversal(B_node<Record, order> *current, ofstream &ofile) 
{
   if(current != NULL) {
        for(int i = 0; i < current -> count; i++) {
            ofile << current -> data[i] << ",";
            //cout << current -> data[i] << ",";
        }
        //ofile << " ";
        //ofile << " ";
        
        for(int i = 0; i < order; i++) {
            print_traversal(current -> branch[i],ofile);
        }
        
    }
    
}



template<class Record, int order>
bool B_tree<Record, order>::search_tree(int &target, int &target2) {
    return recursive_search_tree(root, target, target2);
}

template<class Record, int order>
bool B_tree<Record, order> :: recursive_search_tree(B_node<Record, order> *current, int &target, int &target2)
/* Pre: current is either NULL or points to a suB_tree of the B tree.
 Post: If the Key of target is not in the suB_tree, a code of not present is
 returned. Otherwise, a code of success is returned and target is set to
 the corresponding Record of the suB_tree.
 Uses: recursive search tree recursively and search node */
{
      
    bool result = false;
    int position;
    if (current != NULL) {
        result = search_node(current, target, position);
        if (result == false){
            //cout << "running search again inside recursive search tree" << endl;
            result = recursive_search_tree(current->branch[position], target, target2);
        }  else {
            target = current->data[position];
        }
    }
    //  cout << "search result for:" << target << " is " << result << endl;
    return result;
    
}


template <class Record, int order>
bool B_tree<Record, order>::search_node(B_node<Record, order> *current, int &target, int &position)
/*
 Pre:  current points to a node of a B_tree.
 Post: If the Key of target is found in *current, then a code of
 success is returned, the parameter position is set to the index
 of target, and the corresponding Record is copied to
 target.  Otherwise, a code of not_present is returned, and
 position is set to the branch index on which to continue the search.
 Uses: Methods of class Record.
 */
{
	//cout<<"search node called"<<endl;
    position = 0;
	//cout<<"segfault is happening here somewhere dammit, screw u author, u suck"<<endl;
    while (position < current->count && target > current->data[position])
        //cout<<position++<<endl;//  Perform a sequential search through the keys.
	//cout<<"WTF"<<endl;
    if ((position < current->count && target == current->data[position])&&current->branch[0]==NULL)
        return 0;
    else
    {
        return 1;
    }
}



template <class Record, int order>
bool B_tree<Record, order>::insert(Record &new_entry)
/* Post: If the Key of new entry is already in the B tree, a code of duplicate error
 is returned. Otherwise, a code of success is returned and the Record
 new entry is inserted into the B-tree in such a way that the properties of a
 B-tree are preserved.
 Uses: Methods of struct B node and the auxiliary function push down. */
{
    //cout<<"insert called"<<endl;
	
    
    Record median;
    B_node<Record, order> *right_branch, *new_root;
	//cout<<"pushing down"<<endl;
    Error_code result = push_down(root, new_entry, median, right_branch);
    //cout<<"overflow"<<endl;
    if (result == overflow) {  //  The whole tree grows in height.
        //  Make a brand new root for the whole B-tree.
        new_root = new B_node<Record, order>;
        new_root->count = 1;
        new_root->data[0] = median;
        new_root->branch[0] = root;
        new_root->branch[1] = right_branch;
        root = new_root;
        result = success;
    }
    return result == success;
}

template <class Record, int order>
Error_code B_tree<Record, order>::push_down(
                                            B_node<Record, order> *current,
                                            Record &new_entry,
                                            Record &median,
                                            B_node<Record, order> *&right_branch)
/*
 Pre:  current is either NULL or points to a node of a B_tree.
 Post: If an entry with a Key matching that of new_entry is in the suB_tree
 to which current points, a code of duplicate_error is returned.
 Otherwise, new_entry is inserted into the suB_tree: If this causes the
 height of the suB_tree to grow, a code of overflow is returned, and the
 Record median is extracted to be reinserted higher in the B-tree,
 together with the suB_tree right_branch on its right.
 If the height does not grow, a code of success is returned.
 Uses: Functions push_down (called recursively), search_node,
 split_node, and push_in.
 */
{
    
   // cout<<"push down called"<<endl;
    
    Error_code result;
    int position;
	//cout<<"before loop causing seg fault"<<endl;
    if (current == NULL) {
		//cout<<"Since we cannot insert in an empty tree, the recursion terminates."<<endl;
        median = new_entry;
        right_branch = NULL;
        result = overflow;
    }
    else {   
	//cout<<"Search the current node."<<endl;
        if (search_node(current, new_entry, position) == success) {
           // cout<<"push_down - search_node == success"<<endl;
            result = duplicate_error;
        } else {
           // cout<<"push_down - search_node != success"<<endl;
            Record extra_entry;
            B_node<Record, order> *extra_branch;
            result = push_down(current->branch[position], new_entry,
                               extra_entry, extra_branch);
            if (result == overflow) {  //  Record extra_entry now must be added to current
                
                //cout<<"over flow in push down"<<endl;
                
                if (order - 1 > current->count) {
                    
                   // cout<<"push_down - order - 1 > current->count"<<endl;
                    
                    result = success;
                    push_in(current, extra_entry, extra_branch, position);
                }
                
                else {
                    split_node(current, extra_entry, extra_branch, position,
                               right_branch, median);
                }                

                
                //  Record median and its right_branch will go up to a higher node.
            }
        }
    }
    return result;
    
}


template <class Record, int order>
void B_tree<Record, order>::push_in(B_node<Record, order> *current,
                                    Record &entry, B_node<Record, order> *right_branch, int position)
/*
 Pre:  current points to a node of a B_tree.  The node *current is not full
 and entry belongs in *current at index position.
 Post: entry has been inserted along with its right-hand branch
 right_branch into *current at index position.
 */
{
    
   // debug("push in");
    
    for (int i = current->count; i > position; i--) {  //  Shift all later data to the right.
        current->data[i] = current->data[i - 1];
        current->branch[i + 1] = current->branch[i];
    }
    current->data[position] = entry;
    current->branch[position + 1] = right_branch;
    current->count++;
}


template <class Record, int order>
void B_tree<Record, order>::split_node(
                                       B_node<Record, order> *current,    //  node to be split
                                       Record &extra_entry,          //  new entry to insert
                                       B_node<Record, order> *extra_branch,//  suB_tree on right of extra_entry
                                       int position,                  //  index in node where extra_entry goes
                                       B_node<Record, order> *&right_half, //  new node for right half of entries
                                       Record &median)                     //  median entry (in neither half)
/*
 Pre:  current points to a node of a B_tree.
 The node *current is full, but if there were room, the record
 extra_entry with its right-hand pointer extra_branch would belong
 in *current at position position, 0 <= position < order.
 Post: The node *current with extra_entry and pointer extra_branch at
 position position are divided into nodes *current and *right_half
 separated by a Record median.
 Uses: Methods of struct B_node, function push_in.
 */
{
    
    //debug("split node");
    
    right_half = new B_node<Record, order>;
    int mid = order/2;  //  The entries from mid on will go to right_half.
    if (position <= mid) {   //  First case:  extra_entry belongs in left half.
        
       // debug("split_node - position <= mid");
        
        for (int i = mid; i < order - 1; i++) {  //  Move entries to right_half.
            right_half->data[i - mid] = current->data[i];
            right_half->branch[i + 1 - mid] = current->branch[i + 1];
        }
        current->count = mid;
        right_half->count = order - 1 - mid;
        push_in(current, extra_entry, extra_branch, position);
    }
    else {  //  Second case:  extra_entry belongs in right half.
        
        //debug("split_node - else not position <= mid");
        
        mid++;      //  Temporarily leave the median in left half.
        for (int i = mid; i < order - 1; i++) {  //  Move entries to right_half.
            right_half->data[i - mid] = current->data[i];
            right_half->branch[i + 1 - mid] = current->branch[i + 1];
        }
        current->count = mid;
        right_half->count = order - 1 - mid;
        push_in(right_half, extra_entry, extra_branch, position - mid);
    }
    median = current->data[current->count - 1]; //  Remove median from left half.
    right_half->branch[0] = current->branch[current->count];
    
    // B+ tree update
    if(current-> branch[0] != NULL) {
        current->count--;
    }
}


template <class Record, int order>
bool B_tree<Record, order>::remove(Record &target)
/*
 Post: If a Record with Key matching that of target belongs to the
 B_tree, a code of success is returned and the corresponding node
 is removed from the B-tree.  Otherwise, a code of not_present
 is returned.
 Uses: Function recursive_remove
 */
{
    bool result;
    result = recursive_remove(root, target);
    if (root != NULL && root->count == 0) {  //  root is now empty.
        B_node<Record, order> *old_root = root;
        root = root->branch[0];
        delete old_root;
    }
    return result;
}


template <class Record, int order>
bool B_tree<Record, order>::recursive_remove(
                                                   B_node<Record, order> *current, Record &target)
/*
 Pre:  current is either NULL or
 points to the root node of a subtree of a B_tree.
 Post: If a Record with Key matching that of target belongs to the subtree,
 a code of success is returned and the corresponding node is removed
 from the subtree so that the properties of a B-tree are maintained.
 Otherwise, a code of not_present is returned.
 Uses: Functions search_node, copy_in_predecessor,
 recursive_remove (recursively), remove_data, and restore.
 */
{
    bool result;
    int position;
    if (current == NULL) result = false;
    else {
        if (search_node(current, target, position) == 0) {  //  The target is in the current node.
            result = true;
            if (current->branch[position] != NULL) {     //  not at a leaf node
                
                recursive_remove(current->branch[position],
                                 current->data[position]);
            }
            else remove_data(current, position);     //  Remove from a leaf node.
        }
        else result = recursive_remove(current->branch[position], target);
        if (current->branch[position] != NULL)
            if ((order - 1) / 2 > (current->branch[position]->count))
                restore(current, position);
    }
    return result;
}


template <class Record, int order>
void B_tree<Record, order>::remove_data(B_node<Record, order> *current,
                                        int position)
/*
 Pre:  current points to a leaf node in a B-tree with an entry at position.
 Post: This entry is removed from *current.
 */
{
    for (int i = position; i < current->count - 1; i++)
        current->data[i] = current->data[i + 1];
    current->count--;
}


template <class Record, int order>
void B_tree<Record, order>::copy_in_predecessor(
                                                B_node<Record, order> *current, int position)
/*
 Pre:  current points to a non-leaf node in a B-tree with an entry at position.
 Post: This entry is replaced by its immediate predecessor under order of keys.
 */
{
    B_node<Record, order> *leaf = current->branch[position];  //   First go left from the current entry.
    while (leaf->branch[leaf->count] != NULL)
        leaf = leaf->branch[leaf->count]; //   Move as far rightward as possible.
    current->data[position] = leaf->data[leaf->count - 1];
}


template <class Record, int order>
void B_tree<Record, order>::restore(B_node<Record, order> *current,
                                    int position)
/*
 Pre:  current points to a non-leaf node in a B-tree; the node to which
 current->branch[position] points has one too few entries.
 Post: An entry is taken from elsewhere to restore the minimum number of
 entries in the node to which current->branch[position] points.
 Uses: move_left, move_right, combine.
 */
{
    if (position == current->count)   //  case:  rightmost branch
        if (current->branch[position - 1]->count > (order - 1) / 2)
            move_right(current, position - 1);
        else
            combine(current, position);
        else if (position == 0)       //  case: leftmost branch
            if (current->branch[1]->count > (order - 1) / 2)
                move_left(current, 1);
            else
                combine(current, 1);
            else                          //  remaining cases: intermediate branches
                if (current->branch[position - 1]->count > (order - 1) / 2)
                    move_right(current, position - 1);
                else if (current->branch[position + 1]->count > (order - 1) / 2)
                    move_left(current, position + 1);
                else
                    combine(current, position);
}


template <class Record, int order>
void B_tree<Record, order>::move_left(B_node<Record, order> *current,
                                      int position)
/*
 Pre:  current points to a node in a B-tree with more than the minimum
 number of entries in branch position and one too few entries in branch
 position - 1.
 Post: The leftmost entry from branch position has moved into
 current, which has sent an entry into the branch position - 1.
 */
{
    B_node<Record, order> *left_branch = current->branch[position - 1],
    *right_branch = current->branch[position];
    left_branch->data[left_branch->count] = current->data[position - 1];  //  Take entry from the parent.
    left_branch->branch[++left_branch->count] = right_branch->branch[0];
    current->data[position - 1] = right_branch->data[0];  //   Add the right-hand entry to the parent.
    right_branch->count--;
    for (int i = 0; i < right_branch->count; i++) {   //  Move right-hand entries to fill the hole.
        right_branch->data[i] = right_branch->data[i + 1];
        right_branch->branch[i] = right_branch->branch[i + 1];
    }
    right_branch->branch[right_branch->count] =
    right_branch->branch[right_branch->count + 1];
}


template <class Record, int order>
void B_tree<Record, order>::move_right(B_node<Record, order> *current,
                                       int position)
/*
 Pre:  current points to a node in a B-tree with more than the minimum
 number of entries in branch position and one too few entries
 in branch position + 1.
 Post: The rightmost entry from branch position has moved into
 current, which has sent an entry into the branch position + 1.
 */
{
    B_node<Record, order> *right_branch = current->branch[position + 1],
    *left_branch = current->branch[position];
    right_branch->branch[right_branch->count + 1] =
    right_branch->branch[right_branch->count];
    for (int i = right_branch->count ; i > 0; i--) {  //  Make room for new entry.
        right_branch->data[i] = right_branch->data[i - 1];
        right_branch->branch[i] = right_branch->branch[i - 1];
    }
    right_branch->count++;
    right_branch->data[0] = current->data[position]; //  Take entry from parent.
    right_branch->branch[0] = left_branch->branch[left_branch->count--];
    current->data[position] = left_branch->data[left_branch->count];
}


template <class Record, int order>
void B_tree<Record, order>::combine(B_node<Record, order> *current,
                                    int position)
/*
 Pre:  current points to a node in a B-tree with entries in the branches
 position and position - 1, with too few to move entries.
 Post: The nodes at branches position - 1 and position have been combined
 into one node, which also includes the entry formerly in current at
 index  position - 1.
 */
{
    int i;
    B_node<Record, order> *left_branch = current->branch[position - 1],
    *right_branch = current->branch[position];
    left_branch->data[left_branch->count] = current->data[position - 1];
    left_branch->branch[++left_branch->count] = right_branch->branch[0];
    for (i = 0; i < right_branch->count; i++) {
        left_branch->data[left_branch->count] = right_branch->data[i];
        left_branch->branch[++left_branch->count] =
        right_branch->branch[i + 1];
    }
    current->count--;
    for (i = position - 1; i < current->count; i++) {
        current->data[i] = current->data[i + 1];
        current->branch[i + 1] = current->branch[i + 2];
    }
    delete right_branch;
}


#endif
