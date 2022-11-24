#include "Sprite.h"
#include "System.h"
#include "Constants.h"
#include <SDL_image.h>

namespace fruitwork
{
    Sprite::Sprite(int x, int y, int w, int h, const std::string &texturePath) : Component(x, y, w, h)
    {
        SDL_Surface *surface = IMG_Load(texturePath.c_str());

        if (surface == nullptr)
            SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Failed to load image: %s", texturePath.c_str());

        spriteTexture = SDL_CreateTextureFromSurface(sys.get_renderer(), surface);
        SDL_FreeSurface(surface);
    }


    Sprite::Sprite(int x, int y, int w, int h) : Component(x, y, w, h), spriteTexture(nullptr) {}

    Sprite *Sprite::getInstance(int x, int y, int w, int h, const std::string &texturePath)
    {
        return new Sprite(x, y, w, h, texturePath);
    }

    Sprite *Sprite::getInstance(int x, int y, int w, int h, SDL_Texture *texture)
    {
        auto *sprite = new Sprite(x, y, w, h);
        sprite->spriteTexture = texture;
        sprite->isTextureOwner = false;
        return sprite;
    }

    void Sprite::draw() const
    {
        if (spriteTexture == nullptr)
            return;

        SDL_SetTextureColorMod(spriteTexture, colorMod.r, colorMod.g, colorMod.b);
        SDL_Rect rect = get_rect();
        SDL_RenderCopyEx(sys.get_renderer(), spriteTexture, nullptr, &rect, 0, nullptr, flipType);
    }

    Sprite::~Sprite()
    {
        if (isTextureOwner)
            SDL_DestroyTexture(spriteTexture);
    }

} // fruitwork