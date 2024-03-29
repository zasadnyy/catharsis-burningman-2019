#ifndef ANIMATION_H
#define ANIMATION_H

#include "Context.h"

namespace Catharsis {
    class Animation
    {
    
    public:
        Animation();

        virtual void setup();
        virtual void loop(Context *context);
    };    
}

#endif /* ANIMATION_H */
