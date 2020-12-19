#ifndef NODE_H
#define NODE_H
template<class X>
class Node
{
public:
    X data;
    Node* left;
    Node* right;
    

    Node(X data);
    ~Node();
    X getData();
    void putData(X data);
    void changeLeft(Node* new_left);
    void changeRight(Node* new_right);

};
template<class X>
Node<X>::Node(X data):data(data),left(nullptr),right(nullptr){}

template<class X>
Node<X>::~Node()
{
    
    if(left==nullptr&&right==nullptr)
    {
        data.~X();
    }
    else if(left==nullptr&&right!=nullptr)
    {
        this->right->left=nullptr;
        data.~X();
        
    }
    else if(left!=nullptr&&right==nullptr)
    {
        this->left->right=nullptr;
        data.~X();
    }
    else if(left!=nullptr&&right!=nullptr)
    {
        this->left->right=this->right;
        this->right->left=this->left;
        data.~X();
    }
    
    
   
}
 template<class X>
X Node<X>::getData()
{
    return data;
}
template<class X>
void Node<X>::putData(X data)
{
    this->data=data;
}

template<class X>
void Node<X>::changeLeft(Node* new_left)
{
    this->left=new_left;
}
template<class X>
void Node<X>::changeRight(Node* new_right)
{
    this->right=new_right;
}



#endif