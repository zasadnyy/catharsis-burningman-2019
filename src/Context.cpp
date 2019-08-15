#include "Context.h"

namespace Catharsis {

Context::Context(u_int8_t animationsCount, CRGBPalette16 *palettes[]) {
    // _animations = animations;
    _palettes = palettes;
    _animationsCount = animationsCount;

    fps = DEFAULT_FPS;
    brightness = MAX_BRIGHTNESS / 2;
    currentAnimation = 0;
    currentPalette = 0;
    
    currentMenu = MENU_NONE;
    menusCount = 4;
}

    // Animation Context::getCurrentAnimation() {
    //     return _animations[currentAnimation];
    // }

    CRGBPalette16 Context::getCurrentPalette() {
        return _palettes[currentPalette];
    }

    u_int8_t Context::getAnimationsCount() {
        return _animationsCount;
    }

}