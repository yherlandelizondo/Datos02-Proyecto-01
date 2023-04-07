#include <iostream>
#include <stdio.h>

using namespace std;

class BulletNode{

    private:
        int id;
        int damage;
        BulletNode* next;
        int bulletX;
        int bulletY;
        bool onScreen;

    public:
        BulletNode(){
            id = 0;
            next = NULL;
            damage = 0;
            onScreen = false;
        }

        BulletNode(int identifier, int dmg){
            this -> id = identifier;
            this -> next = NULL;
            this -> damage = dmg;
            this -> onScreen = true;
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