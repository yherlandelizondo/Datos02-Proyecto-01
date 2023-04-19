#include <iostream>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <allegro5/allegro5.h>
#include <allegro5/allegro_image.h>
using namespace std;

//! SpaceshipNode class, used to store Nodes of SpaceshipList
class SpaceshipNode{
    private:
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
        
        //!method used to generate a random boolean
        bool randomBool(){
            random = rand()%2;
            if(random){
                return true;
            }
            return false;    
        }
        //!method used to set the health of the enemies
        void setHealth(){
            for(int i = 0; i <= wave; i++){
                health += 10;
            }
        }

    public:
        //!constructor method
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
        //!method used to set the id of the node
        void setID(int identifier){
            id = identifier;
        }
        //!method used to return the id of the node
        int getID(){
            return id;
        }
        //!method used to set the next node
        void setNext(SpaceshipNode* ptr){
            next=ptr;
        }
        //!method used to get the next node
        SpaceshipNode* getNext(){
            return next;
        }
        //!method used to apply the damage to the spaceship
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
        //!method used to load and return the sprite of the spaceship
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
        //!method used to return the x coord of the spaceship
        int getXCoord(){
            return xCoord;
        }
        //!method used to return the y coord of the spaceship
        int getYCoord(){
            return yCoord;
        }
        //!method used to modify the x coord of the spaceship
        void modifyXCoord(){
            xCoord -= enemieSpeed;
        }
        //!method used to modify the y coord of the spaceship
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
        //!method used to return the wave number
        int getWave(){
            return wave;
        }
        //!method used to get the color of some enemie
        ALLEGRO_BITMAP* getColor(){
            return sprite;
        }
        //!method used to return if some enemie can move up or down
        int getYMovement(){
            return yMovement;
        }
        //!method used to get the health of the spaceship
        int getHealth(){
            return health;
        }
        //!method used to set the speed of the enemies
        void setSpeed(float speed){
            if(speed > 0){
                enemieSpeed = speed;
            }
        }
        //!method used to get the enemies speed
        int getSpeed(){
            return enemieSpeed;
        }
};
