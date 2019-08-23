#include "Arduino.h"
#include "DFR_Key.h"
#include "Config.h"

static int DEFAULT_THRESHOLD = 10;

// Real readings from the shield
// right 1-3
// up 197-199
// down 457-484
// left 712-715
// none  1023
// select ??? - looks like not working

static int UPKEY_ARV = 200; // 202
static int DOWNKEY_ARV = 466; // 466-467
static int LEFTKEY_ARV = 727; // 726-728
static int RIGHTKEY_ARV = 10; // 1-3

static int SELKEY_ARV = 900; // TODO seems not working on the shield
static int NOKEY_ARV = 1000;

DFR_Key::DFR_Key(int pin)
{
    _refreshRate = 200;
    _keyPin = pin;
    _threshold = DEFAULT_THRESHOLD;
    _curInput = NO_KEY;
    _curKey = NO_KEY;
    _oldTime = 0;
}

int DFR_Key::getKey()
{
    uint32_t now = millis();
    if (now - _oldTime > _refreshRate)
    {
        _oldTime = now;
        _curInput = analogRead(_keyPin);

        if (_curInput > NOKEY_ARV)
        {
            return NO_KEY;
        }

        if (_curInput > UPKEY_ARV - _threshold && _curInput < UPKEY_ARV + _threshold)
            _curKey = UP_KEY;
        else if (_curInput > DOWNKEY_ARV - _threshold && _curInput < DOWNKEY_ARV + _threshold)
            _curKey = DOWN_KEY;
        else if (_curInput > RIGHTKEY_ARV - _threshold && _curInput < RIGHTKEY_ARV + _threshold)
            _curKey = RIGHT_KEY;
        else if (_curInput > LEFTKEY_ARV - _threshold && _curInput < LEFTKEY_ARV + _threshold)
            _curKey = LEFT_KEY;
        else if (_curInput > SELKEY_ARV - _threshold && _curInput < SELKEY_ARV + _threshold)
            _curKey = SELECT_KEY;

        return _curKey;
    }
}

void DFR_Key::setRate(int rate)
{
    _refreshRate = rate;
}