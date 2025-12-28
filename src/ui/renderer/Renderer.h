#pragma once
#include <SDL3_image/SDL_image.h>

namespace Chess::Rendering {

enum Texture { color, base, hover, pressed };


class Renderer {
public:
  SDL_Texture *baseImage;
  SDL_Texture *hoverImage;
  SDL_Texture *pressedImage;
  SDL_Color *color;

public:
  Renderer(SDL_Color *color = NULL, SDL_Texture *baseImage = NULL, SDL_Texture *hoverImage = NULL,
           SDL_Texture *pressedImage = NULL)
      : color(color), baseImage(baseImage), hoverImage(hoverImage), pressedImage(pressedImage) {}


  /// @brief Renders the requested image
  /// @param textureType The texture type to use
  /// @param rect The rect to render to
  virtual void Render(Texture textureType, SDL_FRect rect);
};
} // namespace Chess::Rendering
