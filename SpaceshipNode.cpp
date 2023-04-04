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
        int xCoord;
        int yCoord;
        SpaceshipNode* next;
        bool yMovement;
        int selectedColor;
        int wave;

        int randomColor(){
            srand(time(NULL));
            randomCol = rand()%4;
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
        void setHealth(){
            for(int i = 0; i <= wave; i++){
                health += 10;
            }
        }
    public:
        
        SpaceshipNode(){
            health = 0;
            id = 0;
            next = NULL;
            yMovement = randomBool();
            selectedColor = randomColor();
            xCoord = 550;
            srand(time(NULL));
            yCoord = rand()%430;
        }

        SpaceshipNode(int identifier, int waveNum){
            this -> id = identifier;
            this -> wave = waveNum;
            this -> next = NULL;
            setHealth();
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

        string getColor(){
            if(selectedColor == 0){
                return "sprite_blueEnemy.png";
            }else if(selectedColor == 1){
                return "sprite_greenEnemy.png";
            }else if(selectedColor == 2){
                return "sprite_redEnemy.png";
            }else if(selectedColor == 3){
                return "sprite_purpleEnemy.png";
            }else if(selectedColor == 4){
                return "sprite_whiteEnemy.png";
            }
        }
        int getXCoord(){
            return xCoord;
        }
        int getYCoord(){
            return yCoord;
        }
        
        int getWave(){
            return wave;
        }

};
