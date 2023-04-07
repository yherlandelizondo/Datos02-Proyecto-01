#include<iostream>
#include<stdio.h>
#include "CollectorNode.cpp"
using namespace std;

class BulletCollector{
    
    CollectorNode* head;
    int size;
    
    public:
        //! constructor method
        BulletCollector(){
            head = NULL;
            size = 0;
        }
        //! method to insert a node at the beginnig of the list
        void insert(void* ptr){
            CollectorNode* newCollectorNode = (CollectorNode*) malloc(sizeof(CollectorNode*)); 
            newCollectorNode->setMemPtr(ptr);
            newCollectorNode -> setNext(head);
            head = newCollectorNode;
            size++;
        }   
        //! method used to use a bullet
        void* useBullet(){
            CollectorNode* bullet = head;
            head = head->next;
            size--;
            return bullet->getMemPtr();
        }
        //! method to print the list elements
        void printList(){
            CollectorNode* temp = head;
            if(head == NULL){
                cout << "\n" << "Empty collector list";
                return;
            }
            cout << "\n";
            while(temp != NULL){
                cout << temp-> getMemPtr() << " -> ";
                temp = temp->next;
            }
            return;
        }
        //! method used to return the head of the list
        CollectorNode* getHead(){
            return head;
        }
        
        int getSize(){
            return size;
        }
};