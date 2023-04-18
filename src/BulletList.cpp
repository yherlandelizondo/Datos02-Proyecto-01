#include <iostream>
#include <stdio.h>
#include "BulletNode.cpp"
#include "BulletCollector.cpp"
using namespace std;

BulletCollector collector;

class BulletList{
    private:
        BulletNode* head;
        int size;
        int bulletDamage;
        int bullets;

    public:
        //!constructor method
        BulletList(){
            head=NULL;
            size = 0;
            bullets = 0;
        }
        //!method used to insert nodes to collectorList
        void insert(int ID, int damage){
            BulletNode* newNode = new BulletNode(ID, damage);
            newNode -> setNext(head);
            head = newNode;
            this -> bulletDamage = damage;
            size += 1;
        }

        //!This function is used to remove bullets from the list when the bullet hit some enemie
        int hitRemove(int id){
            BulletNode* temp = head;
            while (temp != NULL){
                if(temp -> getID() == id){
                    removeAux(temp, false);
                    return 0;
                }
                else{
                    temp = temp -> getNext();
                }
            }
            return 0;
        }

        //!This function is used to remove bullets from the list when the bullet don't hit an enemie
        int noHitRemove(int id){
            BulletNode* temp = head;
            size -= 1;
            while(temp != NULL){
                if(temp -> getID() == id){
                    removeAux(temp, true);
                    return 0;
                }else{
                    temp = temp->getNext();
                }
            }
            return 0;
        }
        //!auxiliar funtion to delete bullets from the list
        BulletNode* removeAux(BulletNode* node, bool coll){
            BulletNode* temp = head;
            if(coll){
                //!reducing the bullet damage and adding to the collector list
                node->reduceDamage();
                collector.insert(node);
            }
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
        //!method used to print the nodes of the list
        void printList(){
            BulletNode* temp = head;
            if(head == NULL){
                cout << "\n" << "Empty  list\n";
                return;
            }
            cout << "\n";
            while(temp != NULL){
                cout << temp-> getID() << " -> ";
                temp = temp -> getNext();
            }
            return;
        }
        //!method used to return the head pointer of the list
        BulletNode* getHead(){
            return head;
        }
        //!method used to set a new head on the list 
        void setHead(BulletNode* data){
            head = data;
        }   
        //!method used to return the size of the list
        int getSize(){
            return size;
        }
        //!method used to return the number of bullets stored on collectorList
        int getCollectorBullets(){
            bullets = collector.bulletsOnCollector();
            return bullets;
        }
};