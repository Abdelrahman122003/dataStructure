#include <iostream>
#include <stack>
#include <vector>
using namespace std;

// successor -> next value that greater than anything in tree
template<typename type>
class BST{
    private: 
    BST<type>* left;
    BST<type>* right;
    BST<type>* parent;
    BST<type>* current;
    type data;
    int size;
    // delete node from BST
    BST<type>* deleteNode(int target, BST<type>* node);
    // special delete --> if(we will delete root)
    void specialDelete(BST<type>* child);
    public:
    BST(): left(nullptr), right(nullptr){}

    // getter for data
    type getData(){
        return data;
    }
    BST(type val);
    bool search(type ele);
    // left -> root -> right ==> LVR
    void inOrderTraversal();
    // left -> right -> root ==> LRV
    void posOrderTraversal( BST<type>* current);
    // root -> left -> right ==> VLR
    void preOrderTraversal( BST<type>* current);

    void insert(type ele);
    // to get all ancestors for any node
    bool findChain(vector< BST<type>*>&ancestors, int target);
 
    // to get parent from ancestors so we need function to get from it this parent
    BST<type>* getNext(vector< BST<type>*>&ancestors);
    BST<type>* minValue();
    type maxValue();
    // find successor (first element greater than target)
    pair<bool, int> successor(int target);
    // to call this ==> this -------> root(important)
    void deleteN(int target);
};
template<typename type>
// use this when you add new element 
BST<type>::BST(type val): data(val), left(nullptr), right(nullptr){}
template<typename type>
bool BST<type>::search(type ele)
{
    if(ele == data)return true;
    if(ele < data)return left && left->search(ele);
    return right && right->search(ele);
}
template<typename type>
void BST<type>::insert(type ele)
{
    if(ele < data){
        if(!left){
            left = new BST(ele);
        }
        else
            left->insert(ele);
    }
    else if(ele > data){
        if(!right){
            right = new BST(ele);
        }
        else
            right->insert(ele);
    }else{
        right->insert(ele);
    }
}
template<typename type>
BST<type>* BST<type>::minValue(){
    BST<type> *cur = this;
    while(cur && cur->left)cur = cur->left;
    return cur;  
}
template<typename type>
type BST<type>::maxValue(){
    BST<type> *cur = this;
    while(cur && cur->right)cur = cur->right;
    return cur->data;  
}
template<typename type>
bool BST<type>::findChain(vector<BST<type>*>&ancestors, int target)
{
    ancestors.push_back(this);
    if(target == data)return true;
    if(target < data){
        return left && left->findChain(ancestors, target);  
    }
    return right && right->findChain(ancestors, target);
}
template<typename type>
BST<type>* BST<type>::getNext(vector< BST<type>*>&ancestors){
    if(!ancestors.size())return nullptr;
    BST<type> *node = ancestors.back();
    ancestors.pop_back();
    return node;
}

// case1 if you want delete leaf no problem delete it without any problem
// case2 if you want delete node that node has right 
    // -- if this node has right node only this node will became successor(this right will be replace parent--> right)
    // -- if this node has right subtree so we will search for successor with this way 
    // --right then left left left for last left
// case3 if you want delete node that not has right (so we will search for successor)
    // -- will we go for parent for this node if(this parent different dir(left or right))
    // -- will we take this parent if no node = parent then we will go for parent for this parent

template<typename type>
pair<bool, int> BST<type>::successor(int target){
    vector<BST<type>*>ancestors;
    // ancestors root ----> node of target
    // so child if this child has right in this case has value that greater than this value(first value greater than it)
     
    
    if(!findChain(ancestors, target)){
       
    } return {false, -1};
    // for (size_t i = 0; i < ancestors.size(); i++)
    // {
    //     BST* ch = ancestors[i];
    //     cout << ch->getData() << endl;
    // }
    // if this node  has right in this case we go to right then left left left if 
    // no left for this right we will take this right
    BST* child = getNext(ancestors);
    if(child->right){
        return {true, child->right->minValue()};
    }

    BST* parent = getNext(ancestors);

    // case3 if you want delete node that not has right (so we will search for successor)
    // -- will we go for parent for this node if(this parent different dir(left or right))
    // -- will we take this parent if no node = parent then we will go for parent for this parent

    while(parent && parent->right == child){
        child = parent;parent = getNext(ancestors); 
    }
    // if no has parent so no successor so we will return {false, -1};
    if(parent){
        return {true, parent->data};
    }

    return {false, -1};

}
//** special delete --> if(we will delete root) not allow to delete root so we access root with child and delete child
template<typename type>
void BST<type>::specialDelete(BST<type>* child){
    data = child->data;
    left = child->left;
    right = child->right;
    delete child;
}
 //**search node in BST with use target
template<typename type>
BST<type>* BST<type>::deleteNode(int target, BST<type>* node)
{
    if(!node)return nullptr;

    if(target < node->data){
        node->left = deleteNode(target, node->left);
    }else if(target > node->data){
        node->right = deleteNode(target, node->right);
    }
    else{
        BST<type>* tem = node;
        if(!node->right && !node->left)//no child so node we become nullptr
            node = nullptr;
        else if(!node->right)//has left child only so node will set it with left child
            node->specialDelete(node->left);
        else if(!node->left)//has right child only so node will set it with right child
            node->specialDelete(node->right);
        else//has two child in this case will find successor
        {
            BST<type>* mn = node->right->minValue();
            node->data = mn->data;// copy this mn in node that deleted
            // understand this
            node->right = deleteNode(node->data, node->right);
            tem = nullptr;
        }
        if(tem){
            delete tem;
        }
    }
    return node;
}
// to call this ==> this -------> root(important)
template<typename type>
void BST<type>::deleteN(int target){
    deleteNode(target, this);
}
// we have three cases for deletion
//  --case 1 ==> delete leaf -> direct
//  --case 2 ==> delete parent have two or one child -> almost direct
//  --case 3 ==> delete  node and must be find successor for this node  -> A bit tricky
// LVR -> left then root then right
template<typename type>
void BST<type>::inOrderTraversal(){
   if(left){
    left->inOrderTraversal();
   }
   cout << data << " ";
   if(right) right->inOrderTraversal();
}
// LRV -> left then right then root
template<typename type>
void BST<type>::posOrderTraversal( BST<type>* current){
    if(left){
    left->inOrderTraversal();
   }
   if(right) right->inOrderTraversal();
   cout << data << " ";
}
// VlR -> root then left then right
template<typename type>
void BST<type>::preOrderTraversal( BST<type>* current){

    cout << data << " ";
     if(left){
        left->inOrderTraversal();
    }
    if(right) right->inOrderTraversal();
}
int main(){
    BST<int>b(10);
    b.insert(5);
    b.insert(12);
    b.insert(1);
    b.insert(3);
    // cout << << endl;
    b.inOrderTraversal();
    // pair<bool, int>p;
    // p = b.successor(45);

    // cout << "\nsuccessor(20): " << p.second << endl;
    b.deleteN(1);
    cout << endl;
    b.inOrderTraversal();

}