#ifndef PALLETCROSSFADEANIMATION_H
#define PALLETCROSSFADEANIMATION_H

#include "Context.h"
#include "Animations/Animation.h"

namespace Catharsis
{

class PalletCrossfadeAnimation : public Animation
{
public:
    PalletCrossfadeAnimation();

    void setup();
    // void loop(Context *context);
    void loop(Context *context, CRGBPalette16 curPalette);
    void FillLEDsFromPaletteColors(uint8_t colorIndex, Context *context, CRGBPalette16 curPalette);
};

} // namespace Catharsis

#endif /* PALLETCROSSFADEANIMATION_H */
