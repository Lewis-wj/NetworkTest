//
// Created by lewis_cjv4sqf on 10/11/2023.
//

#ifndef SFMLGAME_PLAYER_H
#define SFMLGAME_PLAYER_H

#include "Vector2.h"
#include "math.h"
#include <SFML/Graphics.hpp>

class Player
{
 public:
  Player();
  ~Player();

  Player(std::string player)
  {
    *movementSpeed = 100;
    *velocityVector = sf::Vector2f(0,0);
  }

  bool initialiseSprite(sf::Texture &texture,std::string filename);
  sf::Sprite* getSprite();
  bool visibility = true;

  sf::Clock jump_clock;
  sf::Clock hit_clock;

  int getGravity() const;
  const Vector2& getDirection() const;
  void setDirection(const Vector2& direction);

  void resetVelocity();
  sf::Vector2f& getVelocity();
  void setVelocity(sf::Vector2f& velocity);
  void updatePosition(float timeDelta);
  void setMovementSpeed(float speed);
  float getMovementSpeed() const;
  void setPosition(const Vector2& position);

  float centerX;
  float centerY;
  bool isJumping = false;
  bool contact = false;

  bool isMoveLeft = false;
  bool isMoveRight = false;

  float getCenterX(Player* player);
  float getCenterY(Player* player);

 private:
  std::unique_ptr<sf::Vector2f> previousPosition = std::make_unique<sf::Vector2f>();
  std::unique_ptr<sf::Vector2f> velocityVector = std::make_unique<sf::Vector2f>();
  std::unique_ptr<float> movementSpeed = std::make_unique<float>();

  sf::Sprite* sprite = nullptr;
  int speed = 0;
  int Gravity = 7.0;
  Vector2 direction = {0, 0};


};

#endif // SFMLGAME_PLAYER_H
