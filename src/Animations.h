#ifndef ANIMATIONS_H
#define ANIMATIONS_H

#include "Animations/RainbowAnimation.h"
#include "Animations/LineNumbersAnimation.h"
#include "Animations/FireAnimation.h"
#include "Animations/PlasmaAnimation.h"
#include "Animations/TmpAnimation.h"
#include "Animations/PalletCrossfadeAnimation.h"
#include "Animations/Fire2012WithPalettesAnimation.h"
#include "Animations/BeatWaveAnimation.h"
#include "Animations/FadePulseGlowAnimation.h"
#include "Animations/NewKittAnimation.h"
#include "Animations/JungleAnimation.h"
#include "Animations/MatrixAnimation.h"
#include "Animations/NoiseAnimation.h"

namespace Catharsis
{
Animation* animations[] = {
    // new Animation(),
    // new TmpAnimation(),

    new NewKittAnimation(), // good but too fast 3
    new FadePulseGlowAnimation(), // 5
    new BeatWaveAnimation(), // 4
    new NoiseAnimation(), // 5
    new JungleAnimation(), // Sparkles? 5
    new MatrixAnimation(), // only one line?? // 3
    new PlasmaAnimation(), // 5
    new PalletCrossfadeAnimation(), // 5
    new RainbowAnimation(), // 5

    // new LineNumbersAnimation(),
};
}

#endif