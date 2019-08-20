#ifndef NOISE_ANIMATION_H
#define NOISE_ANIMATION_H

#include "Context.h"
#include "Animations/Animation.h"

namespace Catharsis
{

class NoiseAnimation : public Animation
{
public:
    NoiseAnimation();

    void setup();
    void loop(Context *context, CRGBPalette16 curPalette);
};

} // namespace Catharsis

#endif /* NOISE_ANIMATION_H */
