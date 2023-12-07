
// Created by lewis on 04/12/2023.


#ifndef SFMLGAME_TEXTBOX_H
#define SFMLGAME_TEXTBOX_H

#include <iostream>
#include <SFML/Graphics.hpp>
#include <sstream>

#define DELETE_KEY 8
#define ENTER_KEY 13
#define ESCAPE_KEY 27

class TextBox
{
 public:
  TextBox() {}

  TextBox(int size, sf::Color color, bool sel)
  {
    if (!font.loadFromFile("Data/Fonts/OpenSans-Bold.ttf"))
    {
      std::cout << "font did not load \n";
    }

    textbox.setCharacterSize(size);
    textbox.setOutlineColor(color);
    isSelected = sel;

    if (sel)
    {
      textbox.setString("_");
    }
    else
    {
      textbox.setString("");
    }
  }

  void setFont(sf::Font &font)
  {
    textbox.setFont(font);
  }

  void setPosition(sf::Vector2f pos)
  {
    textbox.setPosition(pos);
  }

  void setSelected(bool sel)
  {
    if (!sel)
    {
      std::string t = text.str();
      std::string newT = "";
      for (int i = 0; i < t.length() -1; ++i)
      {
        newT += t[i];
      }
      textbox.setString(newT);
    }
  }

  std::string getText()
  {
    return text.str();
  }

  void drawTo(sf::RenderWindow &window)
  {
    window.draw(textbox);
  }

  void typedOn(sf::Event input)
  {
    if (isSelected)
    {
      int charTyped = input.text.unicode;
      if (charTyped < 128)
      {
        if (text.str().length() <= 1028)
        {
          inputLogic(charTyped);
        }
        else if (text.str().length() > 1028 && charTyped == DELETE_KEY)
        {
          deleteLastChar();
        }
        else
        {
          inputLogic(charTyped);
        }
      }
    }
  }

 private:

  sf::Text textbox;
  sf::Font font;
  std::ostringstream text;
  bool isSelected = false;

  void inputLogic(int charTyped)
  {
    if (charTyped != DELETE_KEY && charTyped != ENTER_KEY && charTyped != ESCAPE_KEY)
    {
      text << static_cast<char>(charTyped);
    }
    else if (charTyped == DELETE_KEY)
    {
      if (text.str().length() > 0)
      {
        deleteLastChar();
      }
    }
    else if (charTyped == ENTER_KEY)
    {
      std::string enteredText;
      enteredText = text.str();
      std::cout << enteredText << std::endl;

      for (int i = 0; i < enteredText.length(); ++i)
      {
        TextBox::deleteLastChar();
      }
    }
    textbox.setString(text.str() + "_");
  }

  void deleteLastChar()
  {
      std::string t = text.str();
      std::string newT = "";
      for (int i = 0; i < t.length() -1; ++i)
      {
      newT += t[i];
      }
      text.str("");
      text << newT;

      textbox.setString(text.str());
  }
};

#endif // SFMLGAME_TEXTBOX_H