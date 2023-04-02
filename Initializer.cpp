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
        //int spaceshipHealth;
        int bulletDamage;

        //TODO: tambien se puede tomar la vida de las naves aqui

        void setValues(int level){
            //! 0=easy, 1=medium, 2=hard
            switch (level)
            {
            case 0:
                bullets = 200;
                spaceshipsPerWave = 5;
                spaceshipsSpeed = 10;
                phases = 1;
                //spaceshipHealth = 50;
                bulletDamage = 25;

            case 1:
                bullets = 150;
                spaceshipsPerWave = 5;
                spaceshipsSpeed = 20;
                phases = 2;
                //spaceshipHealth = 50;
                bulletDamage = 25;

            case 2:
                bullets = 150;
                spaceshipsPerWave = 5;
                spaceshipsSpeed = 25;
                phases = 3;
                //spaceshipHealth = 50;
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

        int getSpaceshipsPerRound(){
            return spaceshipsPerWave;
        }

        int getSpaceshipsSpeed(){
            return spaceshipsSpeed;
        }
};