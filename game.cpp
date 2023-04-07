#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <time.h>
#include "Initializer.cpp"
#include "SpaceshipList.cpp"
#include <allegro5/allegro5.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>

using namespace std;

//! Game variables
bool done = false;
ALLEGRO_EVENT event;

float spaceshipY = 215;
float spaceshipX = 20;

int movementDistance = 5;

int screenWidth = 640;
int screenHeight = 480;

int bulletHeight = 40;
int bulletLength = 40;
int spaceshipHeight = 46;
int spaceshipLength = 80;

float bulletX = spaceshipX;
float bulletY = spaceshipY;
float timeSinceLastShoot, timeSinceLastYUpdate = 0;
bool bulletOnScreen = false;
float shootInterval = 0.1;
int bulletSpeed = 20;
int bullets, level, spaceshipsSpeed, spaceshipsPerWave, phases, enemies, ID, condition;
int wave, aux1, enemiesOnScreen, enemieXCoord, enemieYCoord;
int specificWave = 0;


ALLEGRO_TIMER *timer = NULL;
ALLEGRO_BITMAP *spaceShipImage = NULL;
ALLEGRO_BITMAP *bulletImage = NULL;
ALLEGRO_BITMAP *enemieSprite = NULL;
ALLEGRO_EVENT_QUEUE *queue = NULL;
ALLEGRO_DISPLAY* disp = NULL;
ALLEGRO_FONT* font = NULL;

SpaceshipList* spaceList = new SpaceshipList;
struct spaceArray spaceshipsOnSomeWave;
Initializer* start = new Initializer;

//!Function to update the bullet coords
void shootBullet(){
    if(!bulletOnScreen){
        bulletX = spaceshipX;
        bulletY = spaceshipY;
        bulletOnScreen = true;
    }
}

//!Function to update the bullet position
void updateBullet(){ // verificacion de collisiones
    if(bulletOnScreen){
        bulletX += bulletSpeed;
        if(bulletX > screenWidth && bullets > 0){
            bulletOnScreen = false;
            bullets -= 1;
        }
    }
}

void updateEnemies(struct spaceArray enemiesArray){ //recordar restar el valor de size en el stuct
    for(int j = 0; j < enemiesArray.size; j++){
        if(enemiesArray.spaceshipsOnWave[j]->getYMovement()){
            enemiesArray.spaceshipsOnWave[j]->modifyXCoord();
            enemiesArray.spaceshipsOnWave[j]->modifyYCoord();
            timeSinceLastYUpdate = 0;  
        }else{
            enemiesArray.spaceshipsOnWave[j]->modifyXCoord();
        }
        enemieSprite = spaceshipsOnSomeWave.spaceshipsOnWave[j]->getColor();
        enemieXCoord = spaceshipsOnSomeWave.spaceshipsOnWave[j]->getXCoord();
        enemieYCoord = spaceshipsOnSomeWave.spaceshipsOnWave[j]->getYCoord();
        al_draw_bitmap(enemieSprite, enemieXCoord, enemieYCoord, 1);
    }
}

//! Funtion to render the game
void render(){
    al_clear_to_color(al_map_rgb(0, 0, 0));
    al_draw_textf(font, al_map_rgb(255, 255, 255), 0, 0, 0, " Actual wave: %.1d Bullets: %.1d EnemiesOnScreen: %.1d", specificWave, bullets, enemiesOnScreen);
    al_draw_bitmap(spaceShipImage, spaceshipX, spaceshipY, 0);

    if(bulletOnScreen){
        al_draw_bitmap(bulletImage, bulletX, bulletY, 0);
    }
    if (specificWave == phases * 5 + 1){
        cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n";
        cout << "*****************************\n";
        cout << "           YOU WON\n";
        cout << "       CONGRATULATIONS!\n";  
        cout << "*****************************\n";
        exit(1); 
    }
    else{
        if (enemiesOnScreen == 0){
            specificWave += 1;

            if(specificWave < phases * 5 + 1){
                spaceshipsOnSomeWave = spaceList->returnSpaceships(specificWave);
                enemiesOnScreen = spaceshipsOnSomeWave.size;

                for(int i = 0; i < spaceshipsPerWave; i++){
                    enemieSprite = spaceshipsOnSomeWave.spaceshipsOnWave[i]->getColor();
                    enemieXCoord = spaceshipsOnSomeWave.spaceshipsOnWave[i]->getXCoord();
                    enemieYCoord = spaceshipsOnSomeWave.spaceshipsOnWave[i]->getYCoord();
                    al_draw_bitmap(enemieSprite, enemieXCoord, enemieYCoord, 1);
                }
                updateEnemies(spaceshipsOnSomeWave);
            }
            
        }else{
            //!collition detector:
            condition = spaceList->collitionDetector(bulletX, bulletY, bulletHeight, bulletLength, spaceshipX, spaceshipY, spaceshipHeight, spaceshipLength, specificWave, start->getBulletDamage(), enemiesOnScreen);
    
            //!Using the collition detector return to modify some enemies or finish the game
            if(condition == 8){ //!you hit an enemie with a bullet
                cout << "hi boyyyyy\n";
                bulletOnScreen = false;
                timeSinceLastYUpdate = 0;
                spaceshipsOnSomeWave = spaceList->returnSpaceships(specificWave);
                enemiesOnScreen = spaceshipsOnSomeWave.size;

                for(int i = 0; i < spaceshipsOnSomeWave.size; i++){
                    enemieSprite = spaceshipsOnSomeWave.spaceshipsOnWave[i]->getColor();
                    enemieXCoord = spaceshipsOnSomeWave.spaceshipsOnWave[i]->getXCoord();
                    enemieYCoord = spaceshipsOnSomeWave.spaceshipsOnWave[i]->getYCoord();
                    al_draw_bitmap(enemieSprite, enemieXCoord, enemieYCoord, 1);
                }
                updateEnemies(spaceshipsOnSomeWave);
            
            }else if(condition == 10){
                cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n";
                cout << "*****************************\n";
                cout << "        GAME OVER\n";
                cout << " An enemy crossed the limit\n";  
                cout << "*****************************\n";
                exit(1);   

            }else if(condition == 9){
                cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n";
                cout << "*****************************\n";
                cout << "        GAME OVER\n";
                cout << "An enemy hit your spaceship\n";  
                cout << "*****************************\n";
                exit(1);  

            }else{
                updateEnemies(spaceshipsOnSomeWave);
            }
        }
    al_flip_display(); 
    }
    
}
//! Main funtion
int main()
{
    //!Difficulty selection
    cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n";
    cout << "//////////////////////////////////////////////////////////////////////////\n";
    cout << "Choose the difficulty of the game: \n1 -> Easy\n2 -> Medium\n3 -> Hard\n";
    cout << "//////////////////////////////////////////////////////////////////////////\n";
    cout << "Insert the difficulty number: ";
    cin >> level;

    if(level != 1 && level != 2 && level != 3){
        cout << "Invalid input\n";
        exit(1);
    }else{
        start->setLevel(level);

        //!Components initialization
        al_init();
        al_install_keyboard();
        al_init_image_addon();
        timer = al_create_timer(1.0 / 60.0);
        queue = al_create_event_queue();
        disp = al_create_display(screenWidth, screenHeight);
        font = al_create_builtin_font();
        spaceShipImage = al_load_bitmap("sprite_spaceship.png");
        bulletImage = al_load_bitmap("sprite_bullet.png");
        phases = start -> getPhases();
        bullets = start -> getBullets();
        spaceshipsSpeed = start -> getSpaceshipsSpeed();
        spaceshipsPerWave = start -> getSpaceshipsPerWave();
        enemies = phases * 5 * spaceshipsPerWave;
        aux1 = enemies;
        srand(time(0));

        //!initialization of the spaceship list, and adding all the spaceships to the list
        while(aux1 >= spaceshipsPerWave){
            wave++;
            for(int i = 0; i != spaceshipsPerWave; i++){
                spaceList->insert(ID, wave, rand()%430, start->getSpaceshipsSpeed(), rand()%4, rand()%2);
                ID++;
            }
            aux1 -= spaceshipsPerWave;
        }

        spaceshipsOnSomeWave = spaceList->returnSpaceships(1);
        al_register_event_source(queue, al_get_keyboard_event_source());
        al_register_event_source(queue, al_get_display_event_source(disp));
        al_register_event_source(queue, al_get_timer_event_source(timer));

        //!Antialiasing
        al_set_new_display_option(ALLEGRO_SAMPLE_BUFFERS, 1, ALLEGRO_SUGGEST);
        al_set_new_display_option(ALLEGRO_SAMPLES, 8, ALLEGRO_SUGGEST);
        al_set_new_bitmap_flags(ALLEGRO_MIN_LINEAR | ALLEGRO_MAG_LINEAR);

        unsigned char key[ALLEGRO_KEY_MAX];
        memset(key, 0, sizeof(key));

        #define KEY_SEEN     1
        #define KEY_RELEASED 2

        al_start_timer(timer);

        //!Main loop
        while(1)
        {
            al_wait_for_event(queue, &event);

            switch(event.type)
            {
                case ALLEGRO_EVENT_TIMER:
                    updateBullet();
                    timeSinceLastYUpdate += 1.0 / 60.0;
                    timeSinceLastShoot += 1.0 / 60.0;
                    if (timeSinceLastShoot >= shootInterval){
                        shootBullet();
                        timeSinceLastShoot = 0;
                    }
                    if(key[ALLEGRO_KEY_W]){
                        if(spaceshipY == 0){
                            spaceshipY = 0;
                        }else{
                            spaceshipY -= movementDistance;
                        }
                    }  
                    if(key[ALLEGRO_KEY_S]){
                        if(spaceshipY == 435){
                            spaceshipY = 435;
                        }else{
                            spaceshipY += movementDistance;
                        }
                    }   
                    if(key[ALLEGRO_KEY_D]){
                        if(bulletSpeed < 50){
                            bulletSpeed += 1;
                        }
                    }
                    if(key[ALLEGRO_KEY_A]){
                        if(bulletSpeed > 5){
                            bulletSpeed -= 1;
                        }
                    } 
                    if(key[ALLEGRO_KEY_ESCAPE]){
                        done = true;
                    }
                        
                    for(int i = 0; i < ALLEGRO_KEY_MAX; i++)
                        key[i] &= KEY_SEEN;
                    
                    render();
                    break;

                case ALLEGRO_EVENT_KEY_DOWN:
                    key[event.keyboard.keycode] = KEY_SEEN | KEY_RELEASED;
                    break;
                case ALLEGRO_EVENT_KEY_UP:
                    key[event.keyboard.keycode] &= KEY_RELEASED;
                    break;

                case ALLEGRO_EVENT_DISPLAY_CLOSE:
                    done = true;
                    break;
            }

            if(done)
                break;
        }

        al_destroy_font(font);
        al_destroy_bitmap(spaceShipImage);
        al_destroy_bitmap(bulletImage);
        al_destroy_bitmap(enemieSprite);
        al_destroy_display(disp);
        al_destroy_timer(timer);
        al_destroy_event_queue(queue);
        
        return 0;
        }
};