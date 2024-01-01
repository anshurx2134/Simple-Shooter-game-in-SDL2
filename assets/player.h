#ifndef PLAYER_H
#define PLAYER_H

#include"../inc/SDL.h"
#include"../base.h"
#include"../defs.h"


#include<string>
#include<vector>
#include<iostream>

class Player { 
  private:
    SDL_Rect playerRct;
    SDL_Rect menuPlayerRect;
    SDL_Rect playerHealthRect;
    SDL_Rect playerHealthOutlineRect;
    SDL_Rect* spriteRect;
    SDL_Surface* playerSurface;
    SDL_Texture* playerSpriteTexture;
    SDL_Texture* playerDeathTexture;

  
    int x, y;
    float targetX, targetY, moveSpeed;
    int currentSpriteIndex;
    int playerHealth;
    
  public:
    //Constructor and Destructor
    Player();
    ~Player();

    //Getter
    int getCoors(int &playerx, int &playery);

    SDL_Rect getRect();

    //Setter
    void setCoors(int new_x, int new_y);

  

    //Render
    void render(gamewindow* gw);

    void playerSpriteSplit();

    SDL_Rect* getPlayerSpriteRect();

    void loadPlayerSpriteTexture(const std::string& path, gamewindow* gw);

    void setSpriteIndex(int index);

    SDL_Rect getCurrentSprite();

    SDL_Texture* getSpriteTexture();

    void reduceHealth();

    int getPlayerHealth();

    void setPlayerHealth(int health);

    void rendercopy(gamewindow* gw);

    void renderMenuPlayer(gamewindow* gw, SDL_RendererFlip& fliptype);
    
    void renderPlayerCorpse(gamewindow* gw);

    void setWidthHealthBar(int health);

   
};


#endif