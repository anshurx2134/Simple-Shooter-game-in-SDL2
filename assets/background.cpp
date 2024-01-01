#include"background.h"
using namespace std;

background::~background() { 
  SDL_DestroyTexture(this->bgtexture);
}

void background::loadbgTexture(const std::string& path, gamewindow* gw) { 
  this->bgsurface = IMG_Load(path.c_str());
  
  if(!this->bgsurface) { 
    SDL_Log("The background surface could not be loaded...", SDL_GetError());
  }

  this->bgtexture = SDL_CreateTextureFromSurface(gw->getRenderer(), this->bgsurface);
  SDL_FreeSurface(this->bgsurface);
  if(!this->bgtexture) { 
    SDL_Log("The background texture could not be loaded...", SDL_GetError());
  }
}

SDL_Texture* background:: getBgTexture() { 
  return this->bgtexture;
}

void background::pltrendercopy(float envx, float envy, gamewindow* gw, Camera* c) { 
  SDL_QueryTexture(this->bgtexture, NULL, NULL, &this->bgRect.w, &this->bgRect.h);
  // cout<<this->bgRect.w<<'\t'<<this->bgRect.h<<endl;
  this->bgRect.x = envx;
  this->bgRect.y = envy- Lerp(0.0f,c->getViewPort().y,0.75) + 110;
  // this->bgRect.y = envy- c->getViewPort().y + 150;

  SDL_RenderCopy(gw->getRenderer(), this->bgtexture, NULL, &this->bgRect);
}

void background::envrendercopy(float envx, float envy, gamewindow* gw, Camera* c) { 
  
  
  this->bgRect.w = WORLDWIDTH;
  this->bgRect.h = WORLDHEIGHT;
  this->bgRect.x = envx;
  this->bgRect.y = envy - Lerp(0.0f,c->getViewPort().y,0.75);
  // this->bgRect.y = envy- c->getViewPort().y;
  // cout<<this->bgRect.w<<'\t'<<this->bgRect.h<<endl;
  SDL_RenderCopy(gw->getRenderer(), this->bgtexture, NULL, &this->bgRect);
}

