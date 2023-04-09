#include<iostream>
#include<stdio.h>
#include "CollectorNode.cpp"
using namespace std;

class BulletCollector{
    
    CollectorNode* head;
    int bulletNum;
    int bulletDamage;
    
    public:
        //! constructor method
        BulletCollector(){
            head = NULL;
            this -> bulletNum = 0;
            
        }
        //! method to insert a node at the beginnig of the list
        void insert(void* ptr){
            bulletNum++;
            CollectorNode* newCollectorNode = (CollectorNode*) malloc(sizeof(CollectorNode*)); 
            newCollectorNode->setMemPtr(ptr);
            newCollectorNode -> setNext(head);
            head = newCollectorNode;
        }   
        //! method used to return the number of bullets stored on collector list
        int bulletsOnCollector(){
            return bulletNum;
        }
        void setDamage(int damage){
            bulletDamage = damage;
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
        
        int getDamage(){
            return bulletDamage;
        }
};