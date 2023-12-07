
#include "Game.h"
#include "../Network/Server.h"
#include "TextBox.h"
#include "tmxlite/Map.hpp"
#include "tmxlite/TileLayer.hpp"
#include <iostream>
#include <sstream>

Game::Game(sf::RenderWindow& game_window, bool server)
  : window(game_window), isServer(server)
{
  srand(time(NULL));
}

Game::~Game()
{

}

bool Game::init()
{

  sf::err().rdbuf(NULL);

  if (!title_font.loadFromFile("Data/Fonts/OpenSans-Bold.ttf"))
  {
    std::cout << "font did not load \n";
  }

  if (!text_box_font.loadFromFile("Data/Fonts/OpenSans-Bold.ttf"))
  {
    std::cout << "font did not load \n";
  }

  title_text.setString("My Game");
  title_text.setFont(title_font);
  title_text.setCharacterSize(50);
  title_text.setFillColor(sf::Color(0, 0, 0));
  title_text.setOutlineColor(sf::Color(255,255,255));
  title_text.setOutlineThickness(3);
  title_text.setPosition(window.getSize().x/2 -
                           title_text.getGlobalBounds().width/2, 300);

  username_text.setString("Player 1");
  username_text.setFont(text_box_font);
  username_text.setCharacterSize(15);
  username_text.setFillColor(sf::Color(255,255,255,Opacity));
  username_text.setOutlineColor(sf::Color(0,0,0,Opacity));
  username_text.setOutlineThickness(1.5);

  msg_text.setString("Hello World");
  msg_text.setPosition(100,100);
  msg_text.setFont(text_box_font);
  msg_text.setCharacterSize(50);
  msg_text.setFillColor(sf::Color(255,255,255,Opacity));

  player.initialiseSprite(player_texture, "Data/Images/1 walk.png");
  player.getSprite()->setScale(3,3);
  sf::IntRect rectIdle(TopWalk, TopWalk, Width, Height);
  player.getSprite()->setTextureRect(rectIdle);


  tmx::Map map;
  if (!tileMap->loadFromFile("Data/tileset.png"))
  {
    std::cout << "FAILED TO LOAD SPRITESHEET" << std::endl;
  }

  if (!map.load("Data/Tilemap_new.tmx"))
  {
    std::cout << "FAILED TO LOAD MAP DATA" << std::endl;
  }

  const unsigned int MAP_COLUMNS = map.getTileCount().x;
  const unsigned int MAP_ROWS = map.getTileCount().y;

  auto& tile_size = map.getTileSize();
  TILE_MAP.reserve(map.getLayers().size());

  for (const auto& layer : map.getLayers())
  {
    TILE_MAP.emplace_back(std::vector<std::unique_ptr<Tile>>());

    const auto& tiles = layer->getLayerAs<tmx::TileLayer>().getTiles();
    TILE_MAP.back().reserve(tiles.size());

    for(const auto& tile : tiles)
    {
      SetTileWithID(MAP_COLUMNS, tile_size, tile);
    }
  }

  if(isServer)
  {
    server = std::make_unique<Server>();
    server->init();
    server->run();
  }
  else
  {
    client = std::make_unique<Client>();
    client->connect();
    client->run();
  }
  return true;
}

void Game::update(float dt)
{
  playerUsername();
  spriteSheetMovement();
//  textOutput();
//  setString();
  *previousPos = player.getSprite()->getPosition();
  player.getSprite()->move(player.getVelocity().x * moveSpeed * dt,
                           player.getVelocity().y * moveSpeed * dt);
  collisions();
}

void Game::textOutput()
{
  msg_text.setString(client->text.getString());
  temp_string = msg_text.getString();
  std::cout << temp_string;
}

void Game::render()
{
  if(menu_state)
  {
    window.draw(title_text);
  }

  if(game_state)
  {
    window.clear(sf::Color::Black);
    for (const auto& layer : TILE_MAP)
    {
      for (const auto& tile : layer)
      {
        if (tile->GetID() != 0)
        {
          window.draw(*tile->GetSprite());
        }
      }
    }
  }
  window.draw(msg_text);
  window.draw(username_text);
  window.draw(*player.getSprite());
}

void Game::mouseClicked(sf::Event event)
{
  //get the click position
  sf::Vector2i click = sf::Mouse::getPosition(window);
}

void Game::keyPressed(sf::Event event)
{
  if (event.key.code == sf::Keyboard::D)
  {
    player.getVelocity() = sf::Vector2f(1,0);
    moveRight = true;
  }
  if (event.key.code == sf::Keyboard::A)
  {
    player.getVelocity() = sf::Vector2f(-1,0);
    moveLeft = true;
  }
  if (event.key.code == sf::Keyboard::W)
  {
    player.getVelocity() = sf::Vector2f(0,-1);
    moveUp = true;
  }
  if (event.key.code == sf::Keyboard::S)
  {
    player.getVelocity() = sf::Vector2f(0,1);
    moveDown = true;
  }
  if (event.key.code == sf::Keyboard::I)
  {
//    msgReceived = true;
    msg_text.setString(client->text.getString());
    std::cout << &msg_text.getString();
  }
}

void Game::keyReleased(sf::Event event)
{
  if (event.key.code == sf::Keyboard::D)
  {
    player.getVelocity() = sf::Vector2f(0,0);
    moveRight = false;
  }
  if (event.key.code == sf::Keyboard::A)
  {
    player.getVelocity() = sf::Vector2f(0,0);
    moveLeft = false;
  }
  if (event.key.code == sf::Keyboard::W)
  {
    player.getVelocity() = sf::Vector2f(0,0);
    moveUp = false;
  }
  if (event.key.code == sf::Keyboard::S)
  {
    player.getVelocity() = sf::Vector2f(0,0);
    moveDown = false;
  }
}

//void Game::setString()
//{
//  msg_text.setString(client->text.getString());
//}

void Game::collisions()
{
  for(const auto& tile : TILE_MAP[1])
  {
    if (player.getSprite()->getGlobalBounds().intersects(tile->GetSprite()->getGlobalBounds()))
    {
      {
        player.getSprite()->setPosition(*previousPos);
        std::cout << "collided" << std::endl;
      }
    }
  }
}

void Game::spriteSheetMovement()
{
  // Walk down sprite sheet
  if (moveDown && clock.getElapsedTime().asSeconds() > 0.25f)
  {
    LeftWalk = 0;
    if (TopWalk == 48)
    {
      TopWalk = 0;
    }
    else
    {
      TopWalk += 16;
    }
    clock.restart();
  }

  // Walk up sprite sheet
  if (moveUp && clock.getElapsedTime().asSeconds() > 0.25f)
  {
    LeftWalk = 16;
    if (TopWalk == 48)
    {
      TopWalk = 0;
    }
    else
    {
      TopWalk += 16;
    }
    clock.restart();
  }
  // Walk right sprite sheet
  if (moveRight && !moveLeft && clock.getElapsedTime().asSeconds() > 0.25f)
  {
    LeftWalk = 32;
    if (TopWalk == 48)
    {
      TopWalk = 0;
    }
    else
    {
      TopWalk += 16;
    }
    clock.restart();
  }
  // Walk left sprite sheet
  if (moveLeft && !moveRight && clock.getElapsedTime().asSeconds() > 0.25f)
  {
    LeftWalk = 32;
    if (TopWalk == 48)
    {
      TopWalk = 0;
    }
    else
    {
      TopWalk += 16;
    }
    clock.restart();
  }
  if (moveLeft && !moveRight && horizontalImg == 3)
  {
    horizontalImg = -3;
    player.getSprite()->setPosition(
      player.getSprite()->getPosition().x +
        player.getSprite()->getGlobalBounds().width,
      player.getSprite()->getPosition().y);
    player.getSprite()->setScale(horizontalImg, 3);
  }
  else if (moveRight && !moveLeft && horizontalImg == -3)
  {
    horizontalImg = 3;
    player.getSprite()->setPosition(
      player.getSprite()->getPosition().x -
        player.getSprite()->getGlobalBounds().width,
      player.getSprite()->getPosition().y);
    player.getSprite()->setScale(horizontalImg, 3);
  }
  player.getSprite()->setTextureRect(
    sf::IntRect(LeftWalk, TopWalk, Width, Height));
}

void Game::playerUsername()
{
  username_text.setPosition(player.getSprite()->getPosition().x +
                              (player.getSprite()->getGlobalBounds().width/2)
                              - username_text.getGlobalBounds().width/2,
                            player.getSprite()->getPosition().y - 20);

  if (horizontalImg == -3)
  {
    username_text.setPosition(player.getSprite()->getPosition().x +
                                (player.getSprite()->getGlobalBounds().width/2)
                                - username_text.getGlobalBounds().width/2
                              - player.getSprite()->getGlobalBounds().width,
                              player.getSprite()->getPosition().y - 20);
  }
}

void Game::SetTileWithID(
  const unsigned int MAP_COLUMNS, const tmx::Vector2u& tile_size,
  const tmx::TileLayer::Tile& tile)
{
  auto& current = *TILE_MAP.back().emplace_back(std::make_unique<Tile>(tile.ID, *tileMap));

  if(current.GetID() == 0)
  {
    current.GetSprite()->setTextureRect(
      sf::IntRect(0,0,0,0));
  }
  else
  {
    current.GetSprite()->setTextureRect(sf::IntRect((((current.GetID()-1) %9) * tile_size.x),abs((current.GetID()-1) /9) * tile_size.y,tile_size.x,tile_size.y));
  }

  current.GetSprite()->setPosition(((TILE_MAP.back().size()-1) % MAP_COLUMNS) * tile_size.x,((TILE_MAP.back().size()-1) / MAP_COLUMNS) * tile_size.y);
}