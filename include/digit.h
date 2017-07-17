#ifndef BREAKOUT_DIGIT_H
#define BREAKOUT_DIGIT_H

#include "drawable.h"

#include <vector>

namespace breakout
{
  class Digit final : public Drawable
  {
  public:
    Digit(Game& game);

    void setX(int x) override;
    void setY(int y) override;
    void setWidth(int w) override;
    void setHeight(int h) override;

    void render(SDL_Renderer& renderer) override;

    void refresh();

    void setValue(int value) { mValue = value; }

    int getValue() const { return mValue; }
  private:
    int                   mValue;
    std::vector<SDL_Rect> mHLines;
    std::vector<SDL_Rect> mVLines;
  };
}

#endif