#ifndef NEW_KITT_ANIMATION
#define NEW_KITT_ANIMATION

#include "Context.h"
#include "Animations/Animation.h"

namespace Catharsis
{

class NewKittAnimation : public Animation
{
public:
    NewKittAnimation();

    void setup();
    void loop(Context *context, CRGBPalette16 curPalette);
};

} // namespace Catharsis

#endif /* NEW_KITT_ANIMATION */
