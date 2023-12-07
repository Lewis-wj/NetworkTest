
#include "Server.h"

void Server::init()
{
  if (listener == nullptr) listener = std::make_unique<sf::TcpListener>();
  if (listener->listen(53000) != sf::Socket::Done)
  {
    //error...
  }
}

void Server::run()
{
  while(running)
  {
    sf::TcpSocket& cSock =
      connections.emplace_back(std::make_unique<sf::TcpSocket>()).operator*();

    if (listener->accept(cSock) != sf::Socket::Done)
    {
      connections.pop_back();
      return;
    }
    std::cout << "Client connected @ " << cSock.getRemotePort() << std::endl;
    workers.emplace_back([&]{
                           listen(cSock);
                           cSock.disconnect();

                           std::cout << "detected disconnect\n";
                           std::lock_guard<std::mutex>lck(std::mutex);

                           for (int i = 0; i < connections.size(); ++i)
                           {
                             if (connections[i]->getRemotePort() == cSock.getRemotePort()) continue;

                             connections.erase(std::next(connections.begin(), getConnectionIndex(cSock)));
                             break;
                           }
                         });
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
  }
}

int Server::getConnectionIndex(sf::TcpSocket&targetSocket)
{
  for (int i = 0; i < connections.size(); ++i)
  {
    if (connections[i]->getRemotePort() == targetSocket.getRemotePort()) return i;
  }

  return -1;
}

//void Server::send(std::string buffer)
//{
//  auto message = reinterpret_cast<char*>(buffer.data());
//
//  std::lock_guard<std::mutex>lck(std::mutex);
//
//  for (auto & connection : connections)
//  {
//    connection->send(message, buffer.size());
//  }
//}

void Server::listen(sf::TcpSocket& cSocket)
{
  bool continue_receiving = true;

  sf::Packet receivePacket;

  while (continue_receiving)
  {
    auto status = cSocket.receive(receivePacket);
    if (status == sf::Socket::Status::Disconnected)
    {
      std::cout << "Disconnected " << std::endl;
      return;
    }

    std::string msg;
    receivePacket >> msg;
    std::cout << "Message Received: " << msg << std::endl;
    receivePacket << msg;

    sendAll(receivePacket, getConnectionIndex(cSocket));
  }
  cSocket.disconnect();
}

void Server::sendAll(sf::Packet packetToSend, int senderIdx)
{
  for (int i = 0; i < connections.size(); ++i)
  {
    if (i != senderIdx)
    {
      connections[i]->send(packetToSend);
    }
  }
}

