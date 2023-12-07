//
// Created by lewis_cjv4sqf on 10/11/2023.
//

#include "GameObject.h"
#include <SFML/Graphics.hpp>
#include <iostream>

GameObject::GameObject()
{

}

GameObject::~GameObject()
{
  delete sprite;
}

bool GameObject::initialiseSprite(sf::Texture &texture, std::string filename)
{
  sprite = new sf::Sprite();
  if (!texture.loadFromFile(filename))
  {
    std::cout << "Texture did not load " << filename << std::endl;
  }
  sprite->setTexture(texture);
  return true;
}

sf::Sprite* GameObject::getSprite()
{
  return sprite;
}

int GameObject::getSpeed() const
{
  return speed;
}

void GameObject::setSpeed(int speed)
{
  GameObject::speed = speed;
}

const Vector2& GameObject::getDirection() const
{
  return Direction;
}

void GameObject::setDirection(const Vector2& direction)
{
  Direction = direction;
}

const Vector2& GameObject::getVelocity() const
{
  return Velocity;
}

void GameObject::setVelocity(const Vector2& velocity)
{
  Velocity = velocity;
}