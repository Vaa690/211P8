#include <iostream>
#include <fstream>
#include "definitions.h"
#include "system_utilities.h"
#include "devices.h"
#include "events.h"
#include "string.h"
#include "stdlib.h"


using namespace std;

llnode::llnode(EVENT *e) {
        ev = e;    // fix this later?? ev = e  ? whats e
        next = NULL;
}

llnode::~llnode() {
        delete ev;
}

list::list() {
        front = NULL;
}

list::~list() {
        current = front;
        while (current != NULL) {
                temp = current->next;
                delete current;
                current = temp;
        }
}

void list::display() {

        cout<<"Displaying event list:"<<endl;
        current = front;
        while (current != NULL) {
                current->ev->display();
                current = current->next;
        }
        cout << endl;
}

EVENT *list::getFirstEvent() {
        if(front != NULL) return front->ev;
        return NULL;
}


void list::removeFirstEvent() {
        if(front != NULL) {
                temp = front;
                if(front == back) front = back = 0;
                else front = front->next;
                delete temp;
        }
}

void list::insertEvent(EVENT *e) {
        new_point = new llnode(e);

        if(front == NULL) {
                front = back = new_point;
        }
        else {
                before_point = NULL;
                after_point = front;

                while(after_point != NULL) {
                        if(after_point->ev->getprocessTime() > new_point->ev->getprocessTime()) break;
                        before_point = after_point;
                        after_point = after_point->next;
                }
                
                if(after_point == front) {
                        new_point->next = front;
                        front = new_point;
                }
                else if(after_point == NULL) {
                        back->next = new_point;
                        back = new_point;
                }
                else {
                        before_point->next = new_point;
                        new_point->next = after_point;
                }
        }
}

EVENT::EVENT(char* name,int v, int pt) {
        device = (char *) malloc(strlen(name) + 1);
        strcpy(device, name);
        value = v;
        processTime = pt;

}

EVENT::~EVENT() {
        free( (void *)device);

}

void EVENT::display() {
        cout<<"EVENT:       DEVICE:" << device << endl;
        cout << "Device value " << value << ". Schedule to be processed at " << processTime<< "."<<endl<<endl;
}


int EVENT::getprocessTime() {
        return processTime;
}


void list::processEvents(int tm) {
        cout << endl << endl << "Processing events at time " << tm << "." << endl << endl;
        temp = front;
        while (front != NULL) {
                if(front->ev->getprocessTime() > tm) break;
                cout << "     Processing event:" << endl;
                front->ev->display();
                temp = temp->next;
                removeFirstEvent();
        }
}