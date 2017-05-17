#include <Arduino.h>

#include <AnalogSens.h>

AnalogSens sens(A5);

void setup() {
    sens.init();
}

void loop() {


    int mean = sens.mean();

    // Do stuff with mean data
    //
    sens.read();
}