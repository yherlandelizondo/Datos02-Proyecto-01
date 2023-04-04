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

float bulletX = spaceshipX;
float bulletY = spaceshipY;
float timeSinceLastShoot = 0;
bool bulletOnScreen = false;
float shootInterval = 0.1;
int bulletSpeed = 10;
int bullets;
int level;
int spaceshipsSpeed;
int spaceshipsPerWave;
int phases;
int enemies;
int ID = 0;
int specificPhase = 0;

ALLEGRO_TIMER *timer = NULL;
ALLEGRO_BITMAP *spaceShipImage = NULL;
ALLEGRO_BITMAP *blueimage = NULL;
ALLEGRO_BITMAP *purpleimage = NULL;
ALLEGRO_BITMAP *greenimage = NULL;
ALLEGRO_BITMAP *whiteimage = NULL;
ALLEGRO_BITMAP *redimage = NULL;
ALLEGRO_BITMAP *bulletImage = NULL;
ALLEGRO_EVENT_QUEUE *queue = NULL;
ALLEGRO_DISPLAY* disp = NULL;
ALLEGRO_FONT* font = NULL;


//!Function to update the bullet coords
void shootBullet(){
    if(!bulletOnScreen){
        bulletX = spaceshipX;
        bulletY = spaceshipY;
        bulletOnScreen = true;
    }
}

//!Function to update the bullet position
void updateBullet(){
    if(bulletOnScreen){
        bulletX += bulletSpeed;
        if(bulletX > screenWidth && bullets > 0){
            bulletOnScreen = false;
            bullets -= 1;
        }
    }
}

//! Funtion to render the game
void render(){
    al_clear_to_color(al_map_rgb(0, 0, 0));
    al_draw_textf(font, al_map_rgb(255, 255, 255), 0, 0, 0, "BulletSpeed: %.1d Bullets: %.1d", bulletSpeed, bullets);
    al_draw_bitmap(spaceShipImage, spaceshipX, spaceshipY, 0);
    if(bulletOnScreen){
        al_draw_bitmap(bulletImage, bulletX, bulletY, 0);
    }
    srand(time(NULL));
    al_draw_bitmap(blueimage, 550, rand()%430, 1);
    al_draw_bitmap(redimage, 550, rand()%430, 1);
    al_draw_bitmap(greenimage, 550, rand()%430, 1);
    al_draw_bitmap(purpleimage, 550, rand()%430, 1);
    al_draw_bitmap(whiteimage, 550, rand()%430, 1);
    al_flip_display();
}

//! Main funtion
int main()
{
    //!Difficulty selection
    cout << "//////////////////////////////////////////////////////////////////////////\n";
    cout << "Choose the difficulty of the game: \n1 -> Easy\n2 -> Medium\n3 -> Hard\n";
    cout << "//////////////////////////////////////////////////////////////////////////\n";
    cin >> level;

    if(level != 1 && level != 2 && level != 3){
        cout << "Invalid input\n";
        exit;
    }else{
        Initializer* start = new Initializer;
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
        redimage = al_load_bitmap("sprite_redEnemy.png");
        purpleimage = al_load_bitmap("sprite_purpleEnemy.png");
        greenimage = al_load_bitmap("sprite_greenEnemy.png");
        whiteimage = al_load_bitmap("sprite_whiteEnemy.png");
        blueimage = al_load_bitmap("sprite_blueEnemy.png");
        phases = start -> getPhases();
        bullets = start -> getBullets();
        spaceshipsSpeed = start -> getSpaceshipsSpeed();
        spaceshipsPerWave = start -> getSpaceshipsPerWave();
        enemies = phases * 5 * spaceshipsPerWave;

        //! initialization of the spaceship list, and adding all the spaceships to the list
        SpaceshipList* spaceList = new SpaceshipList;

        while(enemies >= (spaceshipsPerWave * 5)){
            specificPhase++;
            for(int i = 0; i != (spaceshipsPerWave * 5); i++){
                spaceList->insert(ID, specificPhase);
                ID++;
            }
            enemies -= (spaceshipsPerWave * 5);
        };
        cout << "list:"<< spaceList->getSize()<<"\n";
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
                    if(key[ALLEGRO_KEY_O]){
                        if(bulletSpeed < 50){
                            bulletSpeed += 1;
                        }
                    }
                    if(key[ALLEGRO_KEY_P]){
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
        al_destroy_display(disp);
        al_destroy_timer(timer);
        al_destroy_event_queue(queue);

        return 0;
        }
};