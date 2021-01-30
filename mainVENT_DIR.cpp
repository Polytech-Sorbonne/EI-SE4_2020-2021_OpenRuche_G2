#include "mbed.h"

// PROGRAMME DIRECTION VENT SEUL - affichage port serie
    // valeurs mesurees "a la main" avec notre capteur, a remesurer si imprecisions detectees

/*
 *  Objets
 */

// USB Serial Terminal (sortie)
Serial pc(USBTX, USBRX);

// Girouette (entree)
AnalogIn gir(A0);

/*
 * Variables
 */

float val;


/*
 *  Fonctions
 */

void girouette(void){

    // lecture de la valeur de la girouette
    val = gir.read();
        
    if      (val < 0.74){
       //NW
       pc.printf("Direction = NW\r\n");
    else if (val < 0.78){
       //SW
       pc.printf("Direction = SW\r\n");
    else if (val < 0.80){
       //NE
       pc.printf("Direction = NE\r\n");
    else if (val < 0.83){
       //W
       pc.printf("Direction = W\r\n");
    else if (val < 0.85){
       //SE
       pc.printf("Direction = SE\r\n");
    else if (val < 0.90){
       //N
       pc.printf("Direction = N\r\n");
    else if (val < 0.91){
       //E
       pc.printf("Direction = E\r\n");
    else{
       //S
       pc.printf("Direction = S\r\n");
    }
}

int main()
{
    girouette();
}
