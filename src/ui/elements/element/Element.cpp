#include "Element.h"
#include <algorithm>
#include <stdexcept>


namespace Chess::Rendering::Elements {


void Element::Render() {
  if (hasColor) renderer.Render(rect);
  else renderer.Render(rect, Texture::base);
};

void Element::HandleEvent(SDL_Event &event) {}

Element::Element() {
  if (renderer.color) hasColor = true;
  else hasColor = false;
}

} // namespace Chess::Rendering::Elements
