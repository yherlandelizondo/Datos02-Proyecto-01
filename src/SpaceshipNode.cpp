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
        float xCoord;
        int yCoord;
        SpaceshipNode* next;
        bool yMovement;
        int selectedSprite;
        int wave;
        float enemieSpeed;
        int upOrDown;
        ALLEGRO_BITMAP *enemySprite = NULL;
        ALLEGRO_BITMAP *sprite;

        bool randomBool(){
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

        SpaceshipNode(int identifier, int waveNum, int yCoor, int speed, int randSprite, int direction){
            this -> id = identifier;
            this -> wave = waveNum;
            this -> next = NULL;
            this -> xCoord = 650;
            this -> yCoord = yCoor;
            this -> health = 0;
            this -> upOrDown = direction;
            this -> yMovement = randomBool();
            this -> randomBool();
            this -> selectedSprite = randSprite;
            this -> sprite = applySprite();
            this -> enemieSpeed = speed;
            this -> setHealth();
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
        ALLEGRO_BITMAP* applySprite(){
            if(selectedSprite == 0){
                enemySprite = al_load_bitmap("./sprites/sprite_blueEnemy.png");
            }else if(selectedSprite == 1){
                enemySprite = al_load_bitmap("./sprites/sprite_greenEnemy.png");
            }else if(selectedSprite == 2){
                enemySprite = al_load_bitmap("./sprites/sprite_redEnemy.png");
            }else if(selectedSprite == 3){
                enemySprite = al_load_bitmap("./sprites/sprite_purpleEnemy.png");
            }else if(selectedSprite == 4){
                enemySprite = al_load_bitmap("./sprites/sprite_whiteEnemy.png");
            }
            return enemySprite;
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
            if(upOrDown == 0){
                if(yCoord + 1 < 435){
                    yCoord += 1;
                }else{
                    yCoord = 435;
                }
            }else{
                if(yCoord - 1 > 0){
                    yCoord -= 1;
                }else{
                    yCoord = 0;
                }
            }
        }
        int getWave(){
            return wave;
        }

        ALLEGRO_BITMAP* getColor(){
            return sprite;
        }
        int getYMovement(){
            return yMovement;
        }
        int getHealth(){
            return health;
        }
        void setSpeed(float speed){
            if(speed > 0){
                enemieSpeed = speed;
            }
        }
        int getSpeed(){
            return enemieSpeed;
        }

};
