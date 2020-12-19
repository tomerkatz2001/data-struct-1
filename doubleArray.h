#ifndef DOUBLE_ARRAY
#define DOUBLE_ARRAY
#include"node.h"
#include"classTuple.h"
#include<exception>

class DoubleArray
{
private:
    int size;
    int* first_array;
    Node<ClassTuple>** second_array;
    int unwatched_classes;
    Node<ClassTuple>* start_list;
    Node<ClassTuple>* end_list;

public:
 DoubleArray(const int curse_id ,const int num_of_classes);
 ~DoubleArray();

 int getFirstArray(const int index)const;
 Node<ClassTuple>* getSecondArray(const int index)const; 
void addTimeWatch(int class_index,int time_to_add);
//void insertSecondArray(int index,Node<ClassTuple*>* item);
int getListSize()const;
Node<ClassTuple>* getListStart()const;
Node<ClassTuple>* getListEnd()const;
void changeStartList(Node<ClassTuple>* new_start);
void changeEndList(Node<ClassTuple>* new_end);
int getSize()const;

};
/*time complax o(num of classes)*/
DoubleArray::DoubleArray(const int course_id,const int num_of_classes):unwatched_classes(num_of_classes),start_list(nullptr),end_list(nullptr)
{
    this->size=num_of_classes;
    if(num_of_classes==0)
    {
        first_array=nullptr;
        second_array=nullptr;    
    }
    if(num_of_classes>0){
        first_array=new int[num_of_classes]();
        second_array=new Node<ClassTuple>*[num_of_classes];
        for(int i=0;i<num_of_classes;i++)
        {
            ClassTuple new_class (course_id,i,0);
            second_array[i]=new Node<ClassTuple>(new_class);
            if(i==0)
            {
                second_array[i]->left=nullptr;
            }
            else
            {
                second_array[i]->left=(second_array[i-1]);
            }
            
        }
        for(int i=0;i<num_of_classes;i++)
        {
            if(i==num_of_classes-1)
            {
                second_array[i]->right=(nullptr);
            }
            else
            {
                second_array[i]->right=(second_array[i+1]);
            }
            
        }
        start_list=second_array[0];
        end_list=second_array[num_of_classes-1];
    }
    else if(num_of_classes<0)
    {
        throw std::exception();
    }
    
}

DoubleArray::~DoubleArray()
{
    delete[]first_array;
    
    for(int i=0;i<this->size;i++)
    {
        delete second_array[i];
        second_array[i]=nullptr;
    }
    delete[] second_array;
    
}

int DoubleArray::getFirstArray(const int index)const
{
    if(index>=size)
    {
        throw std::exception();
    }
    return first_array[index];
}

Node<ClassTuple>* DoubleArray::getSecondArray(const int index)const
{
    if(index>=size)
    {
        throw std::exception();
    }
    return second_array[index];
}

void DoubleArray::addTimeWatch(int class_index,int time_to_add)
{
    if(class_index>=size)
    {
        throw std::exception();
    }
    first_array[class_index]+=time_to_add;
    if(second_array[class_index]!=nullptr)
    {
        if(second_array[class_index]==start_list)
        {
            start_list=second_array[class_index]->right;
        }
        if(second_array[class_index]==end_list)
        {
            end_list=second_array[class_index]->left;
        }
       delete second_array[class_index];
       second_array[class_index]=nullptr;
       unwatched_classes--;
    }

}

/*void DoubleArray::insertSecondArray(int index,Node<ClassTuple*>* item)
{
    if(index>=size)
    {
        throw std::exception();
    }
    second_array[index]=item;
}*/

/*this function return the number of unwated classes in this course*/
int DoubleArray::getListSize()const
{
    return unwatched_classes;
}

Node<ClassTuple>* DoubleArray::getListStart()const
{
    return start_list;
}

Node<ClassTuple>* DoubleArray::getListEnd()const
{
    return end_list;
}


void DoubleArray::changeStartList(Node<ClassTuple>* new_start)
{
    this->start_list=new_start;
}

void DoubleArray::changeEndList(Node<ClassTuple>* new_end)
{
    this->end_list=new_end;
}

int DoubleArray::getSize() const
{
    return size;
}



#endif