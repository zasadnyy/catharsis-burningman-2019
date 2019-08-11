#ifndef SCREEN_H
#define SCREEN_H

#include "Context.h"

namespace Catharsis
{
class Screen
{
public:
    static void setup();
    static void updateScreen(Context *context);
};
} // namespace Catharsis

#endif /* SCREEN_H */
