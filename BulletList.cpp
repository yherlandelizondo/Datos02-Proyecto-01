#include <iostream>
#include <stdio.h>
#include "bulletNode.cpp"

using namespace std;

class BulletList{

    BulletNode* head;

    public:
        BulletList(){
            head=NULL;
        }

        void insert(int data){
            BulletNode* newNode = new BulletNode(data);
            newNode -> setNext(head);
            head = newNode;
        }

        BulletNode* removeAux(BulletNode* node){
            BulletNode* temp = head;
            delete node;
            while(temp != NULL){
                if(temp -> getID() == node -> getID()){
                    head = head -> getNext();
                    return temp;
                }
                else if(temp -> getNext() -> getID()== node -> getID()){
                    temp -> setNext(temp -> getNext()->getNext());
                    return temp;
                }
                else{
                    temp = temp -> getNext();
                }
            }
            return 0;
        }

        int remove(int value){
            BulletNode* temp = head;
            while (temp != NULL){
                if(temp -> getID() == value){
                    removeAux(temp);
                    return 0;
                }
                else{
                    temp = temp -> getNext();
                }
            }
            return 0;
        }

        BulletNode* getHead(){
            return head;
        }

        void setHead(BulletNode* data){
            head = data;
        }   
};