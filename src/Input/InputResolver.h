#ifndef INPUTRESOLVER_H
#define INPUTRESOLVER_H

#include "Context.h"

namespace Catharsis
{

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
