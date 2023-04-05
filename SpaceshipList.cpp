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
    
    public:
        SpaceshipList(){
            head = NULL;
            size = 0;
        }

        void insert(int ID, int wave, int yCoord, int enemieSpeed){
            SpaceshipNode* newNode = new SpaceshipNode(ID, wave, yCoord, enemieSpeed);
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
                    cout << temp1 -> getWave() << "->";
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
        //funcion que resiva las coordedas de la nuestra nave y de la bala y la oleada. y 
        //que las verifique con los enemigos que hayan. Retorna true si hay una colision. tomar en cuenta los rangos 
        //en la coordenada y, y la coordenada x.

        // collitionDetector(bx, by, bh, sx, sy, sh, wave)
        //que devuelva 4 valores, 1 indica si hubo colision minave/enemigo, 2 lo contrario a la 1
        //3 indica colision bala/enemigo, 4 lo contrario a la 3
};