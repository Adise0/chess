#pragma once
#include <SDL3_image/SDL_image.h>

#include <iostream>

namespace Chess::Rendering {

enum Texture { color, base, hover, pressed };


class Renderer {
public:
  SDL_Texture *baseImage = nullptr;
  SDL_Texture *hoverImage = nullptr;
  SDL_Texture *pressedImage = nullptr;
  SDL_Color color{255, 255, 255, 255};
  short sortingLayer = 0;

public:
  Renderer(SDL_Color color) : color(color) {}
  Renderer(SDL_Color color, short sortingLayer) : color(color), sortingLayer(sortingLayer) {}
  Renderer(SDL_Texture *baseImage = NULL, SDL_Texture *hoverImage = NULL,
           SDL_Texture *pressedImage = NULL)
      : baseImage(baseImage), hoverImage(hoverImage), pressedImage(pressedImage) {}
  Renderer(SDL_Texture *baseImage, SDL_Texture *hoverImage, SDL_Texture *pressedImage,
           short sortingLayer)
      : baseImage(baseImage), hoverImage(hoverImage), pressedImage(pressedImage),
        sortingLayer(sortingLayer) {}

  /// @brief Renders the requested image
  /// @param rect The rect to render to
  /// @param textureType The texture type to use
  virtual void Render(SDL_FRect rect, Texture textureType);
  virtual void Render(SDL_FRect rect) { Render(rect, Texture::color); };
};
} // namespace Chess::Rendering
