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
  /// @brief The color of the renderer. Default: `White`
  SDL_Color color{255, 255, 255, 255};
  /// @brief The sorting layer of the renderer. Default: `0`
  short sortingLayer = 0;

public:
  /// @brief Creates a new renderer object
  /// @param color The color to use
  Renderer(SDL_Color color) : color(color) {}
  /// @brief Creates a new renderer object
  /// @param color The color to use
  /// @param sortingLayer The sorting layer of the renderer
  Renderer(SDL_Color color, short sortingLayer) : color(color), sortingLayer(sortingLayer) {}
  /// @brief Creates a new renderer object
  /// @param baseImage The base image
  /// @param hoverImage The hovered image
  /// @param pressedImage The pressed image
  Renderer(SDL_Texture *baseImage = NULL, SDL_Texture *hoverImage = NULL,
           SDL_Texture *pressedImage = NULL)
      : baseImage(baseImage), hoverImage(hoverImage), pressedImage(pressedImage) {}
  /// @brief Creates a new renderer object
  /// @param baseImage The base image
  /// @param hoverImage The hovered image
  /// @param pressedImage The pressed image
  /// @param sortingLayer The sorting layer of the renderer
  Renderer(SDL_Texture *baseImage, SDL_Texture *hoverImage, SDL_Texture *pressedImage,
           short sortingLayer)
      : baseImage(baseImage), hoverImage(hoverImage), pressedImage(pressedImage),
        sortingLayer(sortingLayer) {}

  /// @brief Renders the element with an image
  /// @param rect The rect to render to
  /// @param textureType The texture type to use
  virtual void Render(SDL_FRect rect, Texture textureType);
  /// @brief Renders the element with a color
  /// @param rect The rect to render to
  virtual void Render(SDL_FRect rect) { Render(rect, Texture::color); };
};
} // namespace Chess::Rendering
