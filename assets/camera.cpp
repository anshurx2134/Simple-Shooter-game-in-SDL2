#include"camera.h"

using namespace std;

Camera::Camera(int screenwidth, int screenheight, int worldW, int worldH) {
  viewPort.x = 0;
  viewPort.y = screenheight/2;
  viewPort.w = screenwidth;
  viewPort.h = screenheight;
  worldWidth = worldW;
  worldHeight = worldH;
}

void Camera::setViewPort(int x, int y, int w, int h) { 
  this->viewPort.x = x;
  this->viewPort.y = y;
  this->viewPort.w = w;
  this->viewPort.h = h;
}

void Camera::update(Player* p) { 
  // viewPort.x = p->getRect().x - (viewPort.w)/2;
  viewPort.y = p->getRect().y - (viewPort.h)/2;

  
  int i = 0;
  // if(i%121 == 0){
  //   cout<<"PlayerY:"<< p->getRect().y<<endl;
  //   cout<<"Half of the Height of viewport:"<< (viewPort.h)/2<< endl;
  //   cout<<"viewPort.y:"<<viewPort.y<<endl;
  //   i++;
  // }

  // if(viewPort.x<0) { 
  //   viewPort.x = 0;
  // }

  // if(viewPort.x + viewPort.w > worldWidth) { 
  //   viewPort.x = worldWidth - viewPort.w;
  // }

  if(viewPort.y<0) { 
    viewPort.y = 0;
  }
  if(viewPort.y+viewPort.h> worldHeight) { 
    viewPort.y = worldHeight - viewPort.h;
  }
  
}

SDL_Rect Camera::getViewPort() const{
  return viewPort;
}