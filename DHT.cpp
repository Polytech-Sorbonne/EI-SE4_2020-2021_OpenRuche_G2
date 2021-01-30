/*
 *  modified (10/17/20) DHT Library for  Digital-output Humidity and Temperature sensors
 *
 *  Works with DHT11, DHT22
 *             SEN11301P,  Grove - Temperature&Humidity Sensor     (Seeed Studio)
 *             SEN51035P,  Grove - Temperature&Humidity Sensor Pro (Seeed Studio)
 *             AM2302   ,  temperature-humidity sensor
 *             HM2303   ,  Digital-output humidity and temperature sensor
 *
 *  Copyright (C) Wim De Roeve
 *                based on DHT22 sensor library by HO WING KIT
 *                Arduino DHT11 library 
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documnetation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to  whom the Software is
 * furished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS OR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

#include "DHT.h"

#define DHT_DATA_BIT_COUNT 41

DHT::DHT(PinName pin,int DHTtype) {
    _pin = pin;
    _DHTtype = DHTtype;
    _firsttime=true;
}

DHT::~DHT() {
}

int DHT::readData() { // lecture donnée
    int i, j, retryCount,b;
    unsigned int bitTimes[DHT_DATA_BIT_COUNT];

    eError err = ERROR_NONE;
    time_t currentTime = time(NULL);

    DigitalInOut DHT_io(_pin);

    for (i = 0; i < DHT_DATA_BIT_COUNT; i++) {
        bitTimes[i] = 0;
    }

    if (!_firsttime) {
        if (int(currentTime - _lastReadTime) < 2) {
            err = ERROR_NO_PATIENCE;
            return err;
        }
    } else {
        _firsttime=false;
        _lastReadTime=currentTime;
    }
    retryCount = 0;

    do {
        if (retryCount > 125) {
            err = BUS_BUSY;
            return err;
        }
        retryCount ++;
        wait_us(2);
    } while ((DHT_io==0));


    DHT_io.output();
    DHT_io = 0;
    wait_us(18000);
    DHT_io = 1;
    wait_us(40);
    DHT_io.input();

    retryCount = 0;
    do {
        if (retryCount > 40)  {
            err = ERROR_NOT_PRESENT;
            return err;
        }
        retryCount++;
        wait_us(1);
    } while ((DHT_io==1));

    if (err != ERROR_NONE) {
        return err;
    }

    wait_us(80);

    for (i = 0; i < 5; i++) {
        for (j = 0; j < 8; j++) {

            retryCount = 0;
            do {
                retryCount++;
                wait_us(1);
            } while (DHT_io == 0);
            wait_us(40);
            bitTimes[i*8+j]=DHT_io;

            int count = 0;
            while (DHT_io == 1 && count < 100) {
                wait_us(1);
                count++;
            }
        }
    }
    DHT_io.output();
    DHT_io = 1;
    for (i = 0; i < 5; i++) {
        b=0;
        for (j=0; j<8; j++) {
            if (bitTimes[i*8+j+1] > 0) {
                b |= ( 1 << (7-j));
            }
        }
        DHT_data[i]=b;
    }

    if (DHT_data[4] == ((DHT_data[0] + DHT_data[1] + DHT_data[2] + DHT_data[3]) & 0xFF)) {
        _lastReadTime = currentTime;
        _lastTemperature=CalcTemperature();
        _lastHumidity=CalcHumidity();

    } 

    return err;
}


float DHT::CalcTemperature() { // calcul temp à 0.1 près
    float v;

    switch (_DHTtype) {
        case DHT11:
            v = DHT_data[2];
            return float(v);
        case DHT22:
            v = DHT_data[2] & 0x7F;
            v *= 256.0;
            v += DHT_data[3];
            v /= 10.0;
            if (DHT_data[2] & 0x80)
                v *= -1.0;
            return float(v);
    }
    return 0;
}


float DHT::CalcHumidity() { // calcul humid à 0.1 près
    float v;

    switch (_DHTtype) {
        case DHT11:
            v = DHT_data[0];
            return float(v);
        case DHT22:
            v = DHT_data[0];
            v *= 256.0;
            v += DHT_data[1];
            v /= 10.0;
            return float(v);
    }
    return 0;
}


float DHT::ReadTemperature(eScale Scale) {
    if (Scale == FARENHEIT)
        return ConvertCelciustoFarenheit(_lastTemperature);
    else if (Scale == KELVIN)
        return ConvertCelciustoKelvin(_lastTemperature);
    else
        return _lastTemperature;
}


float DHT::ReadHumidity() {
    return _lastHumidity;
}



float DHT::ConvertCelciustoFarenheit(float celsius) {
    return celsius * 9 / 5 + 32;
}


float DHT::ConvertCelciustoKelvin(float celsius) {
    return celsius + 273.15;
}
