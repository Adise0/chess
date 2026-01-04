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
  /// @param rect The rect to render to
  /// @param textureType The texture type to use
  virtual void Render(SDL_FRect rect, Texture textureType);
  virtual void Render(SDL_FRect rect) { Render(rect, Texture::color); };
};
} // namespace Chess::Rendering
