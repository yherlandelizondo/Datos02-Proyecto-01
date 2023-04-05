#include <iostream>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <allegro5/allegro5.h>
#include <allegro5/allegro_image.h>
using namespace std;

//! falta el id

class SpaceshipNode{
    public:
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
        int enemieSpeed;
        int upOrDown;
        ALLEGRO_BITMAP *enemySprite = NULL;

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

        SpaceshipNode(int identifier, int waveNum, int yCoor, int speed){
            this -> id = identifier;
            this -> wave = waveNum;
            this -> next = NULL;
            this -> xCoord = 550;
            this -> yCoord = yCoor;
            this -> health = 0;
            this -> yMovement = randomBool();
            this -> selectedColor = randomColor();
            this -> enemieSpeed = speed;
            setHealth();
            applyColor();
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
        void applyColor(){
            if(selectedColor == 0){
                enemySprite = al_load_bitmap("sprite_blueEnemy.png");
            }else if(selectedColor == 1){
                enemySprite = al_load_bitmap("sprite_greenEnemy.png");
            }else if(selectedColor == 2){
                enemySprite = al_load_bitmap("sprite_redEnemy.png");
            }else if(selectedColor == 3){
                enemySprite = al_load_bitmap("sprite_purpleEnemy.png");
            }else if(selectedColor == 4){
                enemySprite = al_load_bitmap("sprite_whiteEnemy.png");
            }
        }
        int getXCoord(){
            return xCoord;
        }
        int getYCoord(){
            return yCoord;
        }
        void modifyXCoord(){
            xCoord -= enemieSpeed;
        }
        void modifyYCoord(){
            srand(time(0));
            upOrDown = rand()%2;
            if(upOrDown == 0){
                if(yCoord + 10 < 335){
                    yCoord += 10;
                }else{
                    yCoord = 335;
                }
            }else{
                if(yCoord - 10 > 0){
                    yCoord -= 10;
                }else{
                    yCoord = 0;
                }
            }
        }
        int getWave(){
            return wave;
        }

        ALLEGRO_BITMAP* getColor(){
            return enemySprite;
        }
        int getYMovement(){
            return yMovement;
        }

};
