#include "Arduino.h"
#include "DFR_Key.h"
#include "Config.h"

static int DEFAULT_THRESHOLD = 5;

// Real readings from the shield
// right 0
// up 202
// down 467
// left 729
// none  1023
// select ??? - looks like not working

static int UPKEY_ARV = 202; //that's read "analogue read value"
static int DOWNKEY_ARV = 467;
static int LEFTKEY_ARV = 729;
static int RIGHTKEY_ARV = 0;
static int SELKEY_ARV = 900; // TODO fix
static int NOKEY_ARV = 1023;

DFR_Key::DFR_Key(int pin)
{
    _refreshRate = 10;
    _keyPin = pin;
    _threshold = DEFAULT_THRESHOLD;
    _keyIn = NO_KEY;
    _curInput = NO_KEY;
    _curKey = NO_KEY;
    _prevInput = NO_KEY;
    _prevKey = NO_KEY;
    _oldTime = 0;
}

int DFR_Key::getKey()
{
    if (millis() > _oldTime + _refreshRate)
    {
        _prevInput = _curInput;
        _curInput = analogRead(_keyPin);

        if (_curInput == _prevInput)
        {
            _change = false;
            _curKey = _prevKey;
        }
        else
        {
            _change = true;
            _prevKey = _curKey;

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
            else
                _curKey = NO_KEY;
        }

        if (_change)
        {
            _oldTime = millis();
            return _curKey;
        }
        else
        {
            return SAMPLE_WAIT;
        }
    }
}

void DFR_Key::setRate(int rate)
{
    _refreshRate = rate;
}