#include "Game.h"
#include "TextBox.h"
#include <SFML/Graphics.hpp>
#include <iostream>

int main()
{
  std::cout << "You should see a window that opens as well as this writing to console..."
            << std::endl;

  // create window and set up
  sf::RenderWindow window(sf::VideoMode(1920, 1080), "SFML Base Game");
  window.setFramerateLimit(60);

  //initialise an instance of the game class
  bool x = *std::getenv("doServer") == '1';
  Game game(window, x);

  //run the init function of the game class and check it all initialises ok
  if (!game.init())
  {
    return 0;
  }

  // A Clock starts counting as soon as it's created
  sf::Clock clock;

  sf::Font text_box_font;
  text_box_font.loadFromFile("Data/Fonts/OpenSans-Bold.ttf");
  TextBox textbox1(20, (sf::Color::White), true);
  textbox1.setFont(text_box_font);
  textbox1.setPosition({80, 1000});

  // Game loop: run the program as long as the window is open
  while (window.isOpen())
  {
    // check all the window's events that were triggered since the last iteration of the loop
    sf::Event event;

    //calculate delta time
    sf::Time time = clock.restart();
    float dt = time.asSeconds();

    //'process inputs' element of the game loop
    while (window.pollEvent(event))
    {
      // "close requested" event: we close the window
      if (event.type == sf::Event::Closed)
        window.close();

      if (event.type == sf::Event::KeyPressed)
        game.keyPressed(event);

      if (event.type == sf::Event::KeyReleased)
        game.keyReleased(event);

      switch (event.type)
      {
        case sf::Event::TextEntered:
          textbox1.typedOn(event);
      }
    }


    //'update' element of the game loop
    game.update(dt);

    window.clear(sf::Color::Black);

    //'render' element of the game loop
    game.render();
    textbox1.drawTo(window);
    window.display();

    //'render' textbox

  }

  return 0;
}
