#include"menu.h"

using namespace std;

Menu::Menu(gamewindow* gw) {
  this->textFont = TTF_OpenFont(PLAYGAMEFONTPATH, PLAYGAMEFONTSIZE);
  if(!this->textFont) {
    SDL_Log("The menu font could not be loaded", SDL_GetError());
  }

  SDL_Surface* playGameSurface = TTF_RenderText_Solid(this->textFont, "PLAY NOW", {255,255,255});
  if(!playGameSurface) {
    SDL_Log("The menu could not be loaded", SDL_GetError());
  }

  this->gameTriggerTexture = SDL_CreateTextureFromSurface(gw->getRenderer(), playGameSurface);
  SDL_FreeSurface(playGameSurface);
  if(!this->gameTriggerTexture) {
    SDL_Log("The menu screen text texture could not be loaded...", SDL_GetError());
  }

  this->gameTriggerRect.x = 150;
  this->gameTriggerRect.y = 200;
  this->gameTriggerRect.w = PLAYGAMEWIDTH;
  this->gameTriggerRect.h = PLAYGAMEHEIGHT;

  SDL_Surface* exitSurface = TTF_RenderText_Solid(this->textFont, "EXIT GAME", {255,255,255});
  if(!exitSurface) {
    SDL_Log("The exit game surface could not be loaded...", SDL_GetError());
  }

  this->exitTexture = SDL_CreateTextureFromSurface(gw->getRenderer(), exitSurface);
  SDL_FreeSurface(exitSurface);
  if(!this->exitTexture) {
    SDL_Log("The exit texture could not be loaded...", SDL_GetError());
  }
  this->exitRect.x = 150;
  this->exitRect.y = 400;
  this->exitRect.w = EXITGAMEWIDTH;
  this->exitRect.h = EXITGAMHEIGHT;

  SDL_Surface* creditSurface = TTF_RenderText_Solid(this->textFont, "By Anshu Jyothikumar", {255,255,255});
  if(!creditSurface) {
    SDL_Log("The credits surface could not be loaded...", SDL_GetError());
  }

  this->creditTexture = SDL_CreateTextureFromSurface(gw->getRenderer(), creditSurface);
  SDL_FreeSurface(creditSurface);
  if(!this->creditTexture) {
    SDL_Log("The credit texture could not be loaded...", SDL_GetError());
  }

  this->creditRect.x = 750;
  this->creditRect.y = 600;
  this->creditRect.w = CREDITWIDTH;
  this->creditRect.h = CREDITHEIGHT;
  
  SDL_Surface* tryAgainSurface = TTF_RenderText_Solid(this->textFont, "TRY AGAIN", {255,255,255});
  if(!tryAgainSurface) {
    SDL_Log("The try again surface could not be loaded...", SDL_GetError());
  }
  this->tryAgainTexture = SDL_CreateTextureFromSurface(gw->getRenderer(), tryAgainSurface);
  SDL_FreeSurface(tryAgainSurface);
  if(!this->tryAgainTexture) {
    SDL_Log("The try again texture could not be loaded...", SDL_GetError());
  }

  this->tryAgainRect.x = 150;
  this->tryAgainRect.y = 200;
  this->tryAgainRect.w = PLAYGAMEWIDTH;
  this->tryAgainRect.h = PLAYGAMEHEIGHT;


  
}

Menu::~Menu() {
  SDL_DestroyTexture(this->gameTriggerTexture);
  SDL_DestroyTexture(this->exitTexture);
  SDL_DestroyTexture(this->creditTexture);
  SDL_DestroyTexture(this->scoreTexture);
  SDL_DestroyTexture(this->highScoreTexture);
}

void Menu::renderCopy(gamewindow* gw) {
  // cout<<"The x and y coordinates of the Play Game rectangle..."<<this->gameTriggerRect.x<<" "<< this->gameTriggerRect.y<<endl;
  // cout<<"The width and height of the Play Game rectangle..."<<this->gameTriggerRect.w<<" "<< this->gameTriggerRect.h<<endl;
  SDL_RenderCopy(gw->getRenderer(), this->gameTriggerTexture, NULL, &this->gameTriggerRect);
  SDL_RenderCopy(gw->getRenderer(), this->exitTexture, NULL, &this->exitRect);
  SDL_RenderCopy(gw->getRenderer(), this->creditTexture, NULL, &this->creditRect);
}

void Menu::renderTryAgain(gamewindow* gw) {
  SDL_RenderCopy(gw->getRenderer(), this->tryAgainTexture, NULL, &this->tryAgainRect);
  SDL_RenderCopy(gw->getRenderer(), this->exitTexture, NULL, &this->exitRect);
  
}

bool Menu::isPlayGame(float mX, float mY) {
  return (mX>= this->gameTriggerRect.x && mY< (this->gameTriggerRect.x +this->gameTriggerRect.w) 
          && mY>= this->gameTriggerRect.y && mY< (this->gameTriggerRect.y + this->gameTriggerRect.h));
}

bool Menu::isPlayClicked(SDL_Event& menuEvent) {
  if(menuEvent.type == SDL_MOUSEBUTTONDOWN && menuEvent.button.button == SDL_BUTTON_LEFT) {
    int mouseX, mouseY;
    SDL_GetMouseState(&mouseX, &mouseY);
    return (mouseX>= this->gameTriggerRect.x && mouseY< (this->gameTriggerRect.x +this->gameTriggerRect.w) 
          && mouseY>= this->gameTriggerRect.y && mouseY< (this->gameTriggerRect.y + this->gameTriggerRect.h));
  }
  return false;
}

bool Menu::isExitClicked(SDL_Event& menuEvent) {
  if(menuEvent.type == SDL_MOUSEBUTTONDOWN && menuEvent.button.button == SDL_BUTTON_LEFT) {
    int mX, mY;
    SDL_GetMouseState(&mX, &mY);
    return(mX>= this->exitRect.x && mX< (this->exitRect.x + this->exitRect.w)
          && mY>= this->exitRect.y && mY< (this->exitRect.y + this->exitRect.h));
  }
  return false;
}

