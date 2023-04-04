#include <iostream>
#include <stdio.h>

using namespace std;

class Initializer{
    private:
        int level = 0;
        int bullets = 0;
        int spaceshipsPerWave = 0;
        int spaceshipsSpeed = 0;
        int phases = 0;
        int bulletDamage = 0;


        void setValues(int level){
            //! 0=easy, 1=medium, 2=hard
            if(level == 1){
                bullets = 130;
                spaceshipsPerWave = 5;
                spaceshipsSpeed = 10;
                phases = 1;
                bulletDamage = 25;

            }else if(level == 2){
                bullets = 300;
                spaceshipsPerWave = 5;
                spaceshipsSpeed = 20;
                phases = 2;
                bulletDamage = 25;

            }else if(level == 3){
                bullets = 600;
                spaceshipsPerWave = 5;
                spaceshipsSpeed = 25;
                phases = 3;
                bulletDamage = 25;
            }
        }
        
    public:
        void setLevel (int difficulty) {
            level = difficulty;
            setValues(difficulty);
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
};