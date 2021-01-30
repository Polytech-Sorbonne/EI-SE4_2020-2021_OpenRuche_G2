#include "mbed.h"
Serial pc(USBTX, USBRX);
AnalogIn a(A0);

int main(){
    float val;
    while(1){
        val = a.read(); //Lecture de la valeur
        pc.printf("%f\r\n", val*3.3);
    }
}
