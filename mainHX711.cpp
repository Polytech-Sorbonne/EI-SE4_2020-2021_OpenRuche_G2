#include "mbed.h"
#include "HX711.h"
    // librairie MBED : https://os.mbed.com/teams/Cr300-Litho/code/HX711/

// Capteur Poids
HX711 scale(D3, D4); //DATA,CLK
// USB Serial Terminal
Serial pc(USBTX, USBRX);

// Facteur de calibration
float calibration_factor = 11000;

// PROGRAMME POIDS SEUL - code a utiliser une fois le calibrage effectue
    // Si imprécision de mesure, decommentez le code de calibrage ("PROGRAMME CALIBRAGE POIDS")
    // et suivez les instructions affichees sur le terminal en utilisant une masse connue
    // (de preference pas trop petite si votre capteur peut mesurer de grandes valeurs)

float weight_kg = 0;    // poids en kg
uint8_t first_time = 1; // flag de passage en mode power-down

int main() {

    while(1) {
        if(!first_time) scale.powerUp();

        // acquisition de la mesure (KG)
        weight_kg = scale.getGram();
        pc.printf("HX711 Poids = %f kg\r\n",weight_kg);

        // passage en mode power-down
        scale.powerDown();
        first_time = 0;
    }
}

/*
// PROGRAMME CALIBRAGE POIDS - calibrage
    // Ajustez le "calibration_factor" jusqu'a arriver a la valeur de la masse connue
    // puis conservez precieusement cette valeur et initialisez directement la bonne valeur
int averageSamples = 100;
int main(void)
{
    pc.printf("Starting Scale");
    pc.printf("HX711 calibration sketch");
    pc.printf("Remove all weight from scale");
    pc.printf("After readings begin, place known weight on scale");
    pc.printf("Press + or a to increase calibration factor");      
    pc.printf("Press - or z to decrease calibration factor");      
    
     
    scale.setScale(0);
    scale.tare(); //Reset the scale to 0
    
    long zero_factor = scale.averageValue(averageSamples); //Get a baseline reading
    pc.printf("Zero factor: %.4f\n" , zero_factor); //This can be used to remove the need to tare the scale. Useful in permanent scale projects.
    while (true) {
    	// Calibration
        scale.setScale(calibration_factor);
        // acquisition de la mesure
        float weight = scale.getGram();
        // envoi de la mesure
        pc.printf("Reading: %f\r\n", weight);
        
        pc.printf(" calibration_factor: %.2f\r\n", calibration_factor);
       if(pc.readable()) {
            char temp = pc.getc();
            if(temp == '+' || temp == 'a')
               calibration_factor += 10;
            else if(temp == '-' || temp == 'z')
                calibration_factor -= 10;
            }
        wait(0.5f);
    }
}
*/
