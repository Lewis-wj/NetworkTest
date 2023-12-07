//
// Created by l7-jeffery on 11/10/2023.
//

#ifndef SFMLGAME_CLIENT_H
#define SFMLGAME_CLIENT_H

#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <iostream>
#include <atomic>
#include <thread>

class Client
{

 public:
  void connect();
  void input(sf::TcpSocket& iSocket) const;
  void receive(sf::TcpSocket& iSocket, bool connected) const;
  void run();

  sf::Text logReturn(sf::Text log, std::string msg) const;

  sf::Text text;
  sf::Text temp;

  std::atomic<bool> running = false;
  std::atomic<bool> connected = false;


 private:
  std::unique_ptr<sf::TcpSocket> socket;

};

#endif // SFMLGAME_CLIENT_H
