//
// Created by lewis_cjv4sqf on 10/11/2023.
//

#ifndef SFMLGAME_GAMEOBJECT_H
#define SFMLGAME_GAMEOBJECT_H
#include "Vector2.h"
#include <SFML/Graphics.hpp>

class GameObject
{
 public:
  GameObject();
  ~GameObject();

  bool initialiseSprite(sf::Texture &texture, std::string filename);
  sf::Sprite* getSprite();
  bool visibility = true;

  int speed = 50;
  int velocity = 100.0f;
  Vector2 Velocity = {0.0f, 0.0f};
  sf::Clock clock;

  int getSpeed() const;
  void setSpeed(int speed);
  const Vector2& getDirection() const;
  void setDirection(const Vector2& direction);
  const Vector2& getVelocity() const;
  void setVelocity(const Vector2& velocity);


 private:

  Vector2 Direction = {0,0};
  sf::Sprite* sprite = nullptr;
};

#endif // SFMLGAME_GAMEOBJECT_H
