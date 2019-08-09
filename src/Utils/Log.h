#ifndef LOG_H
#define LOG_H

#include <Arduino.h>

namespace Catharsis {

void log(String message) {
    Serial.println(message);
}

}

#endif /* LOG_H */
