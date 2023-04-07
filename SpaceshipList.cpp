#include <iostream>
#include <stdio.h>
#include "SpaceshipNode.cpp"
using namespace std;

//!Struct to store the spaceships of some specific wave
struct spaceArray{
    SpaceshipNode* spaceshipsOnWave[10];
    int size = 0;
};

class SpaceshipList{

    SpaceshipNode* head;
    int size;
    int event;
    int auxiliarEvent;
    
    public:
        SpaceshipList(){
            head = NULL;
            size = 0;
            size = 7;
        }

        void insert(int ID, int wave, int yCoord, int enemieSpeed, int randSrite, int direction){
            SpaceshipNode* newNode = new SpaceshipNode(ID, wave, yCoord, enemieSpeed, randSrite, direction);
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
                    cout << temp1 -> getXCoord() << "->";
                    temp1 = temp1 -> getNext();
                }
            }
            return 0;
        }

        SpaceshipNode* getHead(){
            return head;
        }

        struct spaceArray returnSpaceships(int wave){
            SpaceshipNode* temp3 = head;

            struct spaceArray arrayStruct;
            int i = 0;
            
            while (temp3 != NULL){
                if(temp3 -> getWave() == wave){
                    arrayStruct.spaceshipsOnWave[i] = temp3;
                    arrayStruct.size += 1;
                    temp3 = temp3 -> getNext();
                    i++;
                }
                else{
                    temp3 = temp3 -> getNext();
                }
            }
            return arrayStruct;
        }

        void setHead(SpaceshipNode* data){
            head = data;
        }

        int getSize(){
            return size;
        }
        int collitionDetector(int bulletX, int bulletY, int bulletHeight, int bulletLength, int spaceshipX, int spaceshipY, int spaceshipHeight, int spaceshipLength, int wave, int bulletDamage, int enemiesOnScreen){
            //si colisciona con la nave o si la pasó el limite 7, si le da la bala 8 y si no pasa nada 9
            SpaceshipNode* temp4 = head;
            struct spaceArray arrayStruct;
            int l = 0;
            while (temp4 != NULL){
                if(temp4 -> getWave() == wave){    
                    //!check if the bullet touch some enemie.
                    if((bulletY + bulletHeight > temp4 -> getYCoord()) && (bulletY + bulletHeight < temp4 -> getYCoord() + spaceshipLength) && (bulletX + bulletLength > temp4 -> getXCoord()) && (bulletX + bulletLength < temp4 -> getXCoord() + bulletLength)){
                        event = 8;
                        if((temp4->getHealth() - bulletDamage) > 0){
                            temp4->applyDamage(bulletDamage);
                        }else{
                            remove(temp4->getID());
                        } 
                        break;
                    }
                    //!check if the spaceship touch some enemie
                    if((spaceshipY + spaceshipHeight > temp4 -> getYCoord()) && (spaceshipY < temp4 -> getYCoord() + spaceshipHeight) && (spaceshipX + spaceshipLength > temp4 -> getXCoord()) && (spaceshipX + spaceshipLength < temp4 -> getXCoord() + spaceshipLength)){
                        event = 9;
                        break;
                    }
                    //!check if the xCoord of an enemie it's less than 0
                    if(temp4->getXCoord() < 0){
                        event = 10;
                        break;
                    }
                    if(enemiesOnScreen == 0){
                        event = 11;
                        break;
                    }
                }
                temp4 = temp4 -> getNext();
                l++;
            }
            auxiliarEvent = event;
            event = 0;
            return auxiliarEvent;
        } 
};