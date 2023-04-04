#include <iostream>
#include <stdio.h>
#include "SpaceshipNode.cpp"
using namespace std;

//!Struct to store the spaceships of some specific wave
struct spaceArray{
    /*int maxIndex;

    int setMaxIndex(int index){
        maxIndex = index;
        return 0;
    }*/
    SpaceshipNode* spaceshipsOnWave[10];
};

class SpaceshipList{

    SpaceshipNode* head;
    int size;
    
    public:
        SpaceshipList(){
            head = NULL;
            size = 0;
        }

        void insert(int ID, int wave){
            SpaceshipNode* newNode = new SpaceshipNode(ID, wave);
            size++;
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

        int remove(int id){
            SpaceshipNode* temp = head;
            while (temp != NULL){
                if(temp -> getID() == id){
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

        struct spaceArray returnSpaceships(int wave, int spaceshipsPerWave){

            struct spaceArray arrayStruct;
            //arrayStruct.setMaxIndex(spaceshipsPerWave);
            int i = 0;
            SpaceshipNode* temp3 = head;

            while (temp3 != NULL){
                cout <<"next: "<< temp3->getNext()->getID() << "\n";
                if(temp3 -> getWave() == wave){
                    arrayStruct.spaceshipsOnWave[i] = temp3;
                }
                else{
                    temp3 = temp3 -> getNext();
                }
            }
            i++;
            return arrayStruct;
        }

        void setHead(SpaceshipNode* data){
            head = data;
        }

        int getSize(){
            return size;
        }
};