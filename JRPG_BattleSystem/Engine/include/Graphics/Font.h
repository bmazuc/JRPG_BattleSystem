#ifndef __FONT_H_INCLUDED__
#define __FONT_H_INCLUDED__

#include <glm/ext/vector_float2.hpp>
#include <glm/ext/vector_int2.hpp>
#include <map>

#include <ft2build.h>
#include FT_FREETYPE_H

struct Glyph 
{
    unsigned int textureID;  // ID handle of the glyph texture
    glm::ivec2   size;       // Size of glyph
    glm::ivec2   bearing;    // Offset from baseline to left/top of glyph
    int advance;             // Offset to advance to next glyph
};

class Font
{
public:
    // size = pixel font size
    void Load(FT_Library ft, const char* file, unsigned int _size);

    Glyph GetGlyph(char c) const { return glyphs.at(c); }
    unsigned int GetSize() const { return size; }

private:
    std::map<char, Glyph> glyphs;

    unsigned int size;
};

#endif // __FONT_H_INCLUDED__