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
    // new BeatWaveAnimation(),
    // new NewKittAnimation(),
    new FadePulseGlowAnimation(),
    // new NoiseAnimation(),
    new JungleAnimation(),
    // new MatrixAnimation(),
    // new PlasmaAnimation(),
    // new Fire2012WithPalettesAnimation(),
    new PalletCrossfadeAnimation(),
    // new RainbowAnimation(),
    // new LineNumbersAnimation(),
    // new FireAnimation()
};
}

#endif