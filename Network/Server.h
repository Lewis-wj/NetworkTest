//
// Created by l7-jeffery on 11/10/2023.
//

#ifndef SFMLGAME_SERVER_H
#define SFMLGAME_SERVER_H

#include <SFML/Network.hpp>
#include <thread>
#include <list>
#include <iostream>
#include <mutex>
#include <memory>

class Server
{
 public:
  void init();
  void run();
  void listen(sf::TcpSocket& cSocket);

  std::string output;

 private:
  std::vector<std::thread> workers;
  std::vector<std::unique_ptr<sf::TcpSocket>> connections;

  std::unique_ptr<sf::TcpListener> listener;
  std::unique_ptr<sf::TcpSocket> socket;

  bool running = true;

  //void send(std::string buffer);
  void sendAll(sf::Packet packetToSend, int senderIdx);
  int getConnectionIndex(sf::TcpSocket&targetSocket);
};

#endif // SFMLGAME_SERVER_H
