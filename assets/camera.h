#ifndef CAMERA_H
#define CAMERA_H

#include"player.h"
#include"../defs.h"
#include"../base.h"
#include<iostream>

class Camera { 
  private:
    SDL_Rect viewPort;
    int worldWidth, worldHeight;
  public:
    Camera(int screenwidth, int screenheight, int worldW, int worldH);
    void setViewPort(int x, int y, int w, int h);
    void update(Player* p);
    SDL_Rect getViewPort() const;
};

#endif