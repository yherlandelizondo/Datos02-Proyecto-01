#include<iostream>
#include<stdio.h>

//! CollectorNode class, used to create Collector Node objects
class CollectorNode{
    public:
        void* memPtr;
        CollectorNode* next;
        //! constructor method
        CollectorNode(){
            memPtr = 0;
            next = NULL;
        }
        //! constructor method
        CollectorNode(void* ptr){
            this->memPtr = ptr;
            this->next = NULL;
        }
        //! method used to set the setMemPtr value
        void setMemPtr(void* value){
            memPtr = value;
        }
        //! method used to get the setMemPtr value
        void* getMemPtr(){
            return memPtr;
        }
        //! method used to set the next value
        void setNext(CollectorNode* ptr){
            next = ptr;
        }
        //! method used to get the next value
        CollectorNode* getNext(){
            return next;
        }
};