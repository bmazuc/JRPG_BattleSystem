#ifndef __FONT_H_INCLUDED__
#define __FONT_H_INCLUDED__

#include <glm/ext/vector_float2.hpp>
#include <glm/ext/vector_int2.hpp>
#include <map>

#include <ft2build.h>
#include FT_FREETYPE_H

/*
 *  Represents a character rasterized by Freetype.
 */
struct Glyph 
{
    unsigned int textureID;  // ID handle of the glyph texture
    glm::ivec2   size;       // Size of glyph
    glm::ivec2   bearing;    // Offset from baseline to left/top of glyph
    int advance;             // Offset to advance to next glyph
};

/*
 *  Handle a font with Freetype.
 */
class Font
{
public:
    /*
     *   Load a font and generate ASCII glyphs.
     *   @param ft handle to a FreeType library instance
     *   @param file fontFile
     *   @param _size pixel font size
     */
    void Load(FT_Library ft, const char* file, unsigned int _size);

    /*
     *  Return the glyph corresponding to the character.
     */
    Glyph GetGlyph(char c) const { return glyphs.at(c); }
    /*
     *  Return the pixel font size.
     */
    unsigned int GetSize() const { return size; }

private:
    // List of all generated ASCII glyphs.
    std::map<char, Glyph> glyphs;
    // pixel font size
    unsigned int size;
};

#endif // __FONT_H_INCLUDED__