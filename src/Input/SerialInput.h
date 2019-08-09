#ifndef SERIALINPUT_H
#define SERIALINPUT_H

#include "Input/InputResolver.h"

namespace Catharsis
{

class SerialInput
{
public:
    static void setup();
    static InputResolver::Input readInput();

private:
    static InputResolver::Input parseChar(char c);
};

} // namespace Catharsis
#endif /* SERIALINPUT_H */
