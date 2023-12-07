//
// Created by lewis_cjv4sqf on 10/11/2023.
//

#include "Player.h"
#include <iostream>

Player::Player()
{

}

Player::~Player()
{
  delete sprite;
}

bool Player::initialiseSprite(sf::Texture &texture,std::string filename)
{
  sprite = new sf::Sprite();


  if (!texture.loadFromFile(filename))
  {
    std::cout <<filename + "texture did not load\n";
  }
  else
  {
    sprite->setTexture(texture);
  }
  return true;
}

sf::Sprite* Player::getSprite()
{
  return sprite;
}
int Player::getGravity() const
{
  return Gravity;
}
const Vector2& Player::getDirection() const
{
  return direction;
}
void Player::setDirection(const Vector2& direction)
{
  Player::direction = direction;
}

float Player::getCenterX(Player* player)
{
  centerX = player->getSprite()->getPosition().x + (player->getSprite()->getGlobalBounds().width / 2);
  return centerX;
}

float Player::getCenterY(Player* player)
{
  centerY = player->getSprite()->getPosition().y + (player->getSprite()->getGlobalBounds().height / 2);
  return centerY;
}

sf::Vector2f& Player::getVelocity()
{
  return *velocityVector;
}

void Player::setVelocity(sf::Vector2f& velocity)
{
  *velocityVector = velocity;
}

float Player::getMovementSpeed() const
{
  return *movementSpeed;
}

void Player::setMovementSpeed(float speed)
{
  *movementSpeed = speed;
}

void Player::updatePosition(float timeDelta)
{
  sf::Vector2f normalisedVector;
  float length = sqrt((velocityVector->x * velocityVector->x) + (velocityVector->y * velocityVector->y));
  if (length != 0)
    normalisedVector = sf::Vector2f(velocityVector->x / length, velocityVector->y / length);
  sf::Vector2f newPosition = Player::getSprite()->getPosition() + ((normalisedVector * *movementSpeed) * timeDelta);
  Player::getSprite()->setPosition(newPosition);
}

void Player::resetVelocity()
{
  velocityVector->x = 0;
  velocityVector->y = 0;
}
