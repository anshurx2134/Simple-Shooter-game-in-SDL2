#ifndef ENEMY_H
#define ENEMY_H

#include"../inc/SDL.h"
#include"../inc/SDL_image.h"
#include"../base.h"
#include<iostream>
#include<string>
#include"../defs.h"
#include"../base.h"
#include"camera.h"

class Enemy { 
  private:
    SDL_Texture* enemyTexture;
    SDL_Texture* enemyDeathTexture;
    SDL_Rect enemyRect;
    SDL_Rect enemyDeathRect;
    SDL_Rect enemySpriteRect[8];
    SDL_Rect enemyHealthBarRect;
    int moveCounter = 0;
    float enemyHealth;
    float enemySpeed;
    float enemyDeathX, enemyDeathY;
    int currentSpriteIndex;
    float previousFrame;
    bool isDead;
    Mix_Chunk* enemyDeathSound;
    bool isDeathOnce;
    
  
  public:
    Enemy(gamewindow* gw, const std::string& path);
    ~Enemy();
    void enemySpriteSplit();
    void setEnemyPosX(float enemyX);
    void setEnemySpriteIndex(int index);
    SDL_Rect getEnemyRect();
    void enemyRenderCopy(gamewindow* gw, Camera* c);
    void enemyRenderRect(gamewindow* gw);
    void enemyMove();
    bool isPlayerCollision(Player* p);
    void reduceEnemyHealth();
    float getEnemyHealth();
    void setDeathXandY(float deathX, float deathY);
    void loadEnemyDeathTexture(gamewindow* gw, const std::string& path);
    void renderEnemyDeath(gamewindow* gw, Camera* c);
    void enemyDead();
    bool getEnemyDeathStatus();
    void playEnemyDeathSound();
    void diedOnce();
    void setHealthBarPos(int x, int y, int w);
    bool isDiedOnce();

};

#endif