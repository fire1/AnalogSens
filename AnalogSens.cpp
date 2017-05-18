//
// Created by Angel Zaprianov on 17.5.2017 г..
//

#include "AnalogSens.h"
#include <Arduino.h>

/**
 * Construct with default buffer
 */
AnalogSens::AnalogSens(uint8_t pin) {
    this->sensPin = pin;
    this->sensBuf = ANALOG_SENS_BUFFER_SIZE;
}
/**
 * Construct with custom buffer
 */
AnalogSens::AnalogSens(uint8_t pin, uint8_t buffer) {
    this->sensPin = pin;
    this->sensBuf = buffer;
}


/**
 * First read
 */
void AnalogSens::init(void) {
    int n = 0;
    while (n < this->sensBuf) {
        this->sensData[n] = analogRead(this->sensPin);
        n++;
    }
}

/**
 * Aggressive initialization
 */
void AnalogSens::init(uint8_t absorption) {
    int n = 0;
    while (n < this->sensBuf) {
        this->sensData[n] = this->absorption(absorption);
        n++;
    }
}


/**
 * Single read of sensor
 */
void AnalogSens::read(void) {
    // Read new sensor reading, append to buffer and delete oldest reading
    for (int n = (this->sensBuf - 1); n > 0; n--) {
        this->sensData[n] = this->sensData[n - 1];
    }
    this->sensData[0] = analogRead(this->sensPin);
}

/**
 * Multiple read of sensor and gets average value
 */
void AnalogSens::read(uint8_t absorption) {
    // Read new sensor reading, append to buffer and delete oldest reading
    for (int n = (this->sensBuf - 1); n > 0; n--) {
        this->sensData[n] = this->sensData[n - 1];
    }

    this->sensData[0] = this->absorption(absorption);
}

/**
 * Absorption of sensor
 */
int AnalogSens::absorption(uint8_t times) {
    long int tempRead;
    for (int i = 0; i < times; ++i) {
        tempRead += analogRead(this->sensPin);
    }
    return tempRead / times;
}

/**
 *   Returns (Corrected) Mean
 */
int AnalogSens::mean() {
    // Calculate Raw Mean & SD
    float datasum = 0;
    float diffsum = 0;
    for (int n = 0; n < this->sensBuf; n++) {
        datasum += this->sensData[n];
    }
    int mean = float(datasum / this->sensBuf);
    for (int n = 0; n < this->sensBuf; n++) {
        diffsum += ((this->sensData[n] - mean) * (this->sensData[n] - mean));
    }
    int sd = sqrt(diffsum / (this->sensBuf - 1));

    // Recalculate Corrected Mean only using data within range +/- 1SD of Raw Mean
    if (sd != 0) {      // Avoid divide by zero error if sd = 0
        float newSum = 0; // Sum of readings within acceptable range
        float newLen = 0; // Number of readings within acceptable range
        int n = 0;
        while (n < this->sensBuf) {
            if ((this->sensData[n] < (mean + sd)) and (this->sensData[n] > (mean - sd))) {
                newSum += this->sensData[n];
                newLen++;
            }
            n++;
        }
        mean = newSum / newLen; // Corrected Mean
        return mean;
    }
};
