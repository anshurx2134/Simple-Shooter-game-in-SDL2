#ifndef PLAYERPHYSICS_H
#define PLAYERPHYSICS_H

#include "player.h"
#include "../base.h"
#include "../inc/SDL_mixer.h"

class playerPhysics : public Player { 
  private:  
    
    float playerVel;
    float currentTime;
    float jumpTimer;
    float groundedPos;
    float downJumpTimer;
    float intJumpTimer;
    Mix_Chunk* footSteps[NUMBEROFFOOTSTEPSOUNDS];
    std::vector<std::string> footstepPaths;
    int currentFootstepIndex;
    
  public:
    playerPhysics();
    ~playerPhysics();
    
    void jump(Player* p, bool &isJumping, bool &isGoingUp, float &previousFrame, bool &isGrounded);
    void jumpInterrupt(Player* p, float &previousFrame, Timer* t);
    void moveRight(Player* p);
    void moveLeft(Player* p);
    float getPlayerPosY();
    void playFootsteps();
    
    
};

#endif