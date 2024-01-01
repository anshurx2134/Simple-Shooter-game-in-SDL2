#include"inc/SDL.h"
#include"inc/SDL_image.h"
#include"inc/SDL_mixer.h"

#include<iostream>
#include<vector>
#include<string>
#include"base.h"
#include"assets/player.h"
#include"assets/playerPhysics.h"
#include"assets/background.h"
#include"assets/playerInter.h"
#include"assets/camera.h"
#include"assets/enemy.h"
#include"assets/menu.h"


using namespace std;

void start() { 
  gamewindow* gw;
  Player* p;
  playerPhysics* pPhy;
  Timer* t;
  background* env;
  background* plt;
  landsmoke* ls;
  Camera* c;
  // Enemy* e;
  Bullet* b; // This should be inside player class
  // std::vector<Enemy*> enemies;
  screenBlood* sb;
  gunLightning* gL;
  Mix_Chunk* natureSound1;
  Mix_Chunk* natureSound2;
  Mix_Music* bGMusic;
  if(!bGMusic) {
    SDL_Log("The background music could not be loaded..", SDL_GetError());
  }  
  Menu* m;

  SDL_RendererFlip fliptype = SDL_FLIP_HORIZONTAL;;
  SDL_Event event;
  SDL_Event menuEvent;
  gw = new gamewindow();
  p = new Player();
  t = new Timer();
  env = new background();
  plt = new background();
  ls = new landsmoke();
  c = new Camera(SCREENWIDTH, SCREENHEIGHT, WORLDWIDTH, WORLDHEIGHT);
  // e = new Enemy(gw, ENEMYSPRITEPATH);
  pPhy = new playerPhysics();
  b= new Bullet(gw, BULLETIMAGEPATH);
  sb = new screenBlood(gw, SCREENBLOODIMAGEPATH);
  gL = new gunLightning(gw);
  m = new Menu(gw);
  natureSound1 = Mix_LoadWAV(NATUREBIRDSPATH);
  natureSound2 = Mix_LoadWAV(STREAMANDBIRDSPATH);
  bGMusic = Mix_LoadMUS(BGMUSICPATH);

  

  // SOUND VOLUMES
  Mix_Volume(1, GUNSHOTVOLUME);
  Mix_Volume(2, FOOTSTEPVOLUME);
  Mix_Volume(3, BIRDVOLUME);
  Mix_Volume(4, STREAMANDBIRDSVOLUME);
  Mix_VolumeMusic(MUSICVOLUME);
  Mix_Volume(5, ENEMYDEATHVOLUME);

   
  p->setCoors(300,500);

  bool isJumping = false;
  bool isRunning = false;
  bool isMenuRunning = true;
  bool isGoingUp = true;
  bool isGrounded = true;
  bool iswPressed = false; 
  bool isMovingRight = false;
  bool isMovingLeft = false;
  bool isMoveRightSprite = false;
  bool isMoveLeftSprite = false;
  bool smokeDelayOver = false;
  bool isSmokeAlphaZero = false;
  bool isBulletFired = false;
  bool isPlayerHurt = false;
  bool isGamePaused = false; // This is the pause condition...
  bool isPlayerDeadOnce = false;
  



  p->loadPlayerSpriteTexture(PLAYERSPRITEPATH, gw);
  p->playerSpriteSplit();
  p->setSpriteIndex(3);
  env->loadbgTexture(ENVIRONMENTPATH, gw);
  plt->loadbgTexture(PLATFORMTILEPATH, gw);
  ls->loadInterTexture(LANDSMOKE_SPRITEPATH, gw);
  ls->spritesplit();
  // e->enemySpriteSplit();
  
  float previousSpriteFrame= SDL_GetTicks();
  float enemySpawnPrev = SDL_GetTicks();
  float screenBloodPrev = SDL_GetTicks();
  float gunLightningPrev = SDL_GetTicks();

  
  //The sprite split function being called for the enemy...
  // for(Enemy* enemy : enemies) { 
  //   enemy->enemySpriteSplit();
  // }



  Mix_PlayMusic(bGMusic, -1);
  int smokeAlpha = 255; // The alpha value for the land smoke
  int birdSoundCount = 10000;
  int birdSoundIndex =0;
  int playerReduceHealthCount = 100;
  int playerReduceHealthIndex = 0;

  menu:
  isRunning =false;
  std::vector<Enemy*> enemies;
  while(isMenuRunning) {

    while(SDL_PollEvent(&menuEvent)) {
      if(menuEvent.type == SDL_QUIT) {
        isMenuRunning == false;
        isRunning == false;
        SDL_Quit();
      }

      if(m->isPlayClicked(menuEvent)) {
        isRunning = true;
        isMenuRunning = false;
      }

      if(m->isExitClicked(menuEvent)) {
        // cout<<"The exit button condition is being accessed.."<<endl;
        isMenuRunning = false;
        SDL_Quit();
      }
    }
    gw->clear();
    if(!isPlayerDeadOnce){
      m->renderCopy(gw);
      p->renderMenuPlayer(gw, fliptype);
    }
    else{
      m->renderTryAgain(gw);
      p->renderPlayerCorpse(gw);
    }
    
    gw->render();
    
    
  }
  while(isRunning) {

    if((birdSoundIndex%birdSoundCount) == 0){
      Mix_PlayChannel(3,natureSound1, -1); 
      Mix_PlayChannel(4, natureSound2, -1);
      birdSoundIndex++;
    }
    ls->setCurrentSSpriteIndex(0);
    gL->setLightningPos(p);
    float previousFrame= SDL_GetTicks();

    float enemySpawnCurr = SDL_GetTicks();
    for(int i = 0 ; i<NUMBEROFENEMIES; i++) { 
      // cout<<"The difference between the previous and the current enemy spawn time frames :"<<enemySpawnCurr-enemySpawnPrev<<endl;
      if(enemySpawnCurr-enemySpawnPrev> ENEMYSPAWNDELAY) {
        // cout<<"Entered this condition..."<<endl;
        Enemy* enemy = new Enemy(gw, ENEMYSPRITEPATH);
        enemies.push_back(enemy);
        enemy->enemySpriteSplit();
        enemySpawnPrev = enemySpawnCurr;
      }
    }
    
    
    if(smokeAlpha<=0) {
      isSmokeAlphaZero = true;
    }
    else {
      isSmokeAlphaZero = false;
    }

    // while(SDL_PollEvent(&menuEvent) && isGamePaused) {
    //   // cout<<"This menu loop entered..."<<endl;
    //   if(menuEvent.type == SDL_QUIT) {
    //     isRunning = false;
    //     SDL_Quit();
    //   }
    //   // if(menuEvent.type == SDL_MOUSEBUTTONDOWN && menuEvent.button.button == SDL_BUTTON_LEFT)
    //   // {
    //   //   int mouseX, mouseY;
    //   //   // cout<<"Entered the Play Button loop..."<<endl;
    //   //   // cout<<"The x and the y coordinates of the mouse..."<< mouseX<<" "<< mouseY<<endl;
    //   //   SDL_GetMouseState(&mouseX, &mouseY);
    //   //   if(m->isPlayGame(mouseX, mouseY)) {
    //   //     // cout<<"The play button was clicked..."<<endl;
    //   //     isGamePaused = false;
    //   //   }
    //   // }
    //   if(m->isMouseClicked(menuEvent) && isGamePaused) {
    //     cout<<"The play button was clicked..."<< endl;
    //     isGamePaused = false;
    //   }
    // }
    
   
      // cout<<"The main unpaused condition is being accessed..."<<endl;
      while(SDL_PollEvent(&event)) {
      // cout<<"The main game event loop is accessed..."<<endl;
        if(event.type == SDL_QUIT) { 
          isRunning=false;
          SDL_Quit();

        }

        if(event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_d) { 
          // cout<<"This condition is accessed ...."<<endl;
          isMovingRight = true;
          isMovingLeft = false;
          isMoveRightSprite = true;
          
          
          pPhy->moveRight(p);
          p->setSpriteIndex(4);
        }

        if(event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_a) { 
          isMovingLeft = true;
          isMovingRight = false;
          isMoveLeftSprite = true;
        
          pPhy->moveLeft(p);
          p->setSpriteIndex(3);
        }

        if(event.type== SDL_KEYDOWN && event.key.keysym.sym == SDLK_w ) { 
          iswPressed =true; 
          isJumping = true;
        
          pPhy->jump(p, isJumping, isGoingUp,previousFrame,isGrounded);
          p->setSpriteIndex(3);
          
          if(isMovingRight) { 
          
            float currentFrameRight = SDL_GetTicks();         
            
            pPhy->moveRight(p);      
              
            p->setSpriteIndex(4);
          }
          else if(isMovingLeft) {
          
            pPhy->moveLeft(p);
            p->setSpriteIndex(3);
          }
            
        }
        if(event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_j) { 
          isBulletFired = true;
          
        }   
        if(event.type == SDL_KEYUP && event.key.keysym.sym == SDLK_w) { 
          iswPressed = false;
          isMovingLeft = false;
          isMovingRight = false;
        }
        if(event.type == SDL_KEYUP && event.key.keysym.sym == SDLK_d) {
          isMoveRightSprite = false;
        }
        if(event.type == SDL_KEYUP && event.key.keysym.sym == SDLK_a) {
          isMoveLeftSprite = false;
        } 
      
    }

    if(iswPressed== false) { 
        
        pPhy->jumpInterrupt(p, previousFrame, t);
        
        if(isMoveRightSprite) { 
          p->setSpriteIndex(4);
        }
        else if(isMoveLeftSprite) { 
          p->setSpriteIndex(3);

        }
        else { 
          p->setSpriteIndex(5);
        } 
        if(p->getRect().y >= 500 && !isSmokeAlphaZero) {
          
          ls->smokeFadeOut(smokeDelayOver, smokeAlpha, previousSpriteFrame);  
          
      }
    
    }
    if(isBulletFired) {
      b->bulletMove();
      if(b->getBulletRect().x >=1200) {
        isBulletFired = false;
      }
    }
    // e->enemyMove();
    for(Enemy* enemy : enemies) { 
      if(!enemy->getEnemyDeathStatus()){
        enemy->enemyMove();
      }
    }
    if(p->getRect().x < -50) {
      p->setCoors(-50, p->getRect().y);
    }
    if(p->getRect().x > SCREENWIDTH-p->getRect().w+50) {
      p->setCoors(SCREENWIDTH-p->getRect().w+50, p->getRect().y);
    }

    
    
    
    c->update(p);
    if(!isBulletFired){
      b->bulletPosUpdate(p);
    }
     gL->updateAnim(); // For the gun Lightning animation...
        
    gw->clear();   
    SDL_Rect viewport = c->getViewPort();     
    env->envrendercopy(0,-100,gw, c);
    plt->pltrendercopy(0, -20, gw, c);
    p->rendercopy(gw);
    if(isBulletFired){
      b->renderCopy(gw);
      gL->renderCopy(gw);
    }

    // Collision detection for bullets
    for(Enemy* enemy: enemies) {
      bool collided = b->isCollision(enemy);
      if(collided && isBulletFired) {
        // cout<<"Its hitting the fucking enemy!"<<endl;
        enemy->setEnemySpriteIndex(0);
        enemy->reduceEnemyHealth();
        if(enemy->getEnemyHealth()<=0) {
          // cout<<"Enemy Dead..."<< endl;
          enemy->enemyDead();
          enemy->loadEnemyDeathTexture(gw, ENEMYDEATHPATH);
          

        }
      }
     
    }


    // Collision detection for checking if the enemy is colliding with the player...
    for(Enemy* enemy: enemies) { 
      bool collided = enemy->isPlayerCollision(p);
      if(collided && !enemy->getEnemyDeathStatus()) {
        // cout<<"The enemy is hitting the player..."<<endl;
        isPlayerHurt = true;
        if(playerReduceHealthIndex%playerReduceHealthCount == 0) {
          p->reduceHealth();
        }
        playerReduceHealthIndex++;
        if(p->getPlayerHealth()<=0) {
          
          isMenuRunning = true;
          p->setPlayerHealth(PLAYERTOTALHEALTH);
         
          // This part over here!!!!!!!!!!!
          // for(Enemy* enemy: enemies) {
          //   delete enemy;
          // }
          // enemies.clear();
          isPlayerDeadOnce = true;
          goto menu;
          
          // cout<<"YOU DIED..."<<endl;
        }
      }
      else if(!collided ) {
        // cout<<"Not collided condition entered..."<<endl;
        isPlayerHurt = false;
      }
    }
    // cout<<"Is the player hurt now? "<<isPlayerHurt<<endl;
    // cout<<"The player health..."<<p->getPlayerHealth()<<endl;

    // b->renderRect(gw);
    // e->enemyRenderRect(gw); 
    // e->enemyRenderCopy(gw, c);
   

    for(Enemy* enemy: enemies) { 
      if(enemy->getEnemyHealth()>0){
        // enemy->enemyRenderRect(gw);
        enemy->enemyRenderCopy(gw, c);
        
      
      // Dont forget about this shit... !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
        if(isPlayerHurt) {
          sb->setScreenBloodAlpha(255);
          sb->renderCopy(gw);
      }
      }
      else {
       
        
        enemy->setDeathXandY(enemy->getEnemyRect().x+40, enemy->getEnemyRect().y + 190);
        enemy->renderEnemyDeath(gw, c);
        

        
      }
      
    }

    if(isGamePaused){
      m->renderCopy(gw);
    }

   
    for(Enemy* enemy : enemies) {
      if(enemy->getEnemyDeathStatus()) {
        
        enemy->playEnemyDeathSound();
        if(!enemy->isDiedOnce()){

        }
        enemy->diedOnce();
       
      }
      
    }

    
    

    if(p->getRect().y >= 500 && !isSmokeAlphaZero){
      ls->landSmokeRenderCopy(p,gw);
    }
    if(isSmokeAlphaZero && iswPressed) {
      smokeAlpha = 255;
    }

    // SDL_RenderSetClipRect(gw->getRenderer(), nullptr);    
    gw->render();
    
  }

delete p;
delete gw;
delete pPhy;
delete t;
delete env;
delete plt;
delete ls;
delete c;
// delete e;
delete b;
delete gL;
delete m;

for(Enemy* enemyptr: enemies) { 
  delete enemyptr;
}

enemies.clear();

Mix_FreeChunk(natureSound1);
Mix_FreeChunk(natureSound2);
Mix_FreeMusic(bGMusic);
Mix_CloseAudio();
}