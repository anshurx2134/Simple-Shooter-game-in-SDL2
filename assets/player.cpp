#include"player.h"


Player::Player(){
  this->x = 0;
  this->y = 0;

  this->playerRct.w = PLAYERRECTWIDTH;
  this->playerRct.h = PLAYERRECTHEIGHT;
  this->playerRct.x = this->x;
  this->playerRct.y = this->y;

  this->menuPlayerRect.x = 600;
  this->menuPlayerRect.y = 150;
  this->menuPlayerRect.w = (PLAYERRECTWIDTH*3);
  this->menuPlayerRect.h = (PLAYERRECTHEIGHT*3);

  this->playerHealth = PLAYERTOTALHEALTH;

  this->spriteRect = new SDL_Rect[SPRITEROWS*SPRITECOLUMNS];
  this->currentSpriteIndex = 0;

  this->playerHealthRect.x = 90;
  this->playerHealthRect.y = 60;
  this->playerHealthRect.w = 0;
  this->playerHealthRect.h = 15;

  this->playerHealthOutlineRect.x = 85;
  this->playerHealthOutlineRect.y = 55;
  this->playerHealthOutlineRect.w = 10 + (this->playerHealth)/15 ;
  this->playerHealthOutlineRect.h = 25;


}

Player::~Player() { 
  delete[] this->spriteRect;
  SDL_DestroyTexture(this->playerSpriteTexture);
  
} 

void Player::setCoors(int new_x, int new_y) { 
  this->playerRct.x = new_x;
  this->playerRct.y = new_y;

}

void Player::render(gamewindow* gw) { 
  SDL_SetRenderDrawColor(gw->getRenderer(), 255,0,0,255);
  SDL_RenderFillRect(gw->getRenderer(), &playerRct);
}



int Player::getCoors(int &playerx, int &playery) { 
  playerx = this->playerRct.x;
  playery = this->playerRct.y;

  return playerx, playery; 
}

SDL_Rect Player::getRect() { 

  return playerRct;
} 

void Player::playerSpriteSplit() { 
  
  int index = 0;
  for(int row = 0; row<SPRITEROWS; ++row) { 
    for(int col = 0; col<SPRITECOLUMNS; ++col) { 
      this->spriteRect[index].x = col*SPRITEWIDTH;
      this->spriteRect[index].y = row*SPRITEHEIGHT;
      this->spriteRect[index].w = SPRITEWIDTH;
      this->spriteRect[index].h = SPRITEHEIGHT;
      
      ++index;

      
      
    }
  }

}

// Returns the array with the splitted sprites
SDL_Rect* Player:: getPlayerSpriteRect() { 
  return this->spriteRect;
}

void Player::loadPlayerSpriteTexture(const std::string& path, gamewindow* gw) { 
  
  this->playerSurface = IMG_Load(path.c_str());
  if(!playerSurface) { 
    SDL_Log("The player surface could not be loaded....", SDL_GetError());
  }

  this->playerSpriteTexture = SDL_CreateTextureFromSurface(gw->getRenderer(), this->playerSurface);
  SDL_FreeSurface(playerSurface);
  if(!playerSpriteTexture) { 
    SDL_Log("The player texture could not be loaded...", SDL_GetError());
  }

  SDL_Surface* playerDeathSurface = IMG_Load(PLAYERCORPSEPATH);
  if(!playerDeathSurface) {
    SDL_Log("The player death surface could not be loaded...", SDL_GetError());
  }

  this->playerDeathTexture = SDL_CreateTextureFromSurface(gw->getRenderer(), playerDeathSurface);
  SDL_FreeSurface(playerDeathSurface);
  if(!this->playerDeathTexture) {
    SDL_Log("The player death texture could not be loaded...", SDL_GetError());
  }


}

SDL_Texture* Player::getSpriteTexture() { 
  return this->playerSpriteTexture;
}

void Player::setSpriteIndex(int index){
  
  this->currentSpriteIndex = index;
}

SDL_Rect Player::getCurrentSprite() {
  
  return this->getPlayerSpriteRect()[this->currentSpriteIndex];
  
}

void Player::reduceHealth() { 
  this->playerHealth -= PLAYERHEALTHDECREASE;
}

int Player::getPlayerHealth() { 
  return this->playerHealth;
}

void Player::rendercopy(gamewindow* gw) { 
  this->setWidthHealthBar((this->playerHealth)/15);
  SDL_SetRenderDrawColor(gw->getRenderer(), 0,0,0,155);
  SDL_RenderFillRect(gw->getRenderer(), &this->playerHealthOutlineRect);

  SDL_SetRenderDrawColor(gw->getRenderer(), 255,30,29,255);
  SDL_RenderFillRect(gw->getRenderer(), &this->playerHealthRect);

  SDL_Rect spriteToRender = this->spriteRect[currentSpriteIndex];
  
  SDL_RenderCopy(gw->getRenderer(), this->playerSpriteTexture, &spriteToRender, &this->playerRct);
}

void Player::setWidthHealthBar(int health) {
  this->playerHealthRect.w = health;
}

void Player::renderMenuPlayer(gamewindow* gw, SDL_RendererFlip& fliptype) {
  
  SDL_Rect spriteToRender = this->spriteRect[5];
  SDL_RenderCopyEx(gw->getRenderer(), this->playerSpriteTexture, &spriteToRender, &this->menuPlayerRect, 0.0f, NULL, fliptype);
}

void Player:: renderPlayerCorpse(gamewindow* gw) {
  SDL_Rect playerCorpseRect = {this->menuPlayerRect.x, this->menuPlayerRect.y-40, this->menuPlayerRect.w, this->menuPlayerRect.h-10};
  SDL_RenderCopy(gw->getRenderer(), this->playerDeathTexture, NULL, &playerCorpseRect);
}


void Player::setPlayerHealth(int health) {
  this->playerHealth = health;
}


