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
            damage = 0;
        }

        BulletNode(int identifier, int dmg){
            this -> id = identifier;
            this -> next = NULL;
            this -> damage = dmg
        }

        void setID(int identifier){
            id = identifier;
        }

        int getID(){
            return id;
        }

        void setNext(BulletNode* ptr){
            next = ptr;
        }

        int getDamage(){
            return damage;
        }

        void reduceDamage(){
            damage /= 2;
        }
        
        BulletNode* getNext(){
            return next;
        }
};