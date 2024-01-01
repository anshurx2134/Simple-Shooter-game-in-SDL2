#ifndef PLAYERINTER_H
#define PLAYERINTER_H


#include"../inc/SDL.h"
#include"../inc/SDL_image.h"
#include<iostream>
#include"../defs.h"
#include"player.h"
#include"enemy.h"
#include"../inc/SDL_mixer.h"



class landsmoke { 
  private:
    
    SDL_Rect landSSprite[6];
    SDL_Texture* landSmokeTexture;
    SDL_Surface* landSmokeSurface;
    float landsmokeposX, landsmokeposY;
    int CurrentSSpriteIndex;
    
  public:
    landsmoke();
    ~landsmoke();
    void loadInterTexture(const std::string& path, gamewindow* gw);
    SDL_Rect getLandSRect(Player* p);
    void spritesplit();
    void setCurrentSSpriteIndex(int index);
    // void setSSpriteX(Player* p);
    void landSmokeRenderCopy(Player* p, gamewindow* gw);
    void smokeFadeOut(bool &delayOver, int &alpha, float previousSpriteFrame);
};


// Class for Bullet, well... laser bullets, to be precise...
class Bullet:public Player {
  private:
    SDL_Texture* bulletTexture;
    SDL_Rect bulletRect;
    Mix_Chunk* gunShotSound;
  public:
    Bullet(gamewindow* gw, const std::string& path);
    ~Bullet();
    SDL_Rect getBulletRect();
    void bulletPosUpdate(Player* p);
    void bulletMove();
    void renderCopy(gamewindow* gw);
    void renderRect(gamewindow* gw);
    bool isCollision(Enemy* e);
  
};

class screenBlood {
  private:
    SDL_Rect screenBloodRect;
    SDL_Texture* screenBloodTexture;
    int screenBloodAlpha;
  public:
    screenBlood(gamewindow* gw, const std::string& path);
    ~screenBlood();
    void renderCopy(gamewindow* gw);

    void setScreenBloodAlpha(int alpha);
};

class gunLightning {
  private:
    std::vector<std::string> lightningFrames;
    SDL_Rect lightningRect;
    SDL_Texture* lightningTexture[4];
    int currentFrameIndex;
    float prevFrame;
  public:
    gunLightning(gamewindow* gw);
    ~gunLightning();
    void setLightningPos(Player* p);
    void updateAnim();
    void renderCopy(gamewindow* gw);
    

};
#endif