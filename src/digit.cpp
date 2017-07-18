#include "digit.h"

using namespace breakout;

// The index for the topmost horizontal line.
const auto HLINE_TOP = 0;
// The index for the middle horizontal line.
const auto HLINE_MIDDLE = 1;
// The index for the bottom horizontal line.
const auto HLINE_BOTTOM = 2;

// The index for the topleft vertical line.
const auto VLINE_LEFT_TOP = 0;
// The index for the bottomleft vertical line.
const auto VLINE_LEFT_BOTTOM = 1;
// The index for the topright vertical line.
const auto VLINE_RIGHT_TOP = 2;
// The index for the bottomright vertical line.
const auto VLINE_RIGHT_BOTTOM = 3;
// The index for the center vertical line.
const auto VLINE_CENTER = 4;

// The amount of blinks the digit does when blink is activated.
const auto BLINK_COUNT = 5;
// The amount of ticks (updates) to wait between each blink.
const auto BLINK_INTERVAL = 10;

Digit::Digit(Game& game) 
  : Drawable(game),
    mValue(0),
    mBlinksLeft(0),
    mBlinkTimer(0)
{
  refresh();
}

void Digit::setX(int x)
{
  Entity::setX(x);
  refresh();
}

void Digit::setY(int y)
{
  Entity::setY(y);
  refresh();
}

void Digit::setWidth(int w)
{
  Entity::setWidth(w);
  refresh();
}

void Digit::setHeight(int h)
{
  Entity::setHeight(h);
  refresh();
}

void Digit::render(SDL_Renderer& renderer)
{
  if (mVisible) {
    SDL_SetRenderDrawColor(&renderer, mColor.r, mColor.g, mColor.b, mColor.a);
    switch (mValue) {
    case 0:
      SDL_RenderFillRect(&renderer, &mHLines[HLINE_TOP]);
      SDL_RenderFillRect(&renderer, &mHLines[HLINE_BOTTOM]);
      SDL_RenderFillRect(&renderer, &mVLines[VLINE_LEFT_TOP]);
      SDL_RenderFillRect(&renderer, &mVLines[VLINE_LEFT_BOTTOM]);
      SDL_RenderFillRect(&renderer, &mVLines[VLINE_RIGHT_TOP]);
      SDL_RenderFillRect(&renderer, &mVLines[VLINE_RIGHT_BOTTOM]);
      break;
    case 1:
      SDL_RenderFillRect(&renderer, &mVLines[VLINE_RIGHT_TOP]);
      SDL_RenderFillRect(&renderer, &mVLines[VLINE_RIGHT_BOTTOM]);
      break;
    case 2:
      SDL_RenderFillRect(&renderer, &mHLines[HLINE_TOP]);
      SDL_RenderFillRect(&renderer, &mHLines[HLINE_MIDDLE]);
      SDL_RenderFillRect(&renderer, &mHLines[HLINE_BOTTOM]);
      SDL_RenderFillRect(&renderer, &mVLines[VLINE_LEFT_BOTTOM]);
      SDL_RenderFillRect(&renderer, &mVLines[VLINE_RIGHT_TOP]);
      break;
    case 3:
      SDL_RenderFillRect(&renderer, &mHLines[HLINE_TOP]);
      SDL_RenderFillRect(&renderer, &mHLines[HLINE_MIDDLE]);
      SDL_RenderFillRect(&renderer, &mHLines[HLINE_BOTTOM]);
      SDL_RenderFillRect(&renderer, &mVLines[VLINE_RIGHT_TOP]);
      SDL_RenderFillRect(&renderer, &mVLines[VLINE_RIGHT_BOTTOM]);
      break;
    case 4:
      SDL_RenderFillRect(&renderer, &mHLines[HLINE_MIDDLE]);
      SDL_RenderFillRect(&renderer, &mVLines[VLINE_LEFT_TOP]);
      SDL_RenderFillRect(&renderer, &mVLines[VLINE_RIGHT_TOP]);
      SDL_RenderFillRect(&renderer, &mVLines[VLINE_RIGHT_BOTTOM]);
      break;
    case 5:
      SDL_RenderFillRect(&renderer, &mHLines[HLINE_TOP]);
      SDL_RenderFillRect(&renderer, &mHLines[HLINE_MIDDLE]);
      SDL_RenderFillRect(&renderer, &mHLines[HLINE_BOTTOM]);
      SDL_RenderFillRect(&renderer, &mVLines[VLINE_LEFT_TOP]);
      SDL_RenderFillRect(&renderer, &mVLines[VLINE_RIGHT_BOTTOM]);
      break;
    case 6:
      SDL_RenderFillRect(&renderer, &mHLines[HLINE_TOP]);
      SDL_RenderFillRect(&renderer, &mHLines[HLINE_MIDDLE]);
      SDL_RenderFillRect(&renderer, &mHLines[HLINE_BOTTOM]);
      SDL_RenderFillRect(&renderer, &mVLines[VLINE_LEFT_TOP]);
      SDL_RenderFillRect(&renderer, &mVLines[VLINE_LEFT_BOTTOM]);
      SDL_RenderFillRect(&renderer, &mVLines[VLINE_RIGHT_BOTTOM]);
      break;
    case 7:
      SDL_RenderFillRect(&renderer, &mHLines[HLINE_TOP]);
      SDL_RenderFillRect(&renderer, &mVLines[VLINE_RIGHT_TOP]);
      SDL_RenderFillRect(&renderer, &mVLines[VLINE_RIGHT_BOTTOM]);
      break;
    case 8:
      SDL_RenderFillRect(&renderer, &mHLines[HLINE_TOP]);
      SDL_RenderFillRect(&renderer, &mHLines[HLINE_MIDDLE]);
      SDL_RenderFillRect(&renderer, &mHLines[HLINE_BOTTOM]);
      SDL_RenderFillRect(&renderer, &mVLines[VLINE_LEFT_TOP]);
      SDL_RenderFillRect(&renderer, &mVLines[VLINE_LEFT_BOTTOM]);
      SDL_RenderFillRect(&renderer, &mVLines[VLINE_RIGHT_TOP]);
      SDL_RenderFillRect(&renderer, &mVLines[VLINE_RIGHT_BOTTOM]);
      break;
    case 9:
      SDL_RenderFillRect(&renderer, &mHLines[HLINE_TOP]);
      SDL_RenderFillRect(&renderer, &mHLines[HLINE_MIDDLE]);
      SDL_RenderFillRect(&renderer, &mHLines[HLINE_BOTTOM]);
      SDL_RenderFillRect(&renderer, &mVLines[VLINE_LEFT_TOP]);
      SDL_RenderFillRect(&renderer, &mVLines[VLINE_RIGHT_TOP]);
      SDL_RenderFillRect(&renderer, &mVLines[VLINE_RIGHT_BOTTOM]);
      break;
    }
  }
}

void Digit::refresh()
{
  // clear old lines.
  mHLines.clear();
  mVLines.clear();

  // ensure that containers contain correct amount of items.
  mHLines.resize(3);
  mVLines.resize(5);

  // precalculate thickness and half-height.
  const auto thickness = (mRect.h / 5);
  const auto halfHeight = static_cast<int>(std::ceil(mRect.h / 2) - 1);

  // use some value aliases to make code more clear.
  auto x = mRect.x;
  auto y = mRect.y;
  auto w = mRect.w;
  auto h = mRect.h;

  // construct horizontal line draw instructions.
  mHLines[HLINE_TOP] = { x, y, w, thickness };
  mHLines[HLINE_MIDDLE] = { x - 1, y + halfHeight - thickness / 2, w + 2, thickness };
  mHLines[HLINE_BOTTOM] = { x, y + (h - thickness), w, thickness };

  // construct vertical line draw instructions.
  mVLines[VLINE_LEFT_TOP] = { x - 1, y, thickness, halfHeight + 1 };
  mVLines[VLINE_LEFT_BOTTOM] = { x - 1, y + halfHeight, thickness, halfHeight + 1 };
  mVLines[VLINE_RIGHT_TOP] = { x + w - thickness, y, thickness + 1, halfHeight + 1 };
  mVLines[VLINE_RIGHT_BOTTOM] = { x + w - thickness, y + halfHeight, thickness + 1, halfHeight + 1 };
  mVLines[VLINE_CENTER] = { x + w / 2 - thickness, y, thickness, h };
}

void Digit::setBlink(bool active)
{
  if (active == false) {
    mBlinksLeft = 0;
    mBlinkTimer = 0;
    setVisible(true);
  } else {
    mBlinksLeft = BLINK_COUNT;
    mBlinkTimer = 0;
  }
}

void Digit::update(float dt)
{
  if (mBlinksLeft > 0) {
    mBlinkTimer--;
    if (isVisible() == true) {
      // number is currently shown, so check whether it is time to hide it.
      if (mBlinkTimer <= 0) {
        setVisible(false);
        mBlinkTimer = BLINK_INTERVAL;
      }
    } else {
      // number is currently hidden, so check whether it is time to show it.
      if (mBlinkTimer <= 0) {
        setVisible(true);
        mBlinksLeft--;
        if (mBlinksLeft > 0) {
          mBlinkTimer = BLINK_INTERVAL;
        }
      }
    }
  }
}