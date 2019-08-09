#ifndef LINENUMBERSANIMATION_H
#define LINENUMBERSANIMATION_H

#include "Context.h"
#include "Animation.h"

namespace Catharsis
{

class LineNumbersAnimation : public Animation
{
public:
    LineNumbersAnimation();

    void loop(Context *context);
};

} // namespace Catharsis

#endif /* LINENUMBERSANIMATION_H */
