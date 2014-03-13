#ifndef FONT_RENDERER_H_
#define FONT_RENDERER_H_
#include <string>

#define GLEW_STATIC
#include <GL/glew.h>
#include <engine/logger.h>
#include <SDL2/SDL_ttf.h>


/*
 * NOTE: YOU NEED TO HAVE glEnable(GL_BLEND) and
 * glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
 * Description:
 *  The font renderer class is a wrapper for font printing functionality.
 *  It is associated with one font, and it's color, and is
 *  capable of rendering any string to a texture, and binding the texture.
 *  Once RenderTexture is called, any quad drawn after will contain the text.
 *  Functions:
 *    Overloaded Constructor: Calls LoadFontFile.
 *    LoadFontFile: Takes the path to the font and the point size of the font
 *      that you with to render. Takes that and loads it into TTF_Font.
 *    RenderToSurface: Takes a string and renders it into the TTF_Font. It then
 *    binds this to an OpenGL Texture.
 *    Render: Binds the vertex array object that recorded how the texture was
 *      set up.
 */
class FontRenderer
{
  public:
    FontRenderer();
    FontRenderer(const std::string font_path, const int font_size);
    ~FontRenderer();

    bool LoadFontFile(const std::string font_path, const int font_size);

    //This renders a string to font_texture_
    void RenderToGLTexture(const std::string text,
                           const GLubyte &R, //RGB colors 0 - 255
                           const GLubyte &G,
                           const GLubyte &B);
    void RenderTexture(); //This makes the OpenGLCalls to bind the texture_

    GLuint  GetFontTexture  () const {return font_texture_;}
    int     GetWidth        () const {return width_;}
    int     GetHeight       () const {return height_;}

  private:
    TTF_Font * font_;
    GLuint font_texture_;
    int width_;
    int height_;
};

#endif
