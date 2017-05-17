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

    void init();

    void read();

    int mean();


private:
    uint8_t sensPin;
    int sensData[ANALOG_SENS_BUFFER_SIZE];




};


#endif //ANALOGSENS_ANALOGSENS_H
