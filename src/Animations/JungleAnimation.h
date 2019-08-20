#ifndef JUNGLE_ANIMATION_H
#define JUNGLE_ANIMATION_H

#include "Context.h"
#include "Animations/Animation.h"

namespace Catharsis
{

class JungleAnimation : public Animation
{
public:
    JungleAnimation();

    void setup();
    void loop(Context *context, CRGBPalette16 curPalette);
};

} // namespace Catharsis

#endif /* JUNGLE_ANIMATION_H */
