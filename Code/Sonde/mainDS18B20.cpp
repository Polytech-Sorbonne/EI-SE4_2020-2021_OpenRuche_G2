#include "mbed.h"
#include "DS1820.h"
	// librairie MBED : https://os.mbed.com/users/hudakz/code/DS1820/

// PROGRAMME SONDE DS18B20 SEULE - affichage sur le port serie

DS1820  ds1820(D9); 
Serial pc(USBTX,USBRX);
 
float sonde_f = 0;

int main() 
{

	while(1) {
		//------DS18B20------//
		if(ds1820.begin()) {
			ds1820.startConversion();    
			ThisThread::sleep_for(1000);  
			sonde_f = ds1820.read();
			
			pc.printf("DS18B20 Temperature = %f\r\n", sonde_f);
		}
		else pc.printf("DS18B20 not found\r\n");
	}
}
