#ifndef MENU_H
#define MENU_H

#include "../base.h"
#include<iostream>
#include"../defs.h"

class Menu {
  private:
    TTF_Font* textFont;
    SDL_Texture* gameTriggerTexture;
    SDL_Rect gameTriggerRect;
    SDL_Texture* exitTexture;
    SDL_Rect exitRect;
    SDL_Texture* creditTexture;
    SDL_Rect creditRect;
    SDL_Texture* tryAgainTexture;
    SDL_Rect tryAgainRect;
    SDL_Texture* scoreTexture;
    SDL_Texture* highScoreTexture;


  public:
    Menu(gamewindow* gw);
    ~Menu();

    void renderCopy(gamewindow* gw);
    void renderTryAgain(gamewindow* gw);
    bool isPlayGame(float mouseX, float mouseY);
    bool isPlayClicked(SDL_Event& menuEvent);
    bool isExitClicked(SDL_Event& menuEvent);
   
};


#endif 