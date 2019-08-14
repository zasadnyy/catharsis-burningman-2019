#ifndef CONVEYLIFEANIMATION_H
#define CONVEYLIFEANIMATION_H

#include "Context.h"
#include "Animation.h"

namespace Catharsis
{

class ConveyLifeAnimation : public Animation
{
public:
    ConveyLifeAnimation();

    void loop(Context *context);
};

} // namespace Catharsis

#endif /* CONVEYLIFEANIMATION_H */



