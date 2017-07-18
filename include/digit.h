/*! A class that presents a single digit within the Breakout game.
 *
 *  Digits are used to show three kinds of information for the user in the
 *  Breakout game; player index, the index of the current ball and the player
 *  specific scores. Each digit may contain a value from the range [0..9] and
 *  may also be activated to perform a blink that is commonly used to emphasise
 *  the digit(s) that have just been updated.
 */
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

    void setBlink(bool active);

    void update(float dt);

    void setValue(int value) { mValue = value; }

    int getValue() const { return mValue; }
  private:
    int                   mValue;
    std::vector<SDL_Rect> mHLines;
    std::vector<SDL_Rect> mVLines;
    int                   mBlinksLeft;
    int                   mBlinkTimer;
  };
}

#endif