#include"base.h"
#include"defs.h"
#include<iostream>

using namespace std;

//INTERPOLATION METHOD (LERP)

float Lerp(float start, float end, float step) { 
  return start+(end-start)*step;
}

//GAME WINDOW METHODS 

gamewindow::gamewindow() { 
  if(SDL_Init(SDL_INIT_VIDEO)<0) { 
    SDL_Log("Unable to initialize... Quitting...", SDL_GetError());
    SDL_Quit();
  }
  

  SDL_Window* window;
  window = SDL_CreateWindow(WINDOWNAME,SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED, SCREENWIDTH, SCREENHEIGHT, SDL_WINDOW_SHOWN);
  if(!window) { 
    SDL_Log("Unable to create window...Quitting", SDL_GetError());
    SDL_Quit();
  }

  renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
  if(!renderer) { 
    SDL_Log("Unable to create renderer...Quitting", SDL_GetError());
    SDL_Quit();
  }
  
  surface = SDL_GetWindowSurface(window);
  if(!surface) { 
    SDL_Log("Unable to get surface... Quitting...", SDL_GetError());
  }

  if(Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT,2,2048)<0) {
    SDL_Log("The Audio could not be initialized", SDL_GetError());
  }

  if(TTF_Init()== -1) {
    SDL_Log("The menu font could not be initialized...", SDL_GetError());
  }
  
}

gamewindow::~gamewindow() { 
  SDL_FreeSurface(this->surface);
  SDL_DestroyRenderer(this->renderer);
  SDL_DestroyWindow(this->window);
  SDL_Quit();
}

SDL_Renderer* gamewindow::getRenderer() { 
  return this->renderer;
}

SDL_Surface* gamewindow::getSurface() { 
  return this->surface;
} 

void gamewindow::clear() { 
  SDL_SetRenderDrawColor(this->renderer, 0,0,0,255);
  SDL_RenderClear(this->renderer);
}
void gamewindow::render() { 
  
  SDL_RenderPresent(this->renderer);
}

//TIMER METHODS

float Timer::getDeltaTime(float &previousTime) {
    // cout<<"The previous frame:"<<previousTime<<endl;
    
    Uint32 currentTime = SDL_GetTicks();
    // cout<<"The current frame:"<<currentTime<<endl;
    float deltaTime = static_cast<float>(currentTime-previousTime) / 1000.0;
    previousTime =currentTime;
    return deltaTime;
}
