#ifndef BEAT_WAVE_ANIMATION_H
#define BEAT_WAVE_ANIMATION_H

#include "Context.h"
#include "Animations/Animation.h"

namespace Catharsis
{

class BeatWaveAnimation : public Animation
{
public:
    BeatWaveAnimation();

    void setup();
    void loop(Context *context, CRGBPalette16 curPalette);
};

} // namespace Catharsis

#endif /* BEAT_WAVE_ANIMATION_H */
