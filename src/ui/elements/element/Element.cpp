#include "Element.h"
#include <algorithm>
#include <stdexcept>


namespace Chess::Rendering::Elements {

void Element::Render() { renderer.Render(Texture::color, rect); };

void Element::HandleEvent(SDL_Event &event) {}


} // namespace Chess::Rendering::Elements
