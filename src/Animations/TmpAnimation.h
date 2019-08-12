#ifndef TMPANIMATION_H
#define TMPANIMATION_H

#include "Context.h"
#include "Animations/Animation.h"

namespace Catharsis
{
class TmpAnimation : public Animation
{

public:
    TmpAnimation();

    virtual void setup();
    virtual void loop(Context *context);
};
} // namespace Catharsis

#endif /* TMPANIMATION_H */
