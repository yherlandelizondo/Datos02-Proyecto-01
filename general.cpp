#include <iostream>
#include <stdio.h>

using namespace std;



class general{
    public:

        int level;
        int bullets;
        int spacecraft;
        int speed;

        void setLevel (int dificultad) {
            level=dificultad;
        }

        int getLevel (){
            return level;
        }

        void setBullets(int canBullets){
            bullets=canBullets;
        }

        int getBullets(){
            return bullets;
        }

        void setSpacecraft(int canSpacecraft){
            spacecraft=canSpacecraft;
        }

        int getSpacecraft(){
            return spacecraft;
        }

        void setSpeed(int velocidad){
            speed=velocidad;
        }

        int getSpeed(){
            return speed;
        }
};