#include"playerInter.h"

using namespace std;

landsmoke::landsmoke(){ 
  this->landsmokeposX = 0.0f;
  this->landsmokeposY = 125.0f;
  this->CurrentSSpriteIndex = 0;

  
}

landsmoke::~landsmoke() { 
  SDL_DestroyTexture(this->landSmokeTexture);
}


void landsmoke::loadInterTexture(const std::string& path, gamewindow* gw) {
  this->landSmokeSurface = IMG_Load(path.c_str());

  if(!this->landSmokeSurface) { 
    SDL_Log("The land smoke surface could not be loaded...", SDL_GetError());
  }

  this->landSmokeTexture = SDL_CreateTextureFromSurface(gw->getRenderer(), this->landSmokeSurface);
  SDL_FreeSurface(this->landSmokeSurface);
  if(!this->landSmokeTexture) { 
    SDL_Log("The land smoke texture could not be loaded...", SDL_GetError());
  }
}

void landsmoke::spritesplit() { 
  int index = 0;
  for(int row = 0; row<3; ++row) { 
    for(int column = 0; column<2; ++column) { 
      this->landSSprite[index].w = LANDSMOKE_SPRITEWIDTH;
      this->landSSprite[index].h = LANDSMOKE_SPRITEHEIGHT;
      this->landSSprite[index].x = row*LANDSMOKE_SPRITEWIDTH;
      this->landSSprite[index].y = column*LANDSMOKE_SPRITEHEIGHT;
      // cout<<"row "<<row<<"column "<<column<<endl;
      // cout<<"index "<< index<<endl;
      // cout<<"landSSprite[index].x "<<landSSprite[index].x<<"\t"<<"landSSprite[index].y "<< landSSprite[index].y<< endl;
      // cout<<"landSSprite[index].w "<<landSSprite[index].w<<"\t"<<"landSSprite[index].h "<< landSSprite[index].h<<'\n'<< endl;
      ++index;
      
      
      
    }
  }
}


void landsmoke::setCurrentSSpriteIndex(int index) { 
  this->CurrentSSpriteIndex = index;
}


void landsmoke::landSmokeRenderCopy(Player* p, gamewindow* gw) {
  SDL_Rect playerRect = p->getRect();

  int smokePosX = playerRect.x -15;
  int smokePosY = playerRect.y+ 100;
  int smokeWidth = PLAYERRECTWIDTH - 20;
  int smokeHeight = PLAYERRECTHEIGHT - 70;

  SDL_Rect smokeRenderPos = {smokePosX, smokePosY, smokeWidth, smokeHeight};
  
  // cout<<"landSSprite"<<this->landSSprite[1].x<<endl;
  SDL_RenderCopy(gw->getRenderer(), this->landSmokeTexture, &this->landSSprite[this->CurrentSSpriteIndex], &smokeRenderPos);

}

void landsmoke::smokeFadeOut(bool &delayOver, int &alpha, float previousSpriteFrame) { 
  float currentTime = SDL_GetTicks();
  
  int SMOKEDELAY = 500;
  int ALPHAREDUCTIONRATE = 1;
  if(currentTime - previousSpriteFrame> SMOKEDELAY) { 
      
      previousSpriteFrame = currentTime;
  }
  // cout<<"currentTime - previousSpriteFrame"<< currentTime - previousSpriteFrame<<endl;
  SDL_SetTextureAlphaMod(this->landSmokeTexture, alpha);
  alpha -= ALPHAREDUCTIONRATE;
  // cout<<"alpha"<<alpha<<endl;

  if(alpha < 0) { 
    alpha = 255;
  }
}


Bullet::Bullet(gamewindow* gw, const std::string& path) { 
  SDL_Surface* bulletSurface = IMG_Load(path.c_str());

  if(!bulletSurface) { 
    SDL_Log("The bullet surface could not be loaded...", SDL_GetError());
  }

  this->bulletTexture = SDL_CreateTextureFromSurface(gw->getRenderer(), bulletSurface);
  SDL_FreeSurface(bulletSurface);

  if(!this->bulletTexture) { 
    SDL_Log("The bullet texture could not be loaded...", SDL_GetError());
  }

  this->gunShotSound =  Mix_LoadWAV(GUNSHOTWAV);
  if(!this->gunShotSound) {
    SDL_Log("The gun shot audio could not be loaded...", SDL_GetError());
  }

  this->bulletRect.y = 500.0f;
  this->bulletRect.x = 500.0f;
  this->bulletRect.w = BULLETWIDTH;
  this->bulletRect.h = BULLETHEIGHT;             
}
Bullet::~Bullet() { 
  SDL_DestroyTexture(this->bulletTexture);
  Mix_FreeChunk(this->gunShotSound);
  Mix_CloseAudio();
}

SDL_Rect Bullet::getBulletRect() { 
  return this->bulletRect;
}

// void Bullet::bulletMove() { 

// }

void Bullet::bulletPosUpdate(Player* p) {
  this->bulletRect.x = p->getRect().x; 
  this->bulletRect.y = p->getRect().y + 60;
}

void Bullet::bulletMove() { 
  this->bulletRect.x += BULLETSPEED;
}

void Bullet:: renderCopy(gamewindow* gw) { 
  Mix_PlayChannel(1, this->gunShotSound, 0);
  SDL_RenderCopy(gw->getRenderer(), this->bulletTexture, NULL, &this->bulletRect);
}

void Bullet::renderRect(gamewindow* gw) { 
  SDL_SetRenderDrawColor(gw->getRenderer(), 255,0,0,255);
  SDL_RenderFillRect(gw->getRenderer(), &this->bulletRect);
}

bool Bullet::isCollision(Enemy* e) { 
  bool bulletOverlapX = ((this->bulletRect.x + this->bulletRect.w >= e->getEnemyRect().x) && (this->bulletRect.x<= e->getEnemyRect().x));
  return bulletOverlapX;
}

// Screen Blood while getting hurt...
screenBlood::screenBlood(gamewindow* gw, const std::string& path) {
  SDL_Surface* screenBloodSurface = IMG_Load(path.c_str());
  if(!screenBloodSurface) {
    SDL_Log("The screen blood surface could not be loaded...", SDL_GetError());
  }
  this->screenBloodTexture = SDL_CreateTextureFromSurface(gw->getRenderer(),screenBloodSurface);
  SDL_FreeSurface(screenBloodSurface);
  if(!this->screenBloodTexture) { 
    SDL_Log("The screen blood texture could not be loaded...", SDL_GetError());
  }

  this->screenBloodRect.x = 0;
  this->screenBloodRect.y = 0;
  this->screenBloodRect.w = SCREENWIDTH;
  this->screenBloodRect.h = SCREENHEIGHT;

  this->screenBloodAlpha = 255;
}

screenBlood::~screenBlood() { 
  SDL_DestroyTexture(this->screenBloodTexture);
}

void screenBlood::renderCopy(gamewindow* gw) {
 
  SDL_RenderCopy(gw->getRenderer(), this->screenBloodTexture, NULL, &this->screenBloodRect);
}




void screenBlood::setScreenBloodAlpha(int alpha) {
  this->screenBloodAlpha = alpha;
}


// Gun Lightning animation
gunLightning::gunLightning(gamewindow* gw) { 
  lightningFrames = {
    GUNLIGHTNINGPATH1,
    GUNLIGHTNINGPATH3,
    GUNLIGHTNINGPATH2,
    GUNLIGHTNINGPATH4,
  };

  SDL_Surface* lightningSurface[4];
  int index = 0;
  for(SDL_Surface* surface: lightningSurface) {
    surface = IMG_Load(lightningFrames[index].c_str());
    if(!surface) {
      SDL_Log("The lightning surface could not be loaded...", SDL_GetError());
    }

    this->lightningTexture[index] = SDL_CreateTextureFromSurface(gw->getRenderer(), surface);
    SDL_FreeSurface(surface);

    if(!this->lightningTexture[index]) {
      SDL_Log("The lightning texture could not be loaded ...", SDL_GetError());
    }
    index++;
  }

  this->lightningRect.w = LIGHTNINGWIDTH;
  this->lightningRect.h = LIGHTNINGHEIGHT;

  this->currentFrameIndex = 0;

  this->prevFrame = 0.0f;
}

gunLightning::~gunLightning() {
  for(SDL_Texture* texture: this->lightningTexture){
    SDL_DestroyTexture(texture);
    }
}

void gunLightning::setLightningPos(Player* p) {
  this->lightningRect.x = p->getRect().x+34;
  this->lightningRect.y = p->getRect().y+67;
  
}

void gunLightning::updateAnim() {
  float currentFrame = SDL_GetTicks();
  // cout<<"The difference between the previous and current gun Lighting timers..."<<currentFrame-prevFrame<<endl;
  if(currentFrame - this->prevFrame >= LIGHTNINGANIMATIONSPEED) {
    // cout<<"the current frame Index:"<< this->currentFrameIndex<<endl;
    this->currentFrameIndex++;    
    if(this->currentFrameIndex >= this->lightningFrames.size()){
      this->currentFrameIndex = 0;
    }

    this->prevFrame = currentFrame;
  }
}

void gunLightning::renderCopy(gamewindow*gw) {
  SDL_RenderCopy(gw->getRenderer(), this->lightningTexture[this->currentFrameIndex], NULL, &this->lightningRect);
  // cout<<"The value of the current sprite index inside the render copy function:"<< this->currentFrameIndex<<endl;
}