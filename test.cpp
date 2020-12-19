#include "tree.h"
#include "classTuple.h"
#include "doubleArray.h"
#include "node.h"
#include"CoursesManager.h"
#include<iostream>
#include"library.h"
using namespace std;
int main()
{
 
//  ClassTuple tuple(4,74,0);
//  ClassTuple tuple2(43,3,8);
//  tuple.addWatchTime(4);
//  cout<<(tuple<tuple2)<<endl;

int arr1[5]={-1};
int arr2[5]={-1};

  CoursesManager x;
  x.addCourse(3,1);
  x.addCourse(4,1);
  x.addCourse(1,4);
  x.addWatch(3,0,3);
  
  x.getMostWatched(3,arr1,arr2);
  x.removeCoure(4);

//   Node<ClassTuple> node1(tuple);
   //cout<<tree.get(2)<<endl;
   //double arr[10]={-1,-1,-1,-1,-1,-1,-1,-1,-1,-1};
   //tree.get(arr,8);

  // cout<<arr.get(2);
//tree.get(arr,5);
   //tree.print(0);




   
   
   
   





}
