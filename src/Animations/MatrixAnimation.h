#ifndef MATRIX_ANIMATION_H
#define MATRIX_ANIMATION_H

#include "Context.h"
#include "Animations/Animation.h"

namespace Catharsis
{

class MatrixAnimation : public Animation
{
public:
    MatrixAnimation();

    void setup();
    void loop(Context *context, CRGBPalette16 curPalette);
};

} // namespace Catharsis

#endif /* MATRIX_ANIMATION_H */
