#ifndef ANALOGUEBUTTONSINPUT_H
#define ANALOGUEBUTTONSINPUT_H

#include "Input/InputResolver.h"

namespace Catharsis
{

#define COOLDOWN 200 //ms

class AnalogueButtonsInput
{
public:
    static void setup();
    static InputResolver::Input readInput();
};

} // namespace Catharsis

#endif /* ANALOGUEBUTTONSINPUT_H */
