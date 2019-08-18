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
    void loop(Context *context);
    void ChangePalettePeriodically();
    void FillLEDsFromPaletteColors(uint8_t colorIndex, Context *context);
};

} // namespace Catharsis

#endif /* PALLETCROSSFADEANIMATION_H */
