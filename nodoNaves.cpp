#include <iostream>
#include <stdio.h>

using namespace std;

class nodoNaves{
    public:
        int data;
        nodoNaves* next;

        nodoNaves(){
            data=0;
            next=NULL;
        }

        nodoNaves(int data){
            this->data = data;
            this->next = NULL;
        }

        void setData(int value){
            data=value;
        }

        int getData(){
            return data;
        }

        void setNext(nodoNaves* ptr){
            next=ptr;
        }

        nodoNaves* getNext(){
            return next;
        }

};
