
#ifndef TREE_H
#define TREE_h
#include "info.h"

static int max(const int& a,const  int& b)
{
    if(a>b)
    return a;
    else
    {
        return b;
    }
    
}


template<class X,class Y>
class AvlTree
{
    private:
    Info<X,Y>* info;
    AvlTree<X,Y>* left_tree;
    AvlTree<X,Y>* right_tree;
    AvlTree<X,Y>* father;
    public:
    ~AvlTree()
    {
        delete info;
        info=nullptr;
        delete left_tree;
        left_tree=nullptr;
        delete right_tree;
        right_tree=nullptr;

    }
    AvlTree():info(nullptr),left_tree(nullptr),right_tree(nullptr),father(nullptr){}
    //AvlTree(const X& key ,const Y& data):info(nullptr),left_tree(nullptr),right_tree(nullptr)
    //{
      //  Info<X,Y>* info_ptr= new Info<X,Y>(key,data);
        //info=info_ptr;
   // }
    void print(int sapce)const; 
    void insert(X key,Y data);
    int getHeight() const ;
    void updateHeight();
    int getBF()const;
    void checkAndFix();
    void lRoll();//done on right son
    void rRoll();//done on left son
    void llRoll();
    void lrRoll();
    void rrRoll();
    void rlRoll();
    const Info<X,Y>* find(const X& key) const;
    AvlTree<X,Y>* findV(X key);
    void remove(AvlTree<X,Y>* tree_to_remove);
    //AvlTree<X,Y>* getFatherOf(const X& key);
    
};

template <class X, class Y>
AvlTree<X,Y>* AvlTree<X,Y>::findV(X key)
{
    if(this==nullptr||info==nullptr)
    {
        return nullptr;
    }
    X this_key=this->info->getKey();
    if(this_key==key)
    {
        return this;
    }
    else
    {
        if(this_key<key)
        {
            if(this->right_tree==nullptr)
            {
                return nullptr;
            }
            else
            {
                return this->right_tree->findV(key);
            }
            
            
        }
        else
        {
            if(this->left_tree==nullptr)
            {
                return nullptr;
            }
            else
            {
                return this->left_tree->findV(key);
            }
        }
        
    }   
}

// template<class X,class Y>
// AvlTree<X,Y>* AvlTree<X,Y>::getFatherOf(const X& key)
// {
//     assert(this->find(key)!=nullptr);
//     if(this->info->getKey()=key)
//     {
//         return nullptr; // no father to this
//     }

//     return (this->find(key))->farher;

// }

template<class X,class Y>
void AvlTree<X,Y>::remove(AvlTree<X,Y>* remove_ptr)
{
    
    if(remove_ptr=nullptr)//it is not in the tree
    {
        return;
    }
    if(remove_ptr->left_tree==nullptr&&remove_ptr->right_tree==nullptr)//leaf
    {
        AvlTree<X,Y>* father=remove_ptr->father;
        if(father->left_tree=remove_ptr)
        {
            father->left_tree=nullptr;
        }
        if(father->right_tree=remove_ptr)
        {
            father->right_tree=nullptr;
        }
        delete remove_ptr;
        while (father!=nullptr)
        {   
            father.checkAndFIX();
            father=father->father;
        }   
    }
    if(remove_ptr->right_tree==nullptr&&remove_ptr->left_tree!=nullptr)//no leaf with only left tree
    {   
        if(remove_ptr->father==nullptr)//the info of the tree with only one kid
        {
            Info<X,Y>* temp= remove_ptr->left_tree->info;
            remove_ptr->left_tree->info=nullptr;
            
            delete remove_ptr->info;
            remove_ptr->info=temp;
            
            remove_ptr->right_tree=remove_ptr->left_tree->right_tree;
            remove_ptr->left_tree->right_tree=nullptr;

            AvlTree<X,Y>* temp_tree =remove_ptr->left_tree->left_tree;
            remove_ptr->left_tree->left_tree=nullptr;

            delete remove_ptr->left_tree;

            remove_ptr->left_tree=temp_tree;
        }
        else
        {
            AvlTree<X,Y>* father=remove_ptr->father;
            if(father->left_tree=remove_ptr)
            {
                father->left_tree=remove_ptr->left_tree;
                remove_ptr->left_tree=nullptr;
            }
            if(father->right_tree=remove_ptr)
            {
                father->right_tree=remove_ptr->left_tree;
                remove_ptr->left_tree=nullptr;
            }
            delete remove_ptr;
            
        }
        

    }
}
template<class X,class Y>
const Info<X,Y>* AvlTree<X,Y>::find(const X& key) const
{
    if(this->info==nullptr)//empty tree
    {
        return nullptr;
    }
    if(this->info->getKey()==key)
    {
        return info;
    }
    if(this->info->getKey()>=key)
    {
        if(this->left_tree!=nullptr)
        {
            return this->left_tree->find(key);
        }
        else
        {
            return nullptr;
        }
        
    }
    else
    {
        if(this->right_tree!=nullptr)
        {
            return this->right_tree->find(key);
        }
        else
        {
            return nullptr;
        }
        
    }
    
}
template<class X,class Y>
void AvlTree<X,Y>::updateHeight()
{
    if(this->info==nullptr)
    return;
    int h_left_son=this->left_tree!=nullptr?this->left_tree->getHeight():-1;
    int h_right_son=this->right_tree!=nullptr?this->right_tree->getHeight():-1;
    this->info->changeHeight(1+max(h_left_son,h_right_son));
}

template <class X,class Y>
int AvlTree<X,Y>::getHeight()const
{
    assert(this!=nullptr);
    return this->info==nullptr?-1:this->info->getHeight();

}

template <class X,class Y>
int AvlTree<X,Y>::getBF()const
{
    int h_left_son=this->left_tree==nullptr?-1:this->left_tree->getHeight();
    int h_right_son=this->right_tree==nullptr?-1:this->right_tree->getHeight();
    return h_left_son-h_right_son;

}

template<class X,class Y>
void AvlTree<X,Y>::rRoll()
{
    assert(this->left_tree!=nullptr);
    assert(this->info!=nullptr);
    Info<X,Y>* B=this->info;
    Info<X,Y>* A=this->left_tree->info;
    AvlTree<X,Y>* AL=this->left_tree->left_tree;
    AvlTree<X,Y>* AR=this->left_tree->right_tree;
    AvlTree<X,Y>* BR=this->right_tree;
    this->right_tree=nullptr;
    this->left_tree->left_tree=nullptr;
    this->left_tree->right_tree=nullptr;
    this->left_tree->info=nullptr;
    delete this->left_tree;
    if(this->right_tree==nullptr)
    {
        this->right_tree=new AvlTree<X,Y>;
    }
    this->info=A;
    this->right_tree->right_tree=BR;
    this->right_tree->left_tree=AR;
    this->right_tree->info=B;
    this->right_tree->father=this;
    
    this->left_tree=AL;
    if(AL!=nullptr)
    AL->father=this;
    if(AR!=nullptr)
    AR->father=this->right_tree;
    if(BR!=nullptr)
    BR->father=this->right_tree;

    this->right_tree->updateHeight();
    this->updateHeight();

}

template<class X, class Y>
void AvlTree<X,Y>::lRoll()
{
    assert(this->right_tree!=nullptr);
    assert(this->info!=nullptr);
    Info<X,Y>* B=this->right_tree->info;
    Info<X,Y>* A=this->info;
    AvlTree<X,Y>* AL=this->left_tree;
    AvlTree<X,Y>* BL=this->right_tree->left_tree;
    AvlTree<X,Y>* BR=this->right_tree->right_tree;
    this->left_tree=nullptr;
    this->right_tree->left_tree=nullptr;
    this->right_tree->right_tree=nullptr;
    this->right_tree->info=nullptr;
    delete this->right_tree;
    
    if(this->left_tree==nullptr)
    {
        this->left_tree=new AvlTree<X,Y>;
    }
    this->info=B;
    this->left_tree->left_tree=AL;
    this->left_tree->right_tree=BL;
    this->left_tree->info=A;
    
    this->left_tree->father=this;
    
    this->right_tree=BR;
    if(BR!=nullptr)
    BR->father=this;
    if(AL!=nullptr)
    AL->father=this->left_tree;
    if(BL!=nullptr)
    BL->father=this->left_tree;

    this->left_tree->updateHeight();
    this->updateHeight();
}


template <class X ,class Y>
void AvlTree<X, Y>::llRoll()
{
    this->rRoll();

}

template <class X,class Y>
void AvlTree<X,Y>::rrRoll()
{
    this->lRoll();
}

template <class X,class Y>
void AvlTree<X, Y>::lrRoll()
{
    this->left_tree->lRoll();
    this->rRoll();
}

template <class X,class Y>
void AvlTree<X,Y>::rlRoll()
{
    this->right_tree->rRoll();
    this->lRoll();
}

template <class X,class Y>
void AvlTree<X,Y>::checkAndFix()
{

    int h_left_son=this->left_tree==nullptr?-1:this->left_tree->getHeight();
    int h_right_son=this->right_tree==nullptr?-1:this->right_tree->getHeight();
    int new_height=1+max(h_left_son,h_right_son);
    this->info->changeHeight(new_height);
    int bf=this->getBF();
    if(bf==2)
    {

        int left_bf=this->left_tree==nullptr?0:this->left_tree->getBF();
        if(left_bf>=0)
        {
            this->llRoll();
        }
        if(left_bf==-1)
        {
            this->lrRoll();
        }

    }
    if(bf==-2)
    {
        int right_bf=this->right_tree==nullptr?0:this->right_tree->getBF();
        if(right_bf<=0)
        {
            this->rrRoll();
        }
        if(right_bf==1)
        {
            this->rlRoll();
        }


    }

}

template<class X,class Y>
void AvlTree<X,Y>::print(int space) const{
    if(this!=nullptr)
    {
        this->right_tree->print(space+3);
        for(int i=0;i<space;i++)
        {
            std::cout<<" ";
        }
        std::cout<<this->info->getData()<<std::endl;
        this->left_tree->print(space+3);


    }

}

template<class X,class Y>
void AvlTree<X,Y>::insert(X key,Y data)
{
    if(this->find(key)!=nullptr)
    {
        if(this->info!=nullptr)
        {
           // assert(0);
        }
    }
    
    if(this->info==nullptr)//empty tree
    {
       Info<X,Y>* new_info_ptr= new Info<X,Y>;
       new_info_ptr->changeData(data);
       new_info_ptr->changeKey(key);
        this->info=new_info_ptr;
        return;
    }
    else//added to tree
    {
    
    if(key<=info->getKey())//need to go left
    {
        if(this->left_tree==nullptr)//there is no left tree
        {
            
            AvlTree<X,Y>* new_tree_ptr =new AvlTree<X,Y>;
            new_tree_ptr->info=new Info<X,Y>;
            new_tree_ptr->info->changeData(data);
            new_tree_ptr->info->changeKey(key);
            new_tree_ptr->father=this;
            this->left_tree=new_tree_ptr;
        }
        else
        {
            
            this->left_tree->insert(key,data);
        } 
    }
    else//need to be put in the right side
    {
        if(this->right_tree==nullptr)//ther is no right tree
        {
            
            AvlTree<X,Y>* new_tree_ptr =new AvlTree<X,Y>;
            new_tree_ptr->info= new Info<X,Y>;
            new_tree_ptr->info->changeData(data);
            new_tree_ptr->info->changeKey(key);
            new_tree_ptr->father=this;
            this->right_tree=new_tree_ptr;
        }
        else
        {
            
            this->right_tree->insert(key,data);
        }
        
    }
    }
    this->updateHeight();
    this->checkAndFix();

}
#endif