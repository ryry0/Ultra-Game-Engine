#include <string>

#include <SDL2/SDL_ttf.h>
#define GLEW_STATIC
#include <GL/glew.h>

#include <engine/font_renderer.h>
#include <engine/logger.h>

FontRenderer::FontRenderer()
{
  glGenTextures(1, &font_texture_);
}

/*
 * This constructor overload loads the font into memory;
 */
FontRenderer::FontRenderer(std::string font_path, const int font_size)
{
  glGenTextures(1, &font_texture_);
  LoadFontFile(font_path, font_size);
}

/*
 * The destructor makes sure to remove the font and the textures
 */
FontRenderer::~FontRenderer()
{
  glDeleteTextures(1, &font_texture_);
  TTF_CloseFont(font_);
}

/*
 * Loads the font from font_path, and sets the point size to render at.
 */
bool FontRenderer::LoadFontFile(const std::string font_path,
                                const int font_size)
{
  font_ = TTF_OpenFont(font_path.c_str(), font_size);
  if(font_ == NULL)
  {
    LOG(LOG_ERROR) << "Failed to load font: " << font_path;
    return false;
  }
  return true;
}

/*
 * Loads the font into a SDL_Surface, and it is then bound to an OpenGL texture.
 */
void FontRenderer::RenderToGLTexture(const std::string text,
                     const GLubyte &R, const GLubyte &G, const GLubyte &B)
{
  SDL_Color color = {R, G, B};
  SDL_Surface *font_surface;
  font_surface = TTF_RenderText_Blended(const_cast<TTF_Font*>(font_),
      text.c_str(), color);

  width_ = font_surface->w;
  height_ = font_surface->h;

  glBindTexture(GL_TEXTURE_2D, font_texture_);
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, font_surface->w, font_surface->h,
      0, GL_BGRA, GL_UNSIGNED_BYTE, font_surface->pixels);
  glBindTexture(GL_TEXTURE_2D, 0);

  SDL_FreeSurface(font_surface);
}

/*
 * Calls the texture to be bound. Any quad drawn after this will be drawn
 * with this texture.
 */
void FontRenderer::RenderTexture()
{
    glBindTexture(GL_TEXTURE_2D, font_texture_);
}
