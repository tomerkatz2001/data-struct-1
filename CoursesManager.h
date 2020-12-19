#ifndef COURSE_MENAGER
#define COURSE_MENAGER
#include"tree.h"
#include "classTuple.h"
#include"doubleArray.h"
#include"node.h"
#include "assert.h"

class CoursesManager
{
private:
    AvlTree<int,DoubleArray*>* courses_tree;// tre of int as key (coures id), and double array as data (array of int (watchtime) and Node* to list of unwatched classes)
    AvlTree<ClassTuple,ClassTuple*>* viewed_classes_tree;
    int num_of_courses;
    int total_num_of_classes;
    int num_unwatched_classes;
    AvlTree<int,Node<ClassTuple>*>* unwatched_classes;
    
    
public:
     CoursesManager();
    ~CoursesManager();
    void addCourse(int course_id, int num_of_classes);

   
  
    void removeCoure(int course_id);
     //to_impliment
    void addWatch(int course_id, int class_id, int time_to_add);
    int getTimeViewed(int course_id,int class_id);
    void getMostWatched(int wanted, int* courses,int* classes);

};

CoursesManager::CoursesManager(/* args */)
{
    courses_tree=new AvlTree<int,DoubleArray*>;
    viewed_classes_tree =new AvlTree<ClassTuple,ClassTuple*>;
    num_of_courses=0;
    total_num_of_classes=0;
    num_unwatched_classes=0;
    unwatched_classes=new AvlTree<int,Node<ClassTuple>*>;
   

}

CoursesManager::~CoursesManager()
{
    
    delete viewed_classes_tree;
    
    delete unwatched_classes;
    delete courses_tree;
}

/*add a new course to the struct
don't give a course that is in the tree */
void CoursesManager::addCourse(int course_id,int num_of_classes)
{
    
    
    DoubleArray* array=new DoubleArray (course_id,num_of_classes);
    courses_tree->insert(course_id,array);
    unwatched_classes->insert(course_id,array->getListStart());
    num_of_courses++;
    total_num_of_classes+=num_of_classes;
    num_unwatched_classes+=num_of_classes;
}

/*remove the course from the data struct
make sure it exists*/
void CoursesManager::removeCoure(int course_id)
{
    DoubleArray* need_to_remove_course=courses_tree->get(course_id);
    int num_of_classes=need_to_remove_course->getSize();
    int num_of_unwatecd_classes=need_to_remove_course->getListSize();
    for(int i=0;i<num_of_classes;i++)
    {
        if(need_to_remove_course->getFirstArray(i)!=0)//this class was watched
        {
            viewed_classes_tree->Delete(ClassTuple(course_id,i,need_to_remove_course->getFirstArray(i)));
        }
        
    }
    num_unwatched_classes-=num_of_unwatecd_classes;
    unwatched_classes->Delete(course_id);
    courses_tree->Delete(course_id);
    total_num_of_classes-=num_of_classes;
    num_of_courses--;


}


#endif