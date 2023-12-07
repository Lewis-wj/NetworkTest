//
// Created by lewis_cjv4sqf on 02/12/2023.
//

#ifndef SFMLGAME_PACKETSTRUCT_H
#define SFMLGAME_PACKETSTRUCT_H

#include <SFML/Network/Packet.hpp>
#include <SFML/System/Vector2.hpp>
#include <string>

enum PacketType
{
  MESSAGE = 0,
  MOVEMENT = 1
};

struct Message
{
  std::string username;
  std::string content;
};

sf::Packet& operator <<(std::basic_string<char> packet, const Message& msg);
sf::Packet& operator >>(sf::Packet& packet, Message& msg);

struct Movement
{
  std::string username;
  sf::Vector2f position;
};

sf::Packet& operator <<(sf::Packet& packet, const Movement& nvm);
sf::Packet& operator >>(sf::Packet& packet, Movement& nvm);



#endif // SFMLGAME_PACKETSTRUCT_H
