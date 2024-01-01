#ifndef BACKGROUND_H
#define BACKGROUND_H

#include"../inc/SDL.h"
#include"../inc/SDL_image.h"
#include<string>
#include"../base.h"
#include<iostream>
#include"camera.h"

class background { 
  private:
    SDL_Surface* bgsurface;
    SDL_Texture* bgtexture;
    SDL_Rect bgRect;
  public:
    ~background();
    void loadbgTexture(const std::string& path, gamewindow* gw);
    SDL_Texture* getBgTexture();
    void pltrendercopy(float envx, float envy, gamewindow* gw, Camera* c);
    void envrendercopy(float envx, float envy, gamewindow* gw, Camera* c);
    
};

#endif