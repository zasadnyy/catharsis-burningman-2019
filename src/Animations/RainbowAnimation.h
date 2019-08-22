#ifndef RAINBOWANIMATION_H
#define RAINBOWANIMATION_H

#include "Context.h"
#include "Animation.h"

namespace Catharsis
{

class RainbowAnimation : public Animation
{
public:
    RainbowAnimation();

    void loop(Context *context, CRGBPalette16 currentPalette);
};

} // namespace Catharsis

#endif /* RAINBOWANIMATION_H */
