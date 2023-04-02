#include <iostream>
#include <stdio.h>
#include "SpaceshipNode.cpp"
using namespace std;

class SpaceshipList{

    SpaceshipNode* head;
    public:
        SpaceshipList(){
            head = NULL;
        }

        void insert(int data){
            SpaceshipNode* newNode = new SpaceshipNode(data);
            newNode -> setNext(head);
            head = newNode;
        }

        SpaceshipNode* removeAux(SpaceshipNode* node){
            SpaceshipNode* temp = head;
            delete node;
            while (temp != NULL){
                
                if(temp -> getID() == node -> getID()){
                    head = head -> getNext();
                    return temp;
                }
                else if (temp -> getNext() -> getID() == node -> getID()){
                    temp -> setNext(temp -> getNext() -> getNext());
                    return temp;
                }
                else{
                    temp = temp -> getNext();
                }
            }
            return 0;
        }

        int remove(int value){
            SpaceshipNode* temp = head;
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

        int prinList(){
            SpaceshipNode* temp1 = head;
            if(head == NULL){
                cout << "lista vacía" << "\n";
            }
            else{
                while (temp1 != NULL){
                    cout << temp1 -> getID() << "->";
                    temp1 = temp1 -> getNext();
                }
            }
            return 0;
        }

        SpaceshipNode* getHead(){
            return head;
        }

        void setHead(SpaceshipNode* data){
            head = data;
        }
};