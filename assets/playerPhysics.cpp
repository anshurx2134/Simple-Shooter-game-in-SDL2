#include"playerPhysics.h"
#include"../defs.h"
#include"../base.h"
#include<iostream>
using namespace std;

playerPhysics::playerPhysics():Player() { 
  
  this->playerVel = 0.0f;
  this->currentTime = 0.0f;
  this->jumpTimer =0.0f;
  this->downJumpTimer = 0.0f;
  this->intJumpTimer = 0.0f;
  this->groundedPos = 500.0f;

  this->currentFootstepIndex = 0;
  this->footstepPaths = {
    PLAYERFOOTSTEP1,
    PLAYERFOOTSTEP2,
    PLAYERFOOTSTEP3,
    PLAYERFOOTSTEP4,
    PLAYERFOOTSTEP5,
    PLAYERFOOTSTEP6,
    PLAYERFOOTSTEP7,
    PLAYERFOOTSTEP8,

  };

  for(int i = 0; i<NUMBEROFFOOTSTEPSOUNDS; ++i) {
    this->footSteps[i] = Mix_LoadWAV((this->footstepPaths[i]).c_str());
  }
  
}

playerPhysics::~playerPhysics() {
  for(int i = 0; i<NUMBEROFFOOTSTEPSOUNDS; ++i) {
    Mix_FreeChunk(this->footSteps[i]);
  }
  Mix_CloseAudio();
}



float playerPhysics::getPlayerPosY() { 
    return static_cast<float>(this->getRect().y);
}




void playerPhysics:: jump(Player* p, bool &isJumping, bool &isGoingUp, float &previousFrame, bool &isGrounded) {
  Timer* t;
  float currentJumptime;
  float lastJumpTime;
  
  const float initialPos = p->getRect().y; 

  SDL_Rect playerSpriteRect = p->getCurrentSprite();

  const float finalPos = this->groundedPos-JUMP_HEIGHT;
  
  if(isGrounded == false) {
    isJumping = false;
  
    currentJumptime = SDL_GetTicks();   
    if(currentJumptime-lastJumpTime >=JUMPDELAY) { 
      isJumping = true;
    } 
  }
  

  if(isJumping && isGoingUp) { 
    float jumpProgress = jumpTimer/JUMP_DURATION;

    

    float newY = static_cast<float>(p->getRect().y);
    
     
    newY = initialPos-JUMP_HEIGHT*Lerp(0.0f,2.0f,jumpProgress);
 

    p->setCoors(p->getRect().x, newY);

   

    jumpTimer+= t->getDeltaTime(previousFrame);  

    if(newY <= finalPos) { 
      
      isGoingUp = false;
      jumpTimer = 0.0f;
      
  }
}
    else {
      if(isGoingUp==false) {
      
  
      float downJumpProgress = downJumpTimer/JUMP_DURATION;

      float downNewY = static_cast<float>(p->getRect().y);

      downNewY = downNewY + JUMP_HEIGHT*Lerp(0.0f,1.0f, downJumpProgress);

      p->setCoors(p->getRect().x, downNewY);
      

      

      downJumpTimer+= t->getDeltaTime(previousFrame);


        if(downNewY >= this->groundedPos) {
          isGoingUp=true;
          isGrounded = false;
          downNewY = this->groundedPos;
          downJumpTimer = 0.0f;
          lastJumpTime = SDL_GetTicks();
          
      }
    }

      
  }
}   


void playerPhysics::jumpInterrupt(Player* p, float &previousFrame, Timer* t) { 
  


  float intJumpProgress = this->intJumpTimer/JUMP_DURATION;
  float intNewY = static_cast<float>(p->getRect().y);



  intNewY = intNewY + JUMP_HEIGHT*Lerp(0.0f,1.0f, intJumpProgress);

  p->setCoors(p->getRect().x, intNewY);
  
  intJumpTimer += t->getDeltaTime(previousFrame);

  if(intNewY >= this->groundedPos) {
    intNewY = this->groundedPos;
    intJumpTimer = 0.0f;
  }
}

void playerPhysics::moveRight(Player* p) {
  this->playFootsteps();
  float playerx = p->getRect().x;
  playerx = playerx + Lerp(7.0f,0.0f, 0.1);

  p->setCoors(playerx, p->getRect().y);

}

void playerPhysics::moveLeft(Player* p) {
  this->playFootsteps();
  float playerx = p->getRect().x;
  playerx = playerx - Lerp(7.0f,2.0f, 0.1);

  p->setCoors(playerx, p->getRect().y);
   
}

void playerPhysics::playFootsteps() {
  Mix_PlayChannel(2, this->footSteps[this->currentFootstepIndex], 0);
  this->currentFootstepIndex = (this->currentFootstepIndex+1)% NUMBEROFFOOTSTEPSOUNDS;
}