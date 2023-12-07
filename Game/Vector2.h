//
// Created by lewis_cjv4sqf on 10/11/2023.
//

#ifndef SFMLGAME_VECTOR2_H
#define SFMLGAME_VECTOR2_H

struct Vector2
{
  // construction
  Vector2(float x_, float y_);
  Vector2(const Vector2& rhs);

  // operations
  Vector2 operator*(float scalar);
  Vector2& operator=(const Vector2& rhs);
  void normalise();

  // data
  float x = 0;
  float y = 0;
};

#endif // SFMLGAME_VECTOR2_H
