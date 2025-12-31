#include "Element.h"
#include <algorithm>
#include <stdexcept>
#include <vector>

namespace Chess::Rendering::Elements {

void Element::Render() { renderer.Render(Texture::color, rect); };

void Element::HandleEvent(SDL_Event &event) {}

std::vector<Element *> Element::elements;

Element::Element() {}
Element::~Element() {}

} // namespace Chess::Rendering::Elements
