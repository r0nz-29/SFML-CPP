#include <SFML/Graphics/CircleShape.hpp>
#include <cstdio>
#include<iostream>
#include<SFML/Graphics.hpp>
#include<cmath>
#define MAX_BUL 100
#define RAD 4

using namespace sf;

class Ball : public CircleShape {
public:
  float dx, dy;
  void checkBoundary(float rad) {
    if((this->getPosition().y + rad*2) >= 600){
      this->dy = -this->dy;
    }
    if((this->getPosition().y) <= 0){
      this->dy = -this->dy;
    }
    if((this->getPosition().x + rad*2) >= 800){
      this->dx = -this->dx;
    }
    if((this->getPosition().x) <= 0){
      this->dx = -this->dx;
    }
  }
};

int main() {
  RenderWindow window(VideoMode(800, 600), "myWindow");

  Color colors[4] = {
    Color(221, 124, 183, 255),
    Color(107, 94, 188, 255),
    Color(156, 35, 80, 255),
    Color(223, 133, 223, 255)
  };

  Ball bullets[MAX_BUL];
  srand(time(NULL));
  for(int i=0; i<MAX_BUL; i++){
    Ball bullet;
    bullet.setRadius(RAD);
    float x = rand()%(800-RAD-50)+50;
    float y = rand()%(600-RAD-50)+50;
    bullet.setPosition(x, y);
    bullet.setFillColor(colors[rand()%4]);
    bullet.dx = 0, bullet.dy = 0;
    bullets[i] = bullet;
  }
  float angle=0;

  while(window.isOpen()){
    Event e;
    window.pollEvent(e);

    for(int i=0; i<MAX_BUL; i++){
      float bullet_x = bullets[i].getPosition().x + RAD;
      float bullet_y = bullets[i].getPosition().y + RAD;
      float mouse_x = Mouse::getPosition(window).x;
      float mouse_y = Mouse::getPosition(window).y;
      float ratio = (float)(mouse_y - bullet_y)/(mouse_x - bullet_x);
      angle = atan(ratio)*(180/M_PI);
      bullets[i].dx = cos(angle)*2;
      bullets[i].dy = sin(angle)*2;
    }

    for(int i=0; i<MAX_BUL; i++) {
      bullets[i].move(bullets[i].dx, bullets[i].dy);
      bullets[i].checkBoundary(RAD);
    }

    if(e.type==Event::KeyPressed){
      if(e.key.code==Keyboard::Space){
        for(int i=0; i<MAX_BUL; i++){
          float x = rand()%(800-RAD-50)+50;
          float y = rand()%(600-RAD-50)+50;
          bullets[i].setPosition(x, y);        }
      }
    }

    window.clear();
    for(int i=0; i<MAX_BUL; i++){
      window.draw(bullets[i]);
    }
    window.display();
  }

  return 0;
}
