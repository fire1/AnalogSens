//
// Created by Angel Zaprianov on 17.5.2017 г..
//

#include "AnalogSens.h"


/**
 *
 */
AnalogSens::AnalogSens(uint8_t pin) {
    this->sensPin = pin;
}


/**
 * First read
 */
void AnalogSens::init(void) {
    int n = 0;
    while (n < ANALOG_SENS_BUFFER_SIZE) {
        this->sensData[n] = analogRead(this->sensPin);
        n++;
    }
}

/**
 * Ordinary read
 */
void AnalogSens::read(void) {
    // Read new sensor reading, append to buffer and delete oldest reading
    for (int n = (ANALOG_SENS_BUFFER_SIZE - 1); n > 0; n--) {
        this->sensData[n] =  this->sensData[n - 1];
    }
    this->sensData[0] = analogRead(this->sensPin);
}
/**
 *   Returns (Corrected) Mean
 */
int AnalogSens::mean(){
    // Calculate Raw Mean & SD
    float datasum = 0;
    float diffsum = 0;
    for (int n = 0; n < ANALOG_SENS_BUFFER_SIZE; n++) {
        datasum += this->sensData[n];
    }
    int mean = float(datasum / ANALOG_SENS_BUFFER_SIZE);
    for (int n = 0; n < ANALOG_SENS_BUFFER_SIZE; n++) {
        diffsum += ((this->sensData[n] - mean) * (this->sensData[n] - mean));
    }
    int sd = sqrt(diffsum / (ANALOG_SENS_BUFFER_SIZE - 1));

    // Recalculate Corrected Mean only using data within range +/- 1SD of Raw Mean
    if (sd != 0) {      // Avoid divide by zero error if sd = 0
        float newSum = 0; // Sum of readings within acceptable range
        float newLen = 0; // Number of readings within acceptable range
        int n = 0;
        while (n < ANALOG_SENS_BUFFER_SIZE) {
            if ((this->sensData[n] < (mean + sd)) and (this->sensData[n] > (mean - sd))) {
                newSum += this->sensData[n];
                newLen ++;
            }
            n++;
        }
        mean = newSum / newLen; // Corrected Mean
        return mean;
    }
};
