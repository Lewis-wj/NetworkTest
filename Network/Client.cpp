
#include "Client.h"
#include "PacketStruct.h"
void Client::connect()
{
  if (socket == nullptr) socket = std::make_unique<sf::TcpSocket>();
  if (socket->connect("127.0.0.1", 53000) == sf::Socket::Status::Done)
  {
    std::cout <<"You're Connected!" << std::endl;
    connected = true;
  }
  else
  {
    std::cout << "failed to connect";
  }
}

void Client::run()
{
  running = true;

  std::thread input_thread ([&] {
                             input(*socket);
                           });
  input_thread.detach();

  std::thread received_thread ([&] {
                                receive(*socket, connected);
                              });
  received_thread.detach();
}

void Client::input(sf::TcpSocket& iSocket) const
{
  while(running)
  {
    std::string str;
    std::getline(std::cin, str);
    std::cin.clear();

    sf::Packet msgPacket;

    msgPacket << str;

    if (connected)
    {
      iSocket.send(msgPacket);
    }
  }
}

void Client::receive(sf::TcpSocket& iSocket, bool connected) const
{
  while(running && connected)
  {
    sf::Packet receivedPacket;
    while(connected)
    {
      auto status = socket->receive(receivedPacket);

      if (status == sf::Socket::Status::Disconnected)
      {
        connected = false;
        std::cout << "clean disconnection" <<std::endl;
        socket->disconnect();
        return;
      }

      // set string variable
      std::string msg;

      // convert packet to string
      receivedPacket >> msg;

      // print message to console
      std::cout << msg << std::endl;

      //convert string to sf::text
      Client::logReturn(text, msg);

    }
  }
}

sf::Text Client::logReturn(sf::Text log, std::string msg) const
{
  log.setString(msg);
  return log;
}

