#pragma once
#include <SDL3_image/SDL_image.h>

#include <iostream>

namespace Chess::Rendering {

enum Texture { color, base, hover, pressed };


class Renderer {
public:
  /// @brief The base texture of an image
  SDL_Texture *baseImage = nullptr;
  /// @brief The hovered texture of an image
  SDL_Texture *hoverImage = nullptr;
  /// @brief The pressed texture of an image
  SDL_Texture *pressedImage = nullptr;
  /// @brief White
  SDL_Color color{255, 255, 255, 255};
  short sortingLayer = 0;

public:
  /// @brief Renderer function that only takes a color
  /// @param color It's a color
  Renderer(SDL_Color color) : color(color) {}
  /// @brief Renderer function that takes a color and a sorting layer (to print elements correctly)
  /// @param color It' s a color
  /// @param sortingLayer The sorting layer needed to correctly print elements
  Renderer(SDL_Color color, short sortingLayer) : color(color), sortingLayer(sortingLayer) {}
  /// @brief Renderer function for a button
  /// @param baseImage The base image
  /// @param hoverImage The hovered image
  /// @param pressedImage The pressed image
  Renderer(SDL_Texture *baseImage = NULL, SDL_Texture *hoverImage = NULL,
           SDL_Texture *pressedImage = NULL)
      : baseImage(baseImage), hoverImage(hoverImage), pressedImage(pressedImage) {}
  /// @brief The renderer function for the chess pieces
  /// @param baseImage The base image
  /// @param hoverImage The hovered image
  /// @param pressedImage The pressed image
  /// @param sortingLayer The sorting layer
  Renderer(SDL_Texture *baseImage, SDL_Texture *hoverImage, SDL_Texture *pressedImage,
           short sortingLayer)
      : baseImage(baseImage), hoverImage(hoverImage), pressedImage(pressedImage),
        sortingLayer(sortingLayer) {}

  /// @brief Renders the requested image
  /// @param rect The rect to render to
  /// @param textureType The texture type to use
  virtual void Render(SDL_FRect rect, Texture textureType);
  /// @brief The render function for a rectangle
  /// @param rect The rect to render to
  virtual void Render(SDL_FRect rect) { Render(rect, Texture::color); };
};
} // namespace Chess::Rendering
