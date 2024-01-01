#include"enemy.h"

using namespace std;

Enemy::Enemy(gamewindow* gw, const std::string& path) {
  SDL_Surface* enemySurface = IMG_Load(path.c_str());

  if(!enemySurface) { 
    SDL_Log("The enemy surface could not be loaded...", SDL_GetError());
  }

  this->enemyTexture = SDL_CreateTextureFromSurface(gw->getRenderer(), enemySurface);
  SDL_FreeSurface(enemySurface);

  if(this->enemyTexture == nullptr) { 
    SDL_Log("The enemy texture couldnt be loaded...", SDL_GetError());
  }

  this->enemyRect.x = 1200.0f; //dont forget to bring this back to 1300
  this->enemyRect.y = 320.0f;
  this->enemyRect.w = ENEMYSPRITEWIDTH;
  this->enemyRect.h = ENEMYSPRITEHEIGHT;

  this->enemySpeed = ENEMYMOVESPEED;

  this->enemyHealth = ENEMYTOTALHEALTH;

  this->currentSpriteIndex = 0;

  this->moveCounter = 0;

  this->previousFrame = 0.0f;

  this->enemyDeathX = 0.0f;
  this->enemyDeathY = 0.0f;

  this->isDead = false;

  this->enemyDeathSound = Mix_LoadWAV(ENEMYDEATHSOUND);

  this->isDeathOnce = false;

  this->enemyHealthBarRect.x = this->enemyRect.x;
  this->enemyHealthBarRect.y = this->enemyRect.y - 25;
  this->enemyHealthBarRect.w = 0;
  this->enemyHealthBarRect.h = 5;
  
}
Enemy::~Enemy() { 
  SDL_DestroyTexture(this->enemyTexture);
  SDL_DestroyTexture(this->enemyDeathTexture);

  Mix_FreeChunk(this->enemyDeathSound);
  Mix_CloseAudio();
  
}

void Enemy::enemySpriteSplit() { 
  int index = 0;
  for(int row = 0; row<1; ++row){
    for(int col = 0; col<8; ++col) { 
      this->enemySpriteRect[index].w = ENEMYSPRITEWIDTH;
      this->enemySpriteRect[index].h = ENEMYSPRITEHEIGHT;
      this->enemySpriteRect[index].x = col*ENEMYSPRITEWIDTH;
      this->enemySpriteRect[index].y = row*ENEMYSPRITEHEIGHT;
      // cout<<"Index:"<<index<<endl;
      // cout<<"Column:"<<col<<endl;
      // cout<<"The width and the height of the enemy sprite split:"<<this->enemySpriteRect[index].w<<"\t"<<this->enemySpriteRect[index].h<<endl;
      // cout<<"The x and y coordinates of the enemy sprite split:"<<this->enemySpriteRect[index].x<<"\t"<<this->enemySpriteRect[index].y<<endl;
      ++index;
  } 
  }
  
}

void Enemy::setEnemyPosX(float enemyX) { 
  this->enemyRect.x = enemyX;
}

SDL_Rect Enemy::getEnemyRect() { 
  return this->enemyRect;
}


void Enemy::setEnemySpriteIndex(int index ) { 
  this->currentSpriteIndex = index;
}

void Enemy::setHealthBarPos(int x, int y, int w) {
  this->enemyHealthBarRect.x = x + 115;
  this->enemyHealthBarRect.y = y -10 ;
  this->enemyHealthBarRect.w = w / 6;
}

//Render copy function for the enemy character...
void Enemy::enemyRenderCopy(gamewindow* gw, Camera* c ) { 
  // int w, h;
  // SDL_QueryTexture(this->enemyTexture, NULL, NULL, &w,&h);

  // this->enemyRect.y -= c->getViewPort().y; For the camera viewport, but it has some issues...
  float currentFrame = SDL_GetTicks();
  // cout<<"previousFrame:"<<previousFrame<<endl;
  if(currentFrame - this->previousFrame >= ENEMYANIMATIONSPEED) { 
    this->currentSpriteIndex = (this->currentSpriteIndex+1)%8;
    // cout<<"The value of the difference between the current and the previous frames:"<<currentFrame - previousFrame<<endl;
    this->previousFrame = currentFrame;
    
  }  

  
  SDL_Rect modEnemyRect; // I have no idea why creating a new rectangle similar to the enemyRect
                          // and feeding it to the rendercopy instead of enemyRect works...
                          // I mean, they are essentially the same Rectangle, man...C++ is wierd...
  
  float viewportY = c->getViewPort().y-140;
  modEnemyRect = {this->enemyRect.x, this->enemyRect.y, this->enemyRect.w, this->enemyRect.h};

  modEnemyRect.y = modEnemyRect.y - viewportY;

  
  // cout<<"The y position of the camera viewport... "<< c->getViewPort().y<<endl;
  // cout<<"The y position of the enemy rectangle... "<< modEnemyRect.y <<endl;
  this->setHealthBarPos(this->enemyRect.x, this->enemyRect.y, this->enemyHealth);
  this->enemyHealthBarRect.y = this->enemyHealthBarRect.y - viewportY;
  SDL_SetRenderDrawColor(gw->getRenderer(), 255, 0,0,255);
  SDL_RenderFillRect(gw->getRenderer(), &this->enemyHealthBarRect);
  
  
  SDL_RenderCopy(gw->getRenderer(), this->enemyTexture, &this->enemySpriteRect[this->currentSpriteIndex] , &modEnemyRect);
  //&this->enemySpriteRect[this->currentSpriteIndex] Just to see if the rendering works without the damn srcrect and guess what, it works fine...
  
  // cout<<w<<'\t'<<h<<endl;
  // cout<<"The x and y value of the sprite image in the sprite sheet:"<<this->enemySpriteRect[this->currentSpriteIndex].x<<"\t"<<this->enemySpriteRect[this->currentSpriteIndex].y<<endl;
  // cout<<"The w and h value of the sprite image in the sprite sheet:"<<this->enemySpriteRect[this->currentSpriteIndex].w<<"\t"<<this->enemySpriteRect[this->currentSpriteIndex].h<<endl;
  // cout<<"The x and y value of the rectangle that the texture defines:"<<this->enemyRect.x<<'\t'<<this->enemyRect.y<<endl;
  // cout<<"The w and h value of the rectangle that the texture defines:"<<this->enemyRect.w<<'\t'<<this->enemyRect.h<<endl;
  // cout<<this->currentSpriteIndex<<endl;
}

void Enemy::enemyRenderRect(gamewindow* gw) { 
  SDL_SetRenderDrawColor(gw->getRenderer(),255,0,0,255);
  SDL_RenderFillRect(gw->getRenderer(), &this->enemyRect);
}

void Enemy::enemyMove() {

   
  if(moveCounter%10 ==0){
   
    int enemyX = this->enemyRect.x;
    enemyX-=this->enemySpeed; 
    // cout<<"The x position of the enemy:"<< enemyX<<endl;
    this->setEnemyPosX(enemyX);
   }
   moveCounter++; 
  //  cout<<moveCounter%100000<<endl;
}

bool Enemy::isPlayerCollision(Player* p) { 
  bool overlapX = ((p->getRect().x+p->getRect().w >= this->enemyRect.x)&& (this->enemyRect.x + this->enemyRect.w >= p->getRect().x));
  bool overlapY = ((p->getRect().y+p->getRect().h >= this->enemyRect.y)&& (this->enemyRect.y + this->enemyRect.h >= p->getRect().y));
  return (overlapX && overlapY);
}

void Enemy::reduceEnemyHealth() {
  this->enemyHealth -= ENEMYHEALTHDECREASE;
}

float Enemy::getEnemyHealth() {
  return this->enemyHealth;
}

void Enemy::setDeathXandY(float X, float Y) {
  this->enemyDeathX = X;
  this->enemyDeathY = Y;
} 

void Enemy::loadEnemyDeathTexture(gamewindow* gw, const std::string& path) {
  SDL_Surface* enemyDeathSurface = IMG_Load(path.c_str());
  if(!enemyDeathSurface) {
    SDL_Log("The enemy death texture could not be loaded...", SDL_GetError());
  }
  this->enemyDeathTexture = SDL_CreateTextureFromSurface(gw->getRenderer(), enemyDeathSurface);
  SDL_FreeSurface(enemyDeathSurface);
  if(!this->enemyDeathTexture) {
    SDL_Log("The enemy death texture could not be loaded...", SDL_GetError());
  }

  
  this->enemyDeathRect.w = ENEMYDEATHWIDTH;
  this->enemyDeathRect.h = ENEMYDEATHHEIGHT;
}

void Enemy::renderEnemyDeath(gamewindow* gw, Camera* c) {
  this->enemyDeathRect.x = this->enemyDeathX;
  this->enemyDeathRect.y = this->enemyDeathY;

  float viewPortY = c->getViewPort().y-140;
  this->enemyDeathRect.y -= viewPortY;
  SDL_RenderCopy(gw->getRenderer(), this->enemyDeathTexture, NULL, &this->enemyDeathRect);
}

void Enemy::enemyDead() {
  this->isDead = true;
  
}

bool Enemy::getEnemyDeathStatus() {
  return isDead;
}

void Enemy::playEnemyDeathSound() {
  if(!isDeathOnce){
    Mix_PlayChannel(5,this->enemyDeathSound, 0);
  }
}

void Enemy::diedOnce() {
  this->isDeathOnce = true;
}

bool Enemy::isDiedOnce(){ 
  return this->isDeathOnce;
}