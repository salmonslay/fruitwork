#ifndef FRUITWORK_RESPONSIVE_SPRITE_H
#define FRUITWORK_RESPONSIVE_SPRITE_H

#include "Sprite.h"

namespace fruitwork
{

    /**
     * A Sprite that will be resized to fit within its container, without stretching.
     */
    class ResponsiveSprite : public Sprite {
    public:
        enum class Alignment {
            TOP_LEFT,
            TOP_CENTER,
            TOP_RIGHT,
            CENTER_LEFT,
            CENTER,
            CENTER_RIGHT,
            BOTTOM_LEFT,
            BOTTOM_CENTER,
            BOTTOM_RIGHT
        };

        static ResponsiveSprite *getInstance(int x, int y, int w, int h, const std::string &texturePath, Alignment alignment = Alignment::CENTER);

        static ResponsiveSprite *getInstance(int x, int y, int w, int h, SDL_Texture *texture, Alignment alignment = Alignment::CENTER);

        void start() override;

        void setTexture(const std::string &texturePath) override;

        void setTexture(SDL_Texture *texture) override;

    protected:
        ResponsiveSprite(int x, int y, int w, int h, const std::string &texturePath, Alignment alignment = Alignment::CENTER);

        ResponsiveSprite(int x, int y, int w, int h, SDL_Texture *texture, Alignment alignment = Alignment::CENTER);

    private:
        Alignment alignment;
        SDL_Rect originalRect;

        void updateRect();
    };

} // fruitwork

#endif //FRUITWORK_RESPONSIVE_SPRITE_H
