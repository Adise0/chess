#include "Element.h"
#include <algorithm>


namespace Chess::Rendering::Elements {

std::vector<Element *> Element::elements;

void Element::RegisterElement(Element *element) {
  // #region RegisterElement
  elements.push_back(element);
  // #endregion
}
void Element::UnregisterElement(Element *element) {

  auto foundElementIterator = std::find(elements.begin(), elements.end(), element);

  if (foundElementIterator != elements.end()) {
    elements.erase(foundElementIterator);
  }
}

void Element::Render() {};


Element::Element() { RegisterElement(this); }
Element::~Element() { UnregisterElement(this); }



} // namespace Chess::Rendering::Elements
