#ifndef FIRE2012WITHPALETTESANIMATION_H
#define FIRE2012WITHPALETTESANIMATION_H

#include "Context.h"
#include "Animations/Animation.h"

namespace Catharsis
{

class Fire2012WithPalettesAnimation : public Animation
{
public:
    Fire2012WithPalettesAnimation();

    void setup();
    void loop(Context *context, CRGBPalette16 curPalette);
    void Fire2012WithPalette(Context *context, CRGBPalette16 curPalette);
};

} // namespace Catharsis

#endif /* FIRE2012WITHPALETTESANIMATION_H */
