#include "Element.h"
#include <algorithm>
#include <stdexcept>


namespace Chess::Rendering::Elements {

void Element::Render() {
  // #region Render
  if (hasColor) renderer.Render(rect, Texture::color);
  else renderer.Render(rect, Texture::base);
  // #endregion
};

bool Element::HandleEvent(SDL_Event &event) { return false; }

Element::Element() {
  // #region Element
  if (renderer.baseImage) hasColor = false;
  else hasColor = true;
  // #endregion
}
} // namespace Chess::Rendering::Elements
