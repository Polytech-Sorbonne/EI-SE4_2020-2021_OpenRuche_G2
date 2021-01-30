#include "mbed.h"
#include "DHT.h"
	// librairie MBED : https://os.mbed.com/users/Wimpie/code/DHT/
		//AMELIORATION: modifier DHT.cpp pour eviter les flottants dans humidite

// PROGRAMME DHT SEUL - affichage sur le port serie
 
DHT dht_sensor(D6, DHT22); // ou autre
Serial pc(USBTX, USBRX); 

float dht_t_f = 0; //temperature
uint8_t dht_h = 0; //humidite
int dhterror = 0;


int main()
{
 
    while(1) {
 
        //-------DHT--------//
        dhterror = dht_sensor.readData();
        if (!dhterror){
            dht_t_f = dht_sensor.ReadTemperature(CELCIUS);
            dht_h = (uint8_t)dht_sensor.ReadHumidity();
            pc.printf("DHT22 temperature = %f degC\r\n", dht_t_f);
            pc.printf("DHT22 humidite    = %d \%\r\n", dht_h);
        }
        else pc.printf("Error DHT: %d\r\n", dhterror);

        
    }
}
 
