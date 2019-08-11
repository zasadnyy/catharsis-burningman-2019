#ifndef INPUTRESOLVER_H
#define INPUTRESOLVER_H

#include "Context.h"

namespace Catharsis
{

#define BRIGHTNESS_STEP 10
#define FPS_STEP 1

class InputResolver
{
public:
    enum Input
    {
        NONE,

        BUTTON_UP,
        BUTTON_DOWN,
        BUTTON_LEFT,
        BUTTON_RIGHT
    };

    static void updateContext(Input input, Context *context);

private:
    static void changeMenuValue(Context *context, int8_t increment);
};
} // namespace Catharsis

#endif /* INPUTRESOLVER_H */
