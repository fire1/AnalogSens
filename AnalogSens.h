//
// Created by Angel Zaprianov on 17.5.2017 г..
//

#ifndef ANALOG_SENS_H
#define ANALOG_SENS_H

#include <Arduino.h>

#ifndef ANALOG_SENS_BUFFER_SIZE
#define ANALOG_SENS_BUFFER_SIZE 5
#endif


class AnalogSens {


public:

    AnalogSens(uint8_t pin);

    AnalogSens(uint8_t pin, uint8_t buffer);

    void init();

    void init(uint8_t absorption);

    void read();

    void read(uint8_t absorption);

    int mean();

protected:
    int absorption(uint8_t times);

private:
    uint8_t sensBuf;
    uint8_t sensPin;
    int sensData[ANALOG_SENS_BUFFER_SIZE];


};


#endif //ANALOGSENS_ANALOGSENS_H
