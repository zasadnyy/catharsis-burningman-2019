#ifndef FIREANIMATION_H
#define FIREANIMATION_H

#include "Context.h"
#include "Animation.h"

namespace Catharsis
{

class FireAnimation : public Animation
{
public:
    FireAnimation();

    void loop(Context *context);
};

} // namespace Catharsis

#endif /* FIREANIMATION_H */
