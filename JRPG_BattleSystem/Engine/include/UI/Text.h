#ifndef __TEXT_H_INCLUDED__
#define __TEXT_H_INCLUDED__

#include "Widget.h"
#include "Rendering/IRenderable.h"
#include "Rendering/Color.h"
#include <string>

class Font;

/*
 * Defines how text scaling behaves.
 * 
 *  - Uniform : preserves aspect ratio
 *  - Free : allows independent X/Y scaling
 */
enum class TextScaleMode
{
    Uniform,
    Free
};

/**
 * Widget responsible for rendering text.
 *
 * Text is rendered using a font atlas (glyph-based rendering)
 * and supports color, scaling, and alignment options.
 */
class Text : public Widget, public IRenderable
{
public:
    Text(std::string fontName = "default", bool isCenterX = true, Color _color = Colors::White);

    void SetFont(std::string fontName);
    void SetContent(std::string newContent) { content = newContent; }
    void SetColor(Color newColor) { color = newColor; }
    
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
    Color GetColor() const { return color; }
    float GetSize() const { return size; }

    bool IsCenterX() const { return isCenterX; }
    TextScaleMode GetScaleMode() { return scaleMode; }

    void AddToRenderQueue(RenderQueue& queue) override;

private:
    std::string content;

    Font* font = nullptr;

    Color color = Colors::White;

    float size = 1.0f;

    TextScaleMode scaleMode = TextScaleMode::Uniform;

    // Does this text start at position or is center in X ?
    bool isCenterX;
};

#endif // __TEXT_H_INCLUDED__