#ifndef BASE_H
#define BASE_H

#include"inc/SDL.h"
#include"inc/SDL_image.h"
#include"inc/SDL_mixer.h"
#include"inc/SDL_ttf.h"

float Lerp(float start, float end, float step);


class gamewindow { 
  
  private:
    SDL_Window* window;
    SDL_Renderer* renderer;
    SDL_Surface* surface;
    SDL_Texture* texture;
    
  public:
    gamewindow();
    ~gamewindow();
    SDL_Renderer* getRenderer();
    SDL_Surface* getSurface();
    void clear();
    void render();  
};

class Timer { 
  public:
    float getDeltaTime(float &previousTime);
};
#endif