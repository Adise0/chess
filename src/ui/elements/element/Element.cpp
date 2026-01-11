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

void Element::HandleEvent(SDL_Event &event) {}
void Element::Update(float deltaTime) {}

Element::Element() {
  // #region Element
  if (renderer.baseImage) hasColor = false;
  else hasColor = true;
  // #endregion
}
} // namespace Chess::Rendering::Elements
