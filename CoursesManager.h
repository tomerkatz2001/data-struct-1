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
    int num_of_courses;
    int total_num_of_classes;
    int num_unwatched_classes;
    AvlTree<int,DoubleArray*>* courses_tree;// tree of int as key (coures id), and double array as data (array of int (watchtime) and Node* to list of unwatched classes)
    AvlTree<ClassTuple,ClassTuple*>* viewed_classes_tree;
    AvlTree<int,Node<ClassTuple>*>* unwatched_classes;
    
    
public:
     CoursesManager();
    ~CoursesManager();
    void addCourse(int course_id, int num_of_classes);
    void removeCourse(int course_id);
    void addWatch(int course_id, int class_id, int time_to_add);
    int getTimeViewed(int course_id,int class_id);
    void getMostWatched(int wanted, int* courses,int* classes);
    bool courseExsit(int course_id);
    bool classExisitInCourse(int course_id,int class_id);
    int getTotalClasses();
    int numOfClasses(int course_id);

};

CoursesManager::CoursesManager(/* args */)
{
    num_of_courses=0;
    total_num_of_classes=0;
    num_unwatched_classes=0;
    courses_tree=new AvlTree<int,DoubleArray*>;
    unwatched_classes=new AvlTree<int,Node<ClassTuple>*>;
    viewed_classes_tree =new AvlTree<ClassTuple,ClassTuple*>;

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

int CoursesManager::numOfClasses(int course_id)
{
    DoubleArray* course=courses_tree->get(course_id);
    int num_of_classes=course->getSize();
    return num_of_classes;
}

/*remove the course from the data struct
make sure it exists*/
void CoursesManager::removeCourse(int course_id)
{
    DoubleArray* need_to_remove_course=courses_tree->get(course_id);//log(N=num of courses)
    int num_of_classes=need_to_remove_course->getSize();//o(1)
    int num_of_unwatecd_classes=need_to_remove_course->getListSize();//o(1)
    for(int i=0;i<num_of_classes;i++)//o(num of classes in removed course)
    {
        if(need_to_remove_course->getFirstArray(i)!=0)//this class was watched
        {
            viewed_classes_tree->Delete(ClassTuple(course_id,i,need_to_remove_course->getFirstArray(i)));//o(log(total classes in struct))
        }
        
    }
    num_unwatched_classes-=num_of_unwatecd_classes;
    unwatched_classes->Delete(course_id);//o(log(N))
    courses_tree->Delete(course_id);//o(log(N))
    total_num_of_classes-=num_of_classes;
    num_of_courses--;
}
/*this will add the watch time to the class of the course you ask for
give it course that exists and classs that exists*/
void CoursesManager::addWatch(int course_id, int class_id, int time_to_add)
{
    DoubleArray* course=courses_tree->get(course_id);//log(N)
    int class_watched_time=course->getFirstArray(class_id);//O(1)
    if(class_watched_time!=0)//this classs was watched before
    {
        viewed_classes_tree->Delete(ClassTuple(course_id,class_id,class_watched_time));//o(log(total classes in struct))
    }
    else//unwatched
    {
        if((course->getListStart())==nullptr)
        {
            throw std::exception();
        }
        if(course->getListStart()->getData().getClassID()==class_id)//the class is in the begining og the list
        {
            if(course->getListStart()->right==nullptr)//this is the last unviewed class in this course
            {
                unwatched_classes->Delete(course_id);
            }
            else
            {
                unwatched_classes->insert(course_id,course->getListStart()->right);//o(log(N))
            }
            
            
        }
        num_unwatched_classes--;
    }
    course->addTimeWatch(class_id,time_to_add);
    ClassTuple* new_class_data=new ClassTuple(course_id,class_id,course->getFirstArray(class_id));
    viewed_classes_tree->insert(*new_class_data,new_class_data);
}

/*make sure to give this function a valid course id and class id*/   
int CoursesManager::getTimeViewed(int course_id,int class_id)
{
    return courses_tree->get(course_id)->getFirstArray(class_id);
}

void CoursesManager::getMostWatched(int wanted, int* courses,int* classes)
{
    if(wanted>total_num_of_classes)
    {
        throw std::exception(); //input error
    }
    int viewed=total_num_of_classes-num_unwatched_classes;
    int num=0;
    if(viewed<wanted)
        num=viewed;
    else
        num=wanted;
    if(viewed>0)
    {
        ClassTuple** classes_arr=new ClassTuple*[num];//o(viewed_classes)
        viewed_classes_tree->getBig(classes_arr,num);//o(viewed_classes)
        for(int i=0;i<num;i++)
        {
            courses[i]=classes_arr[i]->getCourseID();
            classes[i]=classes_arr[i]->getClassID();
            classes_arr[i]=nullptr;
        }
        delete []classes_arr;//o(viewed_classes)
    }
    int left=wanted-num;
    unwatched_classes->inorderSmallList(unwatched_classes->getSmallest(),left,courses+num,classes+num);//o(left)
}
/*r
returuns if a courst is in the strcut alraedy
time complax o(N) 
*/
 bool CoursesManager::courseExsit(int course_id)
 {
     return courses_tree->exist(course_id);
 }
 /*returns if a class of the course is in the struct alraedy
 time complax O(N)*/
 bool CoursesManager::classExisitInCourse(int course_id,int class_id)
 {
     if(this->courseExsit(course_id))
     {
         if(courses_tree->get(course_id)->getSize()>class_id)
         {
             return true;
         }
     }
     return false;
 }
 int CoursesManager::getTotalClasses()
 {
     return total_num_of_classes;
 }

#endif