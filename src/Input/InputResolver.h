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
        
        ANIMATION_NEXT,
        ANIMATION_PREVIOUS,

        BRIGHTNESS_UP,
        BRIGHTNESS_DOWN,

        FRAMERATE_UP,
        FRAMERATE_DOWN
    };
    
    static void updateContext(Input input, Context *context);
};
} // namespace Catharsis

#endif /* INPUTRESOLVER_H */
