#ifndef __TEXT_H_INCLUDED__
#define __TEXT_H_INCLUDED__

#include "UIElement.h"

#include "Graphics/Font.h"
#include <string>

/*
 *  Define text scaling behaviour :
 *  - Uniform : Keep ratio.
 *  - Free : X/Y scale independants.
 */
enum class TextScaleMode
{
    Uniform,
    Free
};

/*
 *	An UI element displaying a text.
 */
class Text : public UIElement
{
public:
    /*
     * @param fontName which font this text use
     * @param isCenterX does this text start at position or is center in X ?
     * @param color text color
     */
    Text(std::string fontName = "default", bool isCenterX = true, glm::vec3 _color = glm::vec3(1, 1, 1));

    void SetFont(std::string fontName);
    void SetContent(std::string newContent) { content = newContent; }
    void SetColor(glm::vec3 newColor) { color = newColor; }
    /*
     * Warning : if the text size is too different from the font size, we could get
     * blurry text, stretched pixels and/or artifacts as freetype rasterized at font
     * size, not text size.
     */
    void SetSize(float newScale) { size = newScale; }
    void SetIsCenterX(bool newIsCenterX) { isCenterX = newIsCenterX; }
    void SetScaleMode(TextScaleMode newMode) { scaleMode = newMode; }

    Font* GetFont() { return font; }
    const Font* GetFont() const { return font; }
    const std::string& GetContent() const { return content; }
    glm::vec3 GetColor() const { return color; }
    float GetSize() const { return size; }
    bool IsCenterX() const { return isCenterX; }
    TextScaleMode GetScaleMode() { return scaleMode; }

private:
    std::string content;
    Font* font;
    glm::vec3 color;
    float size;

    // Add a scale mode to allow an user to do non uniform scaling for text
    TextScaleMode scaleMode = TextScaleMode::Uniform;

    // Does this text start at position or is center in X ?
    bool isCenterX;
};

#endif // __TEXT_H_INCLUDED__