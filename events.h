#ifndef EVENTS_H
#define EVENTS_H


class EVENT
{
protected:
        char *device;
        int value;
        int processTime;

public:
        EVENT(char* n,int v,int pt);
        ~EVENT();
        void display();
        int getprocessTime();
};

class llnode
{
friend class LIST;

public:
        llnode *next;
        EVENT *ev;
        llnode(EVENT *e); //constructor
        ~llnode(); //destructor
};


class list
{
protected:
        llnode *front;
        llnode *back;
        llnode *current;
        llnode *new_point;
        llnode *before_point;
        llnode *after_point;
        llnode *temp;

public:
        list(); //constructor
        ~list(); //destructor
        void display();
        EVENT *getFirstEvent();
        void removeFirstEvent();
        void insertEvent(EVENT *e);
        void processEvents(int tm);
};


#endif