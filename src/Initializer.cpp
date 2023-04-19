#include <iostream>
#include <stdio.h>

using namespace std;

//!Initializer class, used to initialize the game parameters
class Initializer{
    private:
        int level;
        int bullets;
        int spaceshipsPerWave;
        int spaceshipsSpeed;
        int phases;
        int bulletDamage;

        //!method used to initialize the game parameters
        void setValues(int level){
            //! 1=easy, 2=medium, 3=hard
            if(level == 1){
                bullets = 50;
                spaceshipsPerWave = 5;
                spaceshipsSpeed = 1; // values between 1 and 2
                phases = 1;
                bulletDamage = 25;

            }else if(level == 2){
                bullets = 95;
                spaceshipsPerWave = 5;
                spaceshipsSpeed = 2.4;// values between 2 and 3
                phases = 2;
                bulletDamage = 25;

            }else if(level == 3){
                bullets = 140;
                spaceshipsPerWave = 6;
                spaceshipsSpeed = 3;// values between 3 and 4
                phases = 3;
                bulletDamage = 50;
            }
        }
        
    public:
        //!method used to set the difficulty level of the game
        void setLevel (int difficulty) {
            level = difficulty;
            setValues(difficulty);
        }
        //!method used to set the damage of the bullets
        void setDamage(int damage){
            bulletDamage = damage;
        }
        //!method used to return the level of the game
        int getLevel(){
            return level;
        }
        //!method used to return the bullet number
        int getBullets(){
            return bullets;
        }
        //!method used to return the phases of the game
        int getPhases(){
            return phases;
        }
        //!method used to return the spaceships per wave
        int getSpaceshipsPerWave(){
            return spaceshipsPerWave;
        }
        //!method used to return the spaceships speed
        int getSpaceshipsSpeed(){
            return spaceshipsSpeed;
        }
        //!method used to return the damage of the bullets
        int getBulletDamage(){
            return bulletDamage;
        }
};