#include"library.h"
#include"CoursesManager.h"
#include <stdio.h>
#include <iostream>
void *Init(){
    return new CoursesManager();
}

StatusType AddCourse (void *DS, int courseID, int numOfClasses)
{
    if(DS==nullptr||numOfClasses<=0||courseID<=0)
    {
        return INVALID_INPUT;
    }
    if(((CoursesManager*)DS)->courseExsit(courseID))//log(N) N-courses in struct
    {
        return FAILURE;
    }
    else
    {
        try
        {
            ((CoursesManager*)DS)->addCourse(courseID,numOfClasses);//O(numOfClassses+log(N))
        }
        catch(const std::bad_alloc& e)
        {
             return ALLOCATION_ERROR;
        }
        catch(const std::exception& e)// i don't think it will get here
        {
            return INVALID_INPUT;
        }
        
    }
    return SUCCESS;
    
}

StatusType RemoveCourse(void *DS, int courseID){
    if(DS==nullptr||courseID<=0)
    {
        return INVALID_INPUT;
    }
    if(!((CoursesManager*)DS)->courseExsit(courseID))//O(log(N). N- number of courses(<<num of classes)
    {
        return FAILURE;
    }
    try
    {
        ((CoursesManager*)DS)->removeCourse(courseID);
    }
    catch(const std::bad_alloc& e)
    {
            return ALLOCATION_ERROR;
    }
    return SUCCESS;
    
}

StatusType WatchClass(void *DS, int courseID, int classID, int time)
{
    if(time<=0||DS==nullptr||courseID<0||classID<=0)
    {
        return INVALID_INPUT;
    }

    if(!((CoursesManager*)DS)->courseExsit(courseID))//O(log(N). N- number of courses(<<num of classes)
    {
        return FAILURE;
    }

    if(!((CoursesManager*)DS)->classExisitInCourse(courseID,classID))//o(log(N))
    {
        return INVALID_INPUT;
    }
    else
    {
        try
        {
            ((CoursesManager*)DS)->addWatch(courseID,classID,time);//o(log(N)+log(M))
        }
        catch(const std::bad_alloc& e)
        {
            return ALLOCATION_ERROR;
        }
        catch(const std::exception& e)
        {
            return INVALID_INPUT;
        }


    }
    return SUCCESS;
    
    
}

StatusType TimeViewed(void *DS, int courseID, int classID, int *timeViewed){
    if(DS==nullptr||courseID<=0||classID<0||((CoursesManager*)DS)->numOfClasses(courseID)<classID+1)
    {
        return INVALID_INPUT;
    }
    if(!((CoursesManager*)DS)->courseExsit(courseID))//O(log(N). N- number of courses(<<num of classes)
    {
        return FAILURE;
    }
    try
    {
        *timeViewed=(((CoursesManager*)DS)->getTimeViewed(courseID,classID));
    }
    catch(const std::bad_alloc& e)
    {
            return ALLOCATION_ERROR;
    }
    return SUCCESS;

}

StatusType GetMostViewedClasses(void *DS, int numOfClasses, int *courses, int *classes)
{
    if(DS==nullptr||numOfClasses<=0)
    {
        return INVALID_INPUT;
    }
    if(((CoursesManager*)DS)->getTotalClasses()<numOfClasses)
    {
        return FAILURE;
    }
    else
    {
        try
        {
            ((CoursesManager*)DS)->getMostWatched(numOfClasses,courses,classes);
        }
        catch(const std::bad_alloc& e)
        {
            return ALLOCATION_ERROR;
        }
        catch(const std::exception& e)
        {
            return INVALID_INPUT;
        }
        
    }
    return SUCCESS;
}

void Quit(void** DS){
    delete (CoursesManager*)*DS;
};