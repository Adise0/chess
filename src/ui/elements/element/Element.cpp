#include "Element.h"
#include <algorithm>
#include <stdexcept>


namespace Chess::Rendering::Elements {


void Element::Render() {
  if (hasColor) renderer.Render(rect, Texture::color);
  else renderer.Render(rect, Texture::base);
};

void Element::HandleEvent(SDL_Event &event) {}

Element::Element() {
  if (renderer.baseImage) hasColor = false;
  else hasColor = true;
}

} // namespace Chess::Rendering::Elements
