#include <SFML/Graphics/CircleShape.hpp>
#include <cstdio>
#include<iostream>
#include<SFML/Graphics.hpp>
#define RADIUS 5
#define MAX_BALLS 250
#define MAX_VEL 40
#define MIN_VEL 20

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

  //Colors
  Color colors[4] = {
    Color(221, 124, 183, 255),
    Color(107, 94, 188, 255),
    Color(156, 35, 80, 255),
    Color(223, 133, 223, 255)
  };

  //balls
  Ball balls[MAX_BALLS];
  srand(time(0));
  for(int i=0; i<MAX_BALLS; i++){
    Ball ball;
    ball.setRadius(RADIUS);
    ball.setPosition(rand()%(790-RADIUS), rand()%(590-RADIUS));
    ball.dx = (rand()%(MAX_VEL-MIN_VEL)+MIN_VEL)/100.00;
    ball.dy = (rand()%(MAX_VEL-MIN_VEL)+MIN_VEL)/100.00;
    ball.setFillColor(colors[rand()%4]);
    balls[i] = ball;
  }

  while(window.isOpen()){
    Event e;
    while(window.pollEvent(e)){
      if(e.type==Event::Closed)
        window.close();
    }
    //update

    for(int i=0; i<MAX_BALLS; i++){
      balls[i].checkBoundary(RADIUS);
      balls[i].move(balls[i].dx, balls[i].dy);
    }

    //draw
    window.clear();
    for(int i=0; i<MAX_BALLS; i++){
      window.draw(balls[i]);
    }
    window.display();
  }
  return 0;
}
