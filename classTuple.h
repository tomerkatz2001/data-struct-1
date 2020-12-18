#ifndef CLASS_TUPLE
#define CLASS_TUPLE

class ClassTuple
{
    private:
    const int course_id;
    const int class_id;
    int watch_time;
    public:
    ClassTuple(const int course_id,const int class_id, const int watch_time=0):course_id(course_id),class_id(class_id),watch_time(watch_time){};
    int getCourseID()const;
    int getClassID()const;
    int getWatchTime()const;
    void addWatchTime(const int to_add);
    bool operator > (const ClassTuple& tuple2)const;
    bool operator == (const ClassTuple& tuple2)const;
    bool operator < (const ClassTuple& tuple2)const;

};

int ClassTuple::getCourseID()const
{
    return this->course_id;
}
int ClassTuple::getClassID()const
{
    return this->class_id;
}
int ClassTuple::getWatchTime()const
{
    return this->watch_time;
}
void ClassTuple::addWatchTime(const int to_add)
{
    this->watch_time+=to_add;
}

bool ClassTuple::operator >(const ClassTuple& tuple2)const
{
    if(*this==tuple2)
    {
        return false;
    }
    if(this->getWatchTime()>tuple2.getWatchTime())
    {
        return true;
    }
    else if(this->getWatchTime()<tuple2.getWatchTime())
    {
        return false;
    }
    else//the time is equal
    {
        if(this->getCourseID()<tuple2.getCourseID())
        {
            return true;
        }
        else if(this->getCourseID()>tuple2.getCourseID())
        {
            return false;
        }
        else
        {
            if(this->getClassID()<tuple2.getClassID())
            {
                return true;
            }
            else
            {
                return false;
            }
            
        }
        
    }
    

}

bool ClassTuple::operator < (const ClassTuple& tuple2)const
{
    if((*this)==tuple2)
    {
        return false;
    }
    return (!(*this>tuple2));
}

bool ClassTuple::operator == (const ClassTuple& tuple2)const
{
    return this->getClassID()==tuple2.getClassID()&&this->getCourseID()==tuple2.getCourseID()&&this->getWatchTime()==tuple2.getWatchTime();
}


#endif