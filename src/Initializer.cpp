#include <iostream>
#include <stdio.h>

using namespace std;

class Initializer{
    private:
        int level;
        int bullets;
        int spaceshipsPerWave;
        int spaceshipsSpeed;
        int phases;
        int bulletDamage;


        void setValues(int level){
            //! 0=easy, 1=medium, 2=hard
            if(level == 1){
                bullets = 50;//130
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
        void setLevel (int difficulty) {
            level = difficulty;
            setValues(difficulty);
        }

        void setDamage(int damage){
            bulletDamage = damage;
        }

        int getLevel (){
            return level;
        }

        int getBullets(){
            return bullets;
        }

        int getPhases(){
            return phases;
        }
        int getSpaceshipsPerWave(){
            return spaceshipsPerWave;
        }

        int getSpaceshipsSpeed(){
            return spaceshipsSpeed;
        }
        int getBulletDamage(){
            return bulletDamage;
        }
};