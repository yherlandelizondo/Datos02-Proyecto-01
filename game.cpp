#include <allegro5/allegro5.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <time.h>
#include <fstream>
#include "./src/BulletList.cpp"
#include "./src/Initializer.cpp"
#include "./src/SpaceshipList.cpp"
#include "./src/StrategyList.cpp"
#include "./data/rapidxml.hpp"
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>

using namespace std;

//! Game variables

SpaceshipList* spaceList = new SpaceshipList;
struct spaceArray spaceshipsOnSomeWave;
Initializer* start = new Initializer;
BulletList* bulletList = new BulletList;
StrategyList* strategyList = new StrategyList;

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
float timeSinceLastShoot, timeSinceLastYUpdate, timeSinceLastPower, timeSinceLastCowUpdate = 0;
bool bulletOnScreen, usingCollector, atomicCowOnScreen = false;
float shootInterval = 0.1;
float cowUpdateInterval = 2;
float powerInterval = 1; //!Variable used to limit the powers
int bulletSpeed = 12;
int level, spaceshipsSpeed, spaceshipsPerWave, phases, enemies, ID, condition, bulletDamage;
int wave, aux1, enemiesOnScreen, enemieXCoord, enemieYCoord, auxiliarDamage;
int bulletID, specificWave, specificWaveForAtomic = 0;
int bullets = 1;
int useCollector = true;
int bulletSoundID = 0;
int atomicCowUsed = false;

//variables for strategies delay
bool startDelay = false;
int temporalID;
float penaltyTime;
string strategyInfo;


ALLEGRO_TIMER *timer = NULL;
ALLEGRO_BITMAP *spaceShipImage = NULL;
ALLEGRO_BITMAP *bulletImage = NULL;
ALLEGRO_BITMAP *enemieSprite = NULL;
ALLEGRO_EVENT_QUEUE *queue = NULL;
ALLEGRO_DISPLAY* disp = NULL;
ALLEGRO_FONT* font = NULL;
ALLEGRO_BITMAP *atomicCow = NULL;
ALLEGRO_BITMAP *auxiliarImage = NULL;
ALLEGRO_SAMPLE *explosion = NULL;
ALLEGRO_SAMPLE *shot = NULL;
ALLEGRO_SAMPLE *moo = NULL;
ALLEGRO_SAMPLE *penalty = NULL;


//!Function to update the bullet coords
void shootBullet(){
    if(!bulletOnScreen && bullets > 0){
        if(bulletSoundID == 1){
            al_play_sample(moo, 0.2, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
        }else{
            al_play_sample(shot, 0.08, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
        }
        bulletX = spaceshipX;
        bulletY = spaceshipY;
        bulletOnScreen = true;
        bullets -= 1;
        bulletList->insert(bulletID, bulletDamage);
    }
}
int strategyLoader(int strategy, string path){
    if(strategy == 1){ //sprinter strategy
        ifstream file(path);
        if (!file.is_open()) {
            cout << "Error: could not open the XML file." << endl;
            return 1;
        }
        //!obtaining the xml content
        string content((istreambuf_iterator<char>(file)), istreambuf_iterator<char>());
        file.close();
        rapidxml::xml_document<> doc;
        doc.parse<0>(&content[0]);

        //!obtaining the increment value
        rapidxml::xml_node<>* powerIncrement = doc.first_node("sprinter_strategy")->first_node("YAxisIncrement");
        int incrementValue = stoi(powerIncrement->value());

        //!Increasing the spaceship speed
        movementDistance += incrementValue;

    }else if(strategy == 2){ //decelerator strategy
        ifstream file(path);
        if (!file.is_open()) {
            cout << "Error: could not open the XML file." << endl;
            return 1;
        }
        //!obtaining the xml content
        string content((istreambuf_iterator<char>(file)), istreambuf_iterator<char>());
        file.close();
        rapidxml::xml_document<> doc;
        doc.parse<0>(&content[0]);

        //!obtaining the reduction value
        rapidxml::xml_node<>* powerReduction = doc.first_node("decelerator_strategy")->first_node("xReduction");
        float reductionValue = stof(powerReduction->value());

        //!Decreasing the spaceship speed
        spaceList->reduceSpeed(reductionValue);

    }else if(strategy == 3){ //cowboy stategy
        ifstream file(path);
        if (!file.is_open()) {
            cout << "Error: could not open the XML file." << endl;
            return 1;
        }
        //!obtaining the xml content
        string content((istreambuf_iterator<char>(file)), istreambuf_iterator<char>());
        file.close();
        rapidxml::xml_document<> doc;
        doc.parse<0>(&content[0]);

        //!obtaining the damageIncrement value
        rapidxml::xml_node<>* damage = doc.first_node("cowboy_strategy")->first_node("damageIncrement");
        int damageIncrement = stoi(damage->value());

        //!Increasing the bullet damage
        auxiliarDamage = bulletDamage;
        bulletDamage += damageIncrement;

        //!obtaining the sprite
        rapidxml::xml_node<>* spritePhath = doc.first_node("cowboy_strategy")->first_node("sprite");
        const char* sprite = spritePhath->first_attribute("path")->value();
        
        //!Loading the sprite
        bulletImage = al_load_bitmap(sprite);
        auxiliarImage = bulletImage;
        bulletSoundID = 1;

    }else{
        if(!atomicCowUsed){
            ifstream file(path);
            if (!file.is_open()) {
                cout << "Error: could not open the XML file." << endl;
                return 1;
            }
            //!obtaining the xml content
            string content((istreambuf_iterator<char>(file)), istreambuf_iterator<char>());
            file.close();
            rapidxml::xml_document<> doc;
            doc.parse<0>(&content[0]);

            //!obtaining the damageIncrement value
            rapidxml::xml_node<>* atomicDamage = doc.first_node("atomicCowboy_strategy")->first_node("damageIncrement");
            int atomicIncrement = stoi(atomicDamage->value());

            //!Increasing the bullet damage
            auxiliarDamage = bulletDamage;
            bulletDamage += atomicIncrement;

            //!obtaining the sprite
            rapidxml::xml_node<>* atomicPath = doc.first_node("atomicCowboy_strategy")->first_node("sprite");
            const char* atomicSprite = atomicPath->first_attribute("path")->value();
            
            //!Loading the sprite
            bulletImage = al_load_bitmap(atomicSprite);
            atomicCowOnScreen = true;

            al_play_sample(moo, 0.08, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
            }
            atomicCowUsed = true;
    }
    
    return 0;
}
//!Function to update the bullet position and add bullet to collector
void updateBullet(){ // verificacion de collisiones
    if(bulletOnScreen){
        bulletX += bulletSpeed;
        if(bullets == 0){
            usingCollector = true; //!variable to check if we are using the collector(used to change on screen text)
            if(useCollector){
                bullets = bulletList->getCollectorBullets();
                start->setDamage(bulletDamage/2);
                useCollector = false;
            }
        }

        if((bulletX > screenWidth) && (bullets > 0)){
            if(atomicCowOnScreen){
                atomicCowOnScreen = false;
                bulletImage = auxiliarImage;
                bulletDamage = auxiliarDamage;
            }
            if(useCollector){ //!check if its necessary to append bullets to the collector list
                bulletList->noHitRemove(bulletID);
            }
            bulletOnScreen = false;
        }
    }
}

void updateEnemies(struct spaceArray enemiesArray){ 
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
    if(usingCollector){
        al_draw_textf(font, al_map_rgb(255, 255, 255), 0, 0, 0, " Actual wave: %.1d Bullets: %.1d UsingCollector: true", specificWave, bullets);
    }else{
        al_draw_textf(font, al_map_rgb(255, 255, 255), 0, 0, 0, " Actual wave: %.1d Bullets: %.1d BulletsOnCollector: %.1d", specificWave, bullets, bulletList->getCollectorBullets());
    }
    if(startDelay){
        if(temporalID == 0){
            al_draw_textf(font, al_map_rgb(255, 0, 0), 0, 15, 0, " %.1f seconds to use sprinter strategy", 5 - penaltyTime);

        }else if(temporalID == 1){
            al_draw_textf(font, al_map_rgb(255, 0, 0), 0, 15, 0, " %.1f seconds to use decelerator strategy", 5 - penaltyTime);

        }else if(temporalID == 2){
            al_draw_textf(font, al_map_rgb(255, 0, 0), 0, 15, 0, " %.1f seconds to use cowboy strategy", 5 - penaltyTime);

        }else if(temporalID == 3){
            al_draw_textf(font, al_map_rgb(255, 0, 0), 0, 15, 0, " %.1f seconds to use atomicCowboy strategy", 5 - penaltyTime);

        } 
    }
    
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
        al_rest(0.2);
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
            condition = spaceList->collitionDetector(bulletX, bulletY, bulletHeight, bulletLength, spaceshipX, spaceshipY, spaceshipHeight, spaceshipLength, specificWave, bulletDamage, enemiesOnScreen);
            //!Using the collition detector return to modify some enemies or finish the game
            if(condition == 8){ //!you hit an enemie with a bullet
                al_play_sample(explosion, 0.05, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
                bulletOnScreen = false;
                if(atomicCowOnScreen){
                    atomicCowOnScreen = false;
                    bulletImage = auxiliarImage;
                    bulletDamage = auxiliarDamage;
                }
                bulletList -> hitRemove(bulletID); 
            
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
                al_rest(0.2);
                exit(1); 

            }else if(condition == 9){
                cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n";
                cout << "*****************************\n";
                cout << "        GAME OVER\n";
                cout << "An enemy hit your spaceship\n";  
                cout << "*****************************\n";
                al_rest(0.2);
                exit(1);

            }else{
                updateEnemies(spaceshipsOnSomeWave);
            }
        }
    al_flip_display(); 
    }
    
}

void setDelay(int ID){
    startDelay = true;
    temporalID = ID;
    penaltyTime = 0;
}

//! Main funtion
int main()
{
    //!Difficulty selection
    cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n";
    cout << "//////////////////////////////////////////////////////////////////////////\n";
    cout << "Choose the difficulty level of the game: \n1 -> Easy\n2 -> Medium\n3 -> Hard\n";
    cout << "//////////////////////////////////////////////////////////////////////////\n";
    cout << "Insert the difficulty level number: ";
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
        al_install_audio();
        al_init_acodec_addon();
        al_reserve_samples(10);
        timer = al_create_timer(1.0 / 60.0);
        queue = al_create_event_queue();
        disp = al_create_display(screenWidth, screenHeight);
        font = al_create_builtin_font();
        spaceShipImage = al_load_bitmap("./sprites/sprite_spaceship.png");
        bulletImage = al_load_bitmap("./sprites/sprite_bullet.png");
        explosion = al_load_sample("aud/explosion.wav");
        shot = al_load_sample("aud/shot.wav");
        moo = al_load_sample("aud/moo.wav");
        penalty = al_load_sample("aud/penalty.wav");
        auxiliarImage = bulletImage;
        phases = start -> getPhases();
        bullets = start -> getBullets();
        bulletDamage = start->getBulletDamage();
        spaceshipsSpeed = start -> getSpaceshipsSpeed();
        spaceshipsPerWave = start -> getSpaceshipsPerWave();
        enemies = phases * 5 * spaceshipsPerWave;
        aux1 = enemies;
        srand(time(0));
        strategyList -> initialize();

        //!initialization of the spaceship list, and adding all the spaceships to the list
        while(aux1 >= spaceshipsPerWave){
            wave++;
            for(int i = 0; i != spaceshipsPerWave; i++){
                spaceList->insert(ID, wave, rand()%430, spaceshipsSpeed, rand()%4, rand()%2);
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

            if(bullets == 0 && useCollector == false){
                cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n";
                cout << "*****************************\n";
                cout << "        GAME OVER\n";
                cout << " You spent all your bullets\n";  
                cout << "*****************************\n";
                al_rest(0.2);
                exit(1);

            }
            al_wait_for_event(queue, &event);
            
            switch(event.type)
            {
                case ALLEGRO_EVENT_TIMER:
                    updateBullet();
                    timeSinceLastCowUpdate += 1.0 / 60.0;
                    timeSinceLastYUpdate += 1.0 / 60.0;
                    timeSinceLastShoot += 1.0 / 60.0;
                    timeSinceLastPower += 1.0 / 60.0;

                    if(startDelay){
                        penaltyTime += 1.0 / 60.0;
                    }
                    
                    if(penaltyTime >= 5.0){
                        strategyList -> loadOnMemory(temporalID);
                        penaltyTime = 0;
                        startDelay = false;
                    }
                    
                    if (timeSinceLastShoot >= shootInterval){
                        if(bulletOnScreen == false){
                            bulletID++;
                        }
                        shootBullet();
                        timeSinceLastShoot = 0;
                    }
                    if(key[ALLEGRO_KEY_W]){
                        if(spaceshipY - movementDistance >= 0){
                            spaceshipY -= movementDistance;
                        }
                    }  
                    if(key[ALLEGRO_KEY_S]){
                        if(spaceshipY - movementDistance <= 435){
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
                        exit(1);
                    }
                    if(key[ALLEGRO_KEY_J]){
                        if(timeSinceLastPower >= powerInterval){
                            if(strategyList -> checkStrategyStatus(0)){
                                strategyLoader(1, strategyList -> getStrategyPath(0));
                                strategyList->removeFromMemory(0);
                            }else{
                                if(!startDelay){
                                    setDelay(0);
                                }else{
                                    al_play_sample(penalty, 0.30, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
                                } 
                            }
                            timeSinceLastPower = 0;
                        }
                    }
                    if(key[ALLEGRO_KEY_K]){
                        if(timeSinceLastPower >= powerInterval){
                            if(strategyList -> checkStrategyStatus(1)){
                                strategyLoader(2, strategyList -> getStrategyPath(1));
                                strategyList->removeFromMemory(1);
                            }else{
                                if(!startDelay){
                                    setDelay(1);
                                }else{
                                    al_play_sample(penalty, 0.30, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
                                } 
                            }
                            timeSinceLastPower = 0;                           
                        }
                    }
                    if(key[ALLEGRO_KEY_L]){
                        if(timeSinceLastPower >= powerInterval){
                            if(strategyList -> checkStrategyStatus(2)){
                                strategyLoader(3, strategyList -> getStrategyPath(2));
                                strategyList->removeFromMemory(2);
                            }else{
                                if(!startDelay){
                                    setDelay(2);
                                }else{
                                    al_play_sample(penalty, 0.30, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
                                } 
                            }
                            timeSinceLastPower = 0;
                            
                        }
                    }
                    if(key[ALLEGRO_KEY_SEMICOLON]){
                        if(!atomicCowUsed){
                            if(timeSinceLastPower >= powerInterval){
                                if(strategyList -> checkStrategyStatus(3)){
                                    strategyLoader(4, strategyList -> getStrategyPath(3));
                                    strategyList->removeFromMemory(3);
                                }else{
                                    if(!startDelay){
                                        setDelay(3);
                                    }else{
                                        al_play_sample(penalty, 0.30, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
                                    }   
                                }
                                timeSinceLastPower = 0;
                            }
                        }
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
                    exit(1);
            }
        }

        al_destroy_font(font);
        al_destroy_bitmap(spaceShipImage);
        al_destroy_bitmap(bulletImage);
        al_destroy_bitmap(enemieSprite);
        al_destroy_bitmap(auxiliarImage);
        al_destroy_bitmap(atomicCow);
        al_destroy_display(disp);
        al_destroy_timer(timer);
        al_destroy_event_queue(queue);
        al_destroy_sample(explosion); 
        al_destroy_sample(shot); 
        al_destroy_sample(moo); 
        al_destroy_sample(penalty); 
        return 0;
        }
};