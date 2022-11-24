#include "ResponsiveSprite.h"
#include "System.h"

namespace fruitwork
{
    ResponsiveSprite *ResponsiveSprite::getInstance(int x, int y, int w, int h, const std::string &texturePath, Alignment alignment)
    {
        return new ResponsiveSprite(x, y, w, h, texturePath, alignment);
    }

    ResponsiveSprite *ResponsiveSprite::getInstance(int x, int y, int w, int h, SDL_Texture *texture, Alignment alignment)
    {
        return new ResponsiveSprite(x, y, w, h, texture, alignment);
    }

    ResponsiveSprite::ResponsiveSprite(int x, int y, int w, int h, const std::string &texturePath, Alignment alignment)
            : Sprite(x, y, w, h, texturePath), alignment(alignment) {}

    ResponsiveSprite::ResponsiveSprite(int x, int y, int w, int h, SDL_Texture *texture, Alignment alignment)
            : Sprite(x, y, w, h), alignment(alignment)
    {
        spriteTexture = texture;
        isTextureOwner = false;
    }

    void ResponsiveSprite::start()
    {
        SDL_Rect r = get_rect();

        // the sprites needs to be downscaled to fit within their rect r, while keeping their aspect ratio
        int w, h;
        SDL_QueryTexture(spriteTexture, nullptr, nullptr, &w, &h);

        // calculate the scale factor
        double scale = std::min((double) r.w / w, (double) r.h / h);

        // calculate the new width and height
        r.w = (int) (w * scale);
        r.h = (int) (h * scale);

        switch (alignment)
        {
            case Alignment::TOP_LEFT:
                break;
            case Alignment::TOP_CENTER: // move right by half the difference
                r.x += (get_rect().w - r.w) / 2;
                break;
            case Alignment::TOP_RIGHT: // move right by the difference
                r.x += get_rect().w - r.w;
                break;
            case Alignment::CENTER_LEFT: // move down by half the difference
                r.y += (get_rect().h - r.h) / 2;
                break;
            case Alignment::CENTER: // move right by half the difference, then down by half the difference
                r.x += (get_rect().w - r.w) / 2;
                r.y += (get_rect().h - r.h) / 2;
                break;
            case Alignment::CENTER_RIGHT:
                r.x += get_rect().w - r.w;
                r.y += (get_rect().h - r.h) / 2;
                break;
            case Alignment::BOTTOM_LEFT:
                r.y += get_rect().h - r.h;
                break;
            case Alignment::BOTTOM_CENTER:
                r.x += (get_rect().w - r.w) / 2;
                r.y += get_rect().h - r.h;
                break;
            case Alignment::BOTTOM_RIGHT:
                r.x += get_rect().w - r.w;
                r.y += get_rect().h - r.h;
                break;
        }

        set_rect(r);
    }
} // fruitwork