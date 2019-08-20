#ifndef FADE_PULSE_GLOW_ANIMATION_H
#define FADE_PULSE_GLOW_ANIMATION_H

#include "Context.h"
#include "Animations/Animation.h"

namespace Catharsis
{

class FadePulseGlowAnimation : public Animation
{
public:
    FadePulseGlowAnimation();

    void setup();
    void loop(Context *context, CRGBPalette16 curPalette);
};

} // namespace Catharsis

#endif /* FADE_PULSE_GLOW_ANIMATION_H */
