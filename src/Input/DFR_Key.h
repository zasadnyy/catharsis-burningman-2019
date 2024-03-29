#ifndef DFR_Key_h
#define DFR_Key_h

#include "Arduino.h"

#define SAMPLE_WAIT -1
#define NO_KEY 0
#define UP_KEY 3
#define DOWN_KEY 4
#define LEFT_KEY 2
#define RIGHT_KEY 5
#define SELECT_KEY 1

class DFR_Key
{
  public:
    DFR_Key(int);
    int getKey();
    void setRate(int);
    int _refreshRate;
  private:
    int _keyPin;
    int _threshold;
    int _curInput;
    int _curKey;
    unsigned long _oldTime;
};

#endif