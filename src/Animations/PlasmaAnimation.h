#ifndef PLASMAANIMATION_H
#define PLASMAANIMATION_H

#include "Context.h"
#include "Animations/Animation.h"

namespace Catharsis
{

class PlasmaAnimation : public Animation
{
public:
    PlasmaAnimation();

    void setup();
    void loop(Context *context);
};

} // namespace Catharsis

#endif /* PLASMAANIMATION_H */
