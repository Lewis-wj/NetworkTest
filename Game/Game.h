
#ifndef PLATFORMER_GAME_H
#define PLATFORMER_GAME_H

#include "../Network/Client.h"
#include "../Network/Server.h"
#include "../TileMap/Tile.h"
#include "GameObject.h"
#include "Player.h"
#include "Vector2.h"
#include "tmxlite/TileLayer.hpp"
#include "tmxlite/Types.hpp"
#include <SFML/Graphics.hpp>

class Game
{
 public:
  Game(sf::RenderWindow& window, bool server);
  ~Game();
  bool init();
  void update(float dt);
  void render();
  void mouseClicked(sf::Event event);
  void keyPressed(sf::Event event);
  void keyReleased(sf::Event event);
  void updatePlayer(float deltaT);
  void movement(float dt);
  void textBox();
  void playerUsername();
  void collisions();
  void textOutput();
  void spriteSheetMovement();
  void setString();
  sf::Text logreturnReverse(sf::Text msg, std::string log);

  bool moveRight = false;
  bool moveLeft = false;
  bool moveUp = false;
  bool moveDown = false;

  bool msgReceived = false;
  bool validPosition = true;

  std::string temp;

  int Opacity = 255;

  int moveSpeed = 100;

  int LeftWalk = 0;
  int TopWalk = 0;
  int Width = 16;
  int Height = 16;
  int horizontalImg = 3;

  bool menu_state = false;
  bool game_state = true;

  sf::Text title_text;
  sf::Font title_font;
  sf::Text username_text;
  sf::Text msg_text;
  sf::Font text_box_font;
  sf::Clock clock;
  sf::Clock textBoxClock;
  Player player;
  sf::Texture player_texture;
  std::string temp_string;

 private:

  std::unique_ptr<sf::Vector2f> previousPos = std::make_unique<sf::Vector2f>();
  std::unique_ptr<sf::Texture> tileMap = std::make_unique<sf::Texture>();
  std::unique_ptr<Player> player1 = std::make_unique<Player>("Data/Images/pacman.png");
  std::vector<std::vector<std::unique_ptr<Tile>>> TILE_MAP;

  sf::RenderWindow& window;
  bool isServer= true;

  std::unique_ptr<Client> client = nullptr;
  std::unique_ptr<Server> server = nullptr;

  void SetTileWithID(
    const unsigned int columns, const tmx::Vector2<unsigned int>& vector2,
    const tmx::TileLayer::Tile& tile);


};

#endif // PLATFORMER_GAME_H
