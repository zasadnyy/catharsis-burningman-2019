#ifndef ANALOGUEBUTTONSINPUT_H
#define ANALOGUEBUTTONSINPUT_H

#include "Input/InputResolver.h"

namespace Catharsis
{

#define COOLDOWN 250 //ms

class AnalogueButtonsInput
{
public:
    static InputResolver::Input readInput();

private:
    static InputResolver::Input readCurrentInput();
};

} // namespace Catharsis

#endif /* ANALOGUEBUTTONSINPUT_H */
