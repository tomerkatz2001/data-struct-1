#ifndef TREE_H
#define TREE_H
#include "info.h"
#include<exception>

#include"node.h"
#include"classTuple.h"

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
    AvlTree<X,Y>* biggest;
    AvlTree<X,Y>* smallest;
    
    
    public:
    ~AvlTree()
    {
        biggest=nullptr;
        smallest=nullptr;
        delete info;
        info=nullptr;
        delete left_tree;
        left_tree=nullptr;
        delete right_tree;
        right_tree=nullptr;

    }
    AvlTree():info(nullptr),left_tree(nullptr),right_tree(nullptr),father(nullptr),biggest(this),smallest(this){}
    
    void print(int sapce)const; 
    void insert(const X& key,const Y& data);
    void Delete(const X& key);
    bool exist(const X& key)const;
    Y get(const X& key)const;
    void getBig(Y* arr,int n)const;
    void getSmall(Y* arr,int n)const;
    AvlTree<X,Y>* getBiggest()const;
    AvlTree<X,Y>* getSmallest()const;

    void insert_help(const X& key,const Y& data);
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
    AvlTree<X,Y>* findV(const X& key);
    void remove(AvlTree<X,Y>* tree_to_remove);
    void getBigAux(Y* arr,int n,const AvlTree<X,Y>* biggest)const;
    void getSmallAux(Y* arr, int n,AvlTree<X,Y>* smallest)const;
    int inorderBig(const AvlTree<X,Y>*tree,Y* arr, int n,int how_much)const;
    int inorderSmall(const AvlTree<X,Y>*tree,Y* arr, int n,int how_much)const;
    
    int inorderSmallListAux(const AvlTree<int,Node<ClassTuple>*>*tree,int wanteted_classes,int* courses,int*  classes)const;
    void inorderSmallList(const AvlTree<int,Node<ClassTuple>*>*smallest,int wanteted_classes,int* courses,int*  classes)const;



    
    
    
};
/*
this function will tell you if the given key is alraedy in the tree
time compax :log(N)
*/
template <class X, class Y>
bool AvlTree<X,Y>::exist(const X& key)const
{
    return this->find(key)==nullptr?false:true;
}

/*
this function will give the data of the given key
BE CAREFUL don't give it a key which not in the tree
time complax:log(N)
*/
template <class X,class Y>
Y AvlTree<X,Y>::get(const X& key)const
{
    if(this->exist(key)==false)
    {
        throw std::exception();
    }
    
    assert(this->exist(key));
    return this->find(key)->getData();
}


/*
give this function a key and it will take it out of the tree without hurting the order of the avltree
time complaxity: log(N) whan n is the amount of items in the tree
if key not found in the tree nothing will happen
*/
template <class X, class Y>
void AvlTree<X,Y>::Delete(const X& key)
{
  
    this->remove(this->findV(key));
    AvlTree<X,Y>* scan=this;
    while(scan->right_tree!=nullptr)//log(N)
    {
        scan=scan->right_tree;
    }
    this->biggest=scan;
    scan=this;
    while(scan->left_tree!=nullptr)//o(logN)
    {
        scan=scan->left_tree;
    }
    this->smallest=scan;
}

/*this function will do an inorder tour in the tree, from the big to the small, and put the data in the given array
give this function how many vertex you want to get
time complax: o(n+log(N)) when n is the givven n and N is size of the tree
but if you give this function the biggedt leaf not log(N) is needed so o(n)
it return the amount of item it got from the tree (it could be at max n)*/
template <class X, class Y>
int AvlTree<X,Y>::inorderBig(const AvlTree<X,Y>*tree, Y* arr, int n,int how_much)const
{ 
    
    if(how_much>=n||tree==nullptr||tree->info==nullptr)
    {
        return how_much;
    }
    
        how_much=this->inorderBig(tree->right_tree,arr,n,how_much);
    
    if(how_much<n)
    {
        arr[how_much]=(tree->info->getData());
        how_much++;
        
        how_much=(this->inorderBig(tree->left_tree,arr,n,how_much));
    }
    return how_much;   
   
}

/*this function will do an inorder tour in the tree, from the small to the big, and put the data in the given array
give this function how many vertex you want to get
time complax: o(n+log(N)) when n is the givven n and N is size of the tree
but if you give this function the biggedt leaf not log(N) is needed so only o(n)
it return the amount of item it got from the tree (it could be at max n)*/
template<class X,class Y>
int AvlTree<X,Y>::inorderSmall(const AvlTree<X,Y>*tree,Y* arr, int n,int how_much)const
{
    if(how_much>=n||tree==nullptr||tree->info==nullptr)
    {
        return how_much;
    }
    how_much=this->inorderSmall(tree->left_tree,arr,n,how_much);
    if(how_much<n)
    {
        arr[how_much]=tree->info->getData();
        how_much++;
        how_much=this->inorderSmall(tree->right_tree,arr,n,how_much);
    }
    return how_much;
}

template<class X,class Y>
int AvlTree<X,Y>::inorderSmallListAux(const AvlTree<int,Node<ClassTuple>*>*tree,int wanteted_classes,int* courses,int*classes)const
{
    int classes_left;
    if(wanteted_classes<=0||tree==nullptr||tree->info==nullptr)
    {
        return wanteted_classes;
    }
    classes_left=this->inorderSmallListAux(tree->left_tree,wanteted_classes,courses,classes);
    if(classes_left>0)
    {
        Node<ClassTuple>* list=tree->info->getData();
        while(list!=nullptr&&classes_left>0)
        {
            classes[wanteted_classes-classes_left]=list->getData().getClassID();
            courses[wanteted_classes-classes_left]=list->getData().getCourseID();
            classes_left--;
            list=list->right;
        }
        int was_inserted=wanteted_classes-classes_left;
        classes_left=this->inorderSmallListAux(tree->right_tree,classes_left,courses+was_inserted,classes+was_inserted);

    }
    return classes_left;

}



template <class X, class Y>
void AvlTree<X,Y>::getBigAux(Y* arr,int n,const AvlTree<X,Y>* biggest)const
{
    int inserted=0;
    inserted=this->inorderBig(biggest,arr,n,0);//
    n=n-inserted;
    const AvlTree<X,Y>* temp_tree=biggest;
    while(n>0)
    {
        int x=0;
        if(temp_tree->father==nullptr)//no more vertex
        {
           throw std::exception();
            break;
        }
        temp_tree=temp_tree->father;
        arr[inserted]=temp_tree->info->getData();
        inserted++;
        n--;
        x=temp_tree->inorderBig(temp_tree->left_tree,(arr+inserted),n,0);
        inserted=inserted+x;
        n=n-x;
    }
        
}

template<class X,class Y>
void AvlTree<X,Y>::getSmallAux(Y* arr, int n,AvlTree<X,Y>* smallest)const
{
    int inserted=0;
    inserted=this->inorderSmall(smallest,arr,n,0);
    n=n-inserted;
    const AvlTree<X,Y>* temp_tree=smallest;
    while(n>0)
    {
        int x=0;
        if(temp_tree->father==nullptr)
        { 
            throw std::exception();
            break;
        }
        temp_tree=temp_tree->father;
        arr[inserted]=temp_tree->info->getData();
        inserted++;
        n--;
        x=temp_tree->inorderSmall(temp_tree->right_tree,(arr+inserted),n,0);
        inserted=inserted+x;
        n=n-x;
    }
}

/*fill the rest of the  given array with the unviewed classes in the right order
give it the smallest vertex it the unviewed tree so it could run in o("wanted_classes") time complax
if given the root time complax o("wanted_class"+log(number of unviewed classes)) */
template<class X,class Y>
void AvlTree<X,Y>::inorderSmallList(const AvlTree<int,Node<ClassTuple>*>*smallest ,int wanteted_classes,int* courses,int*  classes)const
{
    int left=wanteted_classes;
    left=this->inorderSmallListAux(smallest,wanteted_classes,courses,classes);
    const AvlTree<int,Node<ClassTuple>*>*temp_tree= smallest;
    while(left>0)
    {
        if(temp_tree->father==nullptr)
        { 
            throw std::exception();
        }
        Node<ClassTuple>* list=temp_tree->info->getData();
        while(list!=nullptr&&left>0)
        {   
            classes[wanteted_classes-left]=list->getData().getClassID();
            courses[wanteted_classes-left]=list->getData().getCourseID();
            left--;
            list=list->right;
        }
        int was_inserted=wanteted_classes-left;
        left=this->inorderSmallListAux(temp_tree->right_tree,left,courses+was_inserted,classes+was_inserted);

    }


}




/*
this function will give you the n biggest element in the tree by order in the arr you give it (a[0]-the biggest)
give it an arr with enough space and if asked more then what were in the tree thrw exception
 */
template <class X, class Y>
void AvlTree<X,Y>::getBig(Y* arr,int n)const
{
    getBigAux(arr,n,(this->biggest));
}
/*
this function will give you the n small element in the tree by order in the arr you give it (a[0]-the smallest)
give it an arr with enough space and if asked more then what were in the tree thrw exception
 */
template<class X,class Y>
void AvlTree<X,Y>::getSmall(Y* arr,int n)const
{
    getSmallAux(arr,n,this->smallest);
}



/*
this function gets a key and data to add THEM into the tree.
if the key is already in the tree this will replace it with the new data by removing the old one and inserting the new one
time comlex:log(N)
*/
template<class X,class Y>
void AvlTree<X,Y>::insert(const X& key,const Y& data)
{
    this->insert_help(key,data);
    AvlTree<X,Y>* scan=this;
    while(scan->right_tree!=nullptr)
    {
        scan=scan->right_tree;
    }
    this->biggest=scan;
    scan=this;
    while(scan->left_tree!=nullptr)
    {
        scan=scan->left_tree;
    }
    this->smallest=scan;
}

template<class X,class Y>
void AvlTree<X,Y>::insert_help(const X& key,const Y& data)
{
    if(this->findV(key)!=nullptr)
    {
        if(this->info!=nullptr)
        {
            this->Delete(key);
        }
    }
    
    if(this->info==nullptr)//empty tree
    {
       Info<X,Y>* new_info_ptr= new Info<X,Y>;
        new_info_ptr->changeData(data);
       new_info_ptr->changeKey(key);
        this->info=new_info_ptr;
        this->biggest=this;
        this->smallest=this;
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





/*returns a pointer to the biggest vertex in the tree*/
template <class X, class Y>
AvlTree<X,Y>* AvlTree<X,Y>::getBiggest()const
{
    return this->biggest;
}
/*returns a pointer to the smallest vertex in the tree*/
template<class X, class Y>
AvlTree<X,Y>* AvlTree<X,Y>::getSmallest()const
{
    return this->smallest;
}

/*
find the vertex with the same key that was given and return its address
if not fount in the tree returns nullptr
*/
template <class X, class Y>
AvlTree<X,Y>* AvlTree<X,Y>::findV(const X& key)
{
    if(this==nullptr||this->info==nullptr)
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

/*
remove the given vertex that was given without hurting his sons
if given nullptr to remove it won't do anything
*/
template<class X,class Y>
void AvlTree<X,Y>::remove(AvlTree<X,Y>* remove_ptr)
{
    
    if(remove_ptr==nullptr)//it is not in the tree
    {
        return;
    }
    if(remove_ptr->left_tree==nullptr&&remove_ptr->right_tree==nullptr)//leaf
    {
        if(remove_ptr->father==nullptr)//there is only one 
        {
            delete remove_ptr->info;
            remove_ptr->info=nullptr;
        }
        else
        {
            AvlTree<X,Y>* father=remove_ptr->father;
            if(father->left_tree==remove_ptr)
            {
                father->left_tree=nullptr;
            }
            if(father->right_tree==remove_ptr)
            {
                father->right_tree=nullptr;
            }
            father->updateHeight();
            delete remove_ptr;
            while (father!=nullptr)
            {   
                father->checkAndFix();
                father=father->father;
            }   
        }
    }
    else if(remove_ptr->right_tree==nullptr&&remove_ptr->left_tree!=nullptr)//no leaf with only left tree
    {   
        if(remove_ptr->father==nullptr)//the root of the tree with only one kid
        {
            delete remove_ptr->info;
            remove_ptr->info =remove_ptr->left_tree->info;
            remove_ptr->left_tree->info=nullptr;
            AvlTree<X,Y>* temp_left=remove_ptr->left_tree->left_tree;
            AvlTree<X,Y>* temp_right=remove_ptr->left_tree->right_tree;
            remove_ptr->left_tree->left_tree=nullptr;
            remove_ptr->left_tree->right_tree=nullptr;
            delete remove_ptr->left_tree;
            remove_ptr->left_tree=temp_left;
            if(temp_left!=nullptr)
            {
                temp_left->father=remove_ptr;
            }
            remove_ptr->right_tree=temp_right;
            if(temp_right!=nullptr)
            {
                temp_right->father=remove_ptr;
            }
            
            
        }
        else//not the root, has a father
        {
            AvlTree<X,Y>* father=remove_ptr->father;
            if(father->left_tree==remove_ptr)
            {
                father->left_tree=remove_ptr->left_tree;
                
            }
            if(father->right_tree==remove_ptr)
            {
                father->right_tree=remove_ptr->left_tree;
               
            }
            if(remove_ptr->left_tree!=nullptr)
            {
                remove_ptr->left_tree->father=remove_ptr->father;
            }
            remove_ptr->left_tree=nullptr;
            delete remove_ptr;
            while(father!=nullptr)
            {
                father->updateHeight();
                father->checkAndFix();
                father=father->father;
            }
        }

    }
    else if(remove_ptr->right_tree!=nullptr&&remove_ptr->left_tree==nullptr)//no leaf with only right tree
    {
        if(remove_ptr->father==nullptr)//this is the root of the tree, no father
        {
            delete remove_ptr->info;
            remove_ptr->info=remove_ptr->right_tree->info;
            remove_ptr->right_tree->info=nullptr;
            AvlTree<X,Y>* temp_left=remove_ptr->right_tree->left_tree;
            AvlTree<X,Y>* temp_right=remove_ptr->right_tree->right_tree;
            remove_ptr->right_tree->left_tree=nullptr;
            remove_ptr->right_tree->right_tree=nullptr;
            delete remove_ptr->right_tree;
            remove_ptr->left_tree=temp_left;
            if(temp_left!=nullptr)
            {
                temp_left->father=remove_ptr;
            }
            remove_ptr->right_tree=temp_right;
            
            if(temp_right!=nullptr)
            {
                temp_right->father=remove_ptr;
            }
        }
        else//not the root, has a father
        {
             AvlTree<X,Y>* father=remove_ptr->father;
            if(remove_ptr->father->left_tree==remove_ptr)
            {
                remove_ptr->father->left_tree=remove_ptr->right_tree;
            }
            if(remove_ptr->father->right_tree==remove_ptr)
            {
                remove_ptr->father->right_tree=remove_ptr->right_tree;
            }
            if(remove_ptr->right_tree!=nullptr)
            {
                remove_ptr->right_tree->father=remove_ptr->father;
            }
            remove_ptr->right_tree=nullptr;
            delete remove_ptr;
            while(father!=nullptr)
            {
                father->updateHeight();
                father->checkAndFix();
                father=father->father;
            }
        }
    }
    else if(remove_ptr->right_tree!=nullptr&&remove_ptr->right_tree!=nullptr)
    {
        AvlTree<X,Y>* next =remove_ptr->right_tree;
        while(next->left_tree!=nullptr)
        {
            next=next->left_tree;
        }
        Info<X,Y>* temp_info=remove_ptr->info;
        remove_ptr->info=next->info;
        next->info=temp_info;
        this->remove(next);
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
        if(this->info!=nullptr)
        std::cout<<this->info->getData()<<std::endl;
        this->left_tree->print(space+3);

    }

}

#endif