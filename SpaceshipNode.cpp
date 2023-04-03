#include <iostream>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
using namespace std;

//! falta el id

class SpaceshipNode{
    private:
        int id;
        int health;
        int random;
        int randomCol;
        SpaceshipNode* next;
        bool yMovement;
        int selectedColor;

        int randomColor(){
            srand(time(NULL));
            randomCol = rand()%4;
            cout << random;
            return random;
        }

        bool randomBool(){
            srand(time(NULL));
            random = rand()%2;
            if(random){
                return true;
            }
            return false;    
        }

    public:
        
        SpaceshipNode(){
            health = 100;
            id = 0;
            next = NULL;
            yMovement = randomBool();
            selectedColor = randomColor();
        }

        SpaceshipNode(int identifier){
            this->id = identifier;
            this->next = NULL;
        }

        void setID(int identifier){
            id = identifier;
        }

        int getID(){
            return id;
        }

        void setNext(SpaceshipNode* ptr){
            next=ptr;
        }

        SpaceshipNode* getNext(){
            return next;
        }
        void applyDamage(int damage){
            health -= damage;
        }
        //!function to check the spaceship health, if health =< 0, return false, if not, return true
        bool checkHealth(){
            if(health <= 0){
                return false;
            }else{
                return true;
            }
        }

        
        

};
