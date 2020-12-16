#ifndef INFO_H
#define INFO_H
#include <cstddef>
#include<memory>
#include<iostream>
#include<assert.h>

template <class T ,class Z>
class Info
{
    private:
    T key;
    Z data;
    int height;
    
    public:
    Info(Z key , T data):key(key),data(data),height(0){}
    Info():height(0){}//empty Info 
    Z getData()const;
    void changeData(const Z new_data);
    int getHeight()const;
    void changeHeight(int new_h);
    T getKey() const;
    void changeKey(const T new_key);

    

};

template<class T,class Z>
Z Info<T,Z>::getData() const
{
    return this->data;
}

template <class T,class Z>
T Info<T,Z>::getKey()const
{
    return this->key;
}

template<class T,class Z>
int Info<T,Z>::getHeight()const{
    return this->height;
}

template<class T,class Z>
void Info<T,Z>::changeHeight(int hew_h)
{
    this->height=hew_h;
}


template<class T,class Z>
void Info<T,Z>::changeData(const Z new_data)
{
    this->data=new_data;
}

template<class T,class Z>
void Info<T,Z>::changeKey(const T new_key)
{
    this->key=new_key;
}


#endif
