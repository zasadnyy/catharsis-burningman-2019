#ifndef TMPANIMATION_H
#define TMPANIMATION_H

#include "Context.h"
#include "Animations/Animation.h"

namespace Catharsis {
    class TmpAnimation : public Animation
    {
    
    public:
        TmpAnimation();

        void setup();
        void loop(Context *context);
    };    
}


#endif /* TMPANIMATION_H */
