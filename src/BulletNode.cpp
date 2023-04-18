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
        //!constructor method
        BulletNode(){
            id = 0;
            next = NULL;
            damage = 0;
            onScreen = false;
        }
        //!constructor method
        BulletNode(int identifier, int dmg){
            this -> id = identifier;
            this -> next = NULL;
            this -> damage = dmg;
            this -> onScreen = true;
        }
        //!method used to set the ID value 
        void setID(int identifier){
            id = identifier;
        }
        //!method used to return the node ID
        int getID(){
            return id;
        }
        //!method used to set the next value 
        void setNext(BulletNode* ptr){
            next = ptr;
        }
        //!method used to return the damage value
        int getDamage(){
            return damage;
        }
        //!method used to reduce the damage of some node to the half
        void reduceDamage(){
            damage /= 2;
        }
        //!method used to return the next node
        BulletNode* getNext(){
            return next;
        }
};