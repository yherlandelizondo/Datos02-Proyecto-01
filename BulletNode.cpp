#include <iostream>
#include <stdio.h>

using namespace std;

class BulletNode{

    private:
        int id;
        int damage;
        BulletNode* next;

    public:
        BulletNode(){
            id = 0;
            next = NULL;
            damage = 50;
        }

        BulletNode(int identifier){
            this->id=identifier;
            this->next=NULL;
        }

        void setID(int identifier){
            id = identifier;
        }

        int getID(){
            return id;
        }

        void setNext(BulletNode* ptr){
            next=ptr;
        }

        BulletNode* getNext(){
            return next;
        }
};