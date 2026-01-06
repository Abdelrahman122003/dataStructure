#include <iostream>
#include <stack>
#include <vector>
using namespace std;

//* what is degenerate BST tree?
// so let's we talk about degenerate BST => that tree look like linked List
// in this tree all operations in this tree O(n) so what difference between it and 
// sequential containers no so to become BST and operations in this tree O(log n)

//* how do we know this tree is Imbalanced(degenerated BST)?
// we must check for each node balance factor(abs(height(left) - height(right))
// if balance factor for each node  is equal to 1 or 0 so this tree is balanced
// if balance factor for each node  is equal abs value greater than 1 so this tree is Imbalanced

//* how to convert it to balanced BST?
// we need to convert this tree to BST(balanced BST) 
// using rotation(we will talk about it later)

//* what is a rotation?
// we have two different types of rotation 
// --right rotation(clockwise)
// --left rotation(counter-clockwise)


//* types of Imbalance
// --case 1: Right Right  ---> balance factor  -2 = h(left) - h(right) = 0 - 2  so in this we do left rotation
// --case 2: right left   ---> balance factor  -2 = h(left) - h(right) = 2 - 0  so in this we do right rotation then left rotation
// --case 3: left left    ---> balance factor  2 = h(left) - h(right) = 2 - 0  so in this we do right rotation
// --case 4: left right   ---> balance factor  2 = h(left) - h(right) = 2 - 0  so in this we do left rotation then right rotation



template<typename type>
class AVLTree{
    private: 
    AVLTree<type>* left;
    AVLTree<type>* right;
    AVLTree<type>* parent;
    type data;
    int height;
    // delete node from BST
    AVLTree<type>* deleteNode(int target, AVLTree<type>* node);
    // special delete --> if(we will delete root)
    void specialDelete(AVLTree<type>* child);
    AVLTree<type>* insert(type ele, AVLTree<type>* node);
    public:
    AVLTree(): left(nullptr), right(nullptr){}
    AVLTree(type val);
    // getter for data
    type getData();
    int getHeight(AVLTree<type>* node);
    void updateHeight();
    int balanceFactor();
    AVLTree<type>* leftRotation(AVLTree<type>* node); 
    AVLTree<type>* rightRotation(AVLTree<type>* node); 
    AVLTree<type>* balance(AVLTree<type>* node); 
    
    // to get all ancestors for any node
    bool findChain(vector< AVLTree<type>*>&ancestors, int target);
    // to get parent from ancestors so we need function to get from it this parent
    AVLTree<type*> getNext(vector<AVLTree<type>*>&ancestors);
    AVLTree<type*> minValue();
    type maxValue();
    // find successor (first element greater than target)
    pair<bool, int> successor(int target);
    // to call this ==> this -------> root(important)
    void deleteN(int target);
    void insertN(type ele);
    bool search(type ele);
    // left -> root -> right ==> LVR
    void inOrderTraversal();
    // left -> right -> root ==> LRV
    void posOrderTraversal();
    // root -> left -> right ==> VLR
    void preOrderTraversal();

};
template<typename type>
AVLTree<type>::AVLTree(type val): data(val), left(nullptr), right(nullptr){}
// getter for data
template<typename type>
type AVLTree<type>::getData(){
        return data;
        }
// to get height
template<typename type>
int AVLTree<type>::getHeight(AVLTree<type>* node){
    // it not exist 
    if(!node)return -1;

    return node->height;
}
template<typename type>
void AVLTree<type>::updateHeight(){
    height = 1 + max(getHeight(left), getHeight(right)); 
}
// to get balance factor
template<typename type>
int AVLTree<type>::balanceFactor(){
    return (getHeight(left) - getHeight(right));
}

// right rotation
template<typename type>
AVLTree<type>* AVLTree<type>::rightRotation(AVLTree<type>* node){
    // store left for this node
    AVLTree<type>* cur = node->left;
    // node->left point to cur->right
    node->left = cur->right; 

    cur->right = node;//this step move node down and cur up

    // Then Update Height for node and cur
    node->updateHeight();
    cur->updateHeight();
    return cur;
}


// left rotation
template<typename type>
AVLTree<type>* AVLTree<type>::leftRotation(AVLTree<type>* node){
    // store right for this node
    AVLTree<type>* cur = node->right;
    // node->right point to node->right
    node->right = cur->left; 
    // cur->left = node
    cur->left = node;

    // Then Update Height for node and cur
    node->updateHeight();
    cur->updateHeight();
    return cur;
}

// balance function
template<typename type>
AVLTree<type>* AVLTree<type>::balance(AVLTree<type>* node)
{
    // left
    if(node->balanceFactor() == 2)
    {
        // if node->left->balanceFactor() equal 1 so left left -> right rotation
        if(node->left->balanceFactor() == -1)// left right -> left rotation then right rotation
        {
            node->left = leftRotation(node->left);
        }
        node = rightRotation(node);
    }
    if(node->balanceFactor() == -2)
    {
         // if node->right->balanceFactor() equal -1 so right right -> left rotation
        if(node->right->balanceFactor() == 1)// right left -> right rotation then left rotation
        {
            node->right = rightRotation(node->right);
        }
        node = leftRotation(node);
    }
    return node;
}


template<typename type>
bool AVLTree<type>::search(type ele)
{
    if(ele == data)return true;
    if(ele < data)return left && left->search(ele);
    return right && right->search(ele);
}
template<typename type>
void AVLTree<type>::insertN(type ele){
    insert(ele, this);
}

template<typename type>
AVLTree<type*> AVLTree<type>::minValue(){
    AVLTree<type> *cur = this;
    while(cur && cur->left)cur = cur->left;
    return cur;  
}

template<typename type>
type AVLTree<type>::maxValue(){
    AVLTree<type> *cur = this;
    while(cur && cur->right)cur = cur->right;
    return cur->data;  
}

template<typename type>
bool AVLTree<type>::findChain(vector<AVLTree<type>*>&ancestors, int target)
{
    ancestors.push_back(this);
    if(target == data)return true;
    if(target < data){
        return left && left->findChain(ancestors, target);  
    }
    return right && right->findChain(ancestors, target);
}

template<typename type>
AVLTree<type*> AVLTree<type>::getNext(vector<AVLTree<type>*>&ancestors){
    if(!ancestors.size())return nullptr;
    AVLTree<type> *node = ancestors.back();
    ancestors.pop_back();
    return node;
}

//* successor
// case1 if you want delete leaf no problem delete it without any problem
// case2 if you want delete node that node has right 
    // -- if this node has right node only this node will became successor(this right will be replace parent--> right)
    // -- if this node has right subtree so we will search for successor with this way 
    // --right then left left left for last left
// case3 if you want delete node that not has right (so we will search for successor)
    // -- will we go for parent for this node if(this parent different dir(left or right))
    // -- will we take this parent if no node = parent then we will go for parent for this parent

template<typename type>
pair<bool, int> AVLTree<type>::successor(int target){
    vector<AVLTree<AVLTree>*>ancestors;
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
    AVLTree* child = getNext(ancestors);
    if(child->right){
        return {true, child->right->minValue()};
    }

    AVLTree* parent = getNext(ancestors);

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

template<typename type>
AVLTree<type>* AVLTree<type>::insert(type ele, AVLTree<type>* node)
{
    if(ele < node->data){
        if(!node->left){
            node->left = new AVLTree(ele);
        }
        else
            node->left = insert(ele, node->left);
    }
    else if(ele > node->data){
        if(!node->right){
            node->right = new AVLTree(ele);
        }
        else
            node->right = insert(ele, node->right);
    }
    node->updateHeight();
    return(balance(node));
}

//* delete
// we have three cases for deletion
//  --case 1 ==> delete leaf -> direct
//  --case 2 ==> delete parent have two or one child -> almost direct
//  --case 3 ==> delete  node and must be find successor for this node  -> A bit tricky
// LVR -> left then root then right
template<typename type>
AVLTree<type>* AVLTree<type>::deleteNode(int target, AVLTree<type>* node)
{
    if(!node)return nullptr;

    if(target < node->data){
        node->left = deleteNode(target, node->left);
    }else if(target > node->data){
        node->right = deleteNode(target, node->right);
    }
    else{
        AVLTree<type>* tem = node;
        if(!node->right && !node->left)//no child so node we become nullptr
            node = nullptr;
        else if(!node->right)//has left child only so node will set it with left child
            node->specialDelete(node->left);
        else if(!node->left)//has right child only so node will set it with right child
            node->specialDelete(node->right);
        else//has two child in this case will find successor
        {
            AVLTree<type>* mn = node->right->minValue();
            node->data = mn->data;// copy this mn in node that deleted
            // understand this
            node->right = deleteNode(node->data, node->right);
            tem = nullptr;
        }
        if(tem){
            delete tem;
        }
    }
    if(node){
        node->updateHeight();
        node = balance(node);
    }
    return node;
}
// to call this ==> this -------> root(important)
template<typename type>
void AVLTree<type>::deleteN(int target){
    deleteNode(target, this);
}

//** special delete --> if(we will delete root) not allow to delete root so we access root with child and delete child
template<typename type>
void AVLTree<type>::specialDelete(AVLTree<type>* child){
    data = child->data;
    left = child->left;
    right = child->right;
    delete child;
}



template<typename type>
void AVLTree<type>::inOrderTraversal(){
   if(left){
    left->inOrderTraversal();
   }
   cout << data << " ";
   if(right) right->inOrderTraversal();
}
// LRV -> left then right then root
template<typename type>
void AVLTree<type>::posOrderTraversal(){
    if(left){
    left->inOrderTraversal();
   }
   if(right) right->inOrderTraversal();
   cout << data << " ";
}
// VlR -> root then left then right
template<typename type>
void AVLTree<type>::preOrderTraversal(){

    cout << data << " ";
     if(left){
        left->inOrderTraversal();
    }
    if(right) right->inOrderTraversal();
}

int main(){
    AVLTree<int>a(1);
    a.insertN(2);
    a.insertN(3);
    a.insertN(4);
    a.insertN(5);
    a.insertN(6);
    a.insertN(7);
    a.insertN(8);
    a.insertN(9);
    a.insertN(10);
    a.insertN(11);
    a.insertN(12);
    a.insertN(13);
    a.insertN(14);
    a.inOrderTraversal();
    // cout << 
    // a.insertN(7);
    // a.insertN(7);
}