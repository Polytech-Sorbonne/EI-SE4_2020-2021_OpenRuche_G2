// PROGRAMME VITESSE DU VENT SEUL
/*
*******************************************************************************************
Mesure de la vitesse du vent
Quand on démarre une mesure, on attend de recevoir un front montant sur D12 (port lie a l'anemometre).
L'anemometre envoie un front montant par tour.
La reception du front montant declenche un timer (interruption externe).
On attend un deuxieme front montant.
Le deuxieme front montant genere une autre interruption qui arrete le timer.
Alors, le timer contient le nombre de cycles horloge d'un tour d'anemometre. (a diviser par la frequence du lowpowertimer)
S'il n'y a pas de vent. l'anemometre ne bougera pas.
Alors on definit un autre timer (lowpowertimeout) qui forcera l'arret de la mesure si elle depasse une certaine duree.
Sachant qu'un tour par seconde correspond a 2.4km/h, un timeout de 1 s neglige toutes les vitesses inferieures a 2.4km/h.
*******************************************************************************************
*/

#include "mbed.h"

/*
 *  Objets
 */

// DEBUG USB-PUTTY
Serial pc(USBTX, USBRX);

// Anemometre sur D12
InterruptIn anemo(D12);

// Definition Timer Anemometre
LowPowerTimer t;

// Definition Timer Timeout
LowPowerTimeout timeout;


/*
 *  Variables
 */

// montre si on doit arreter ou demarrer le chrono
bool mode_lecture = false;
// sert à empecher une deuxième mesure   
bool premiere_lecture = true;
// sert a montrer si une mesure a ete effectuee
bool success_lecture = false;

bool pas_de_vent = false;

float temps = 0;
int vent_vit = 0;
/*
 *  Fonctions
 */

// Interruption (lance le timer au 1er passage par 0; l'arrete au 2eme)
void time(void)
{
    //si une lecture est en cours
    if (mode_lecture){
        // si cest la premiere lecture
        if (premiere_lecture){
            // on arrete le chrono
            t.stop();
            
            temps = t.read();
            success_lecture = true;

        }
    }else{
        // on demarre le chrono et on passe en mode lecture
        t.start();
        mode_lecture = true;
    }
}


// Fonction activée par l'interruption interne sur le Timer timeout
void inter_timeout(void)
{
    if (!success_lecture){
        // on arrrete le timer s'il a ete active
        if (mode_lecture)
        {
            t.stop();
        }

        premiere_lecture = false;
        
        pas_de_vent = true;
        
        temps = 99;
    }
}

void reset(void)
{
    mode_lecture = false;
    premiere_lecture = true;
    success_lecture = false;
}

int main()
{
    reset();
    
    // Interruption timeout apres 1 seconde
    timeout.attach(&inter_timeout, 1.0);
    
    // Interruption externe déclenche la foncion time
    anemo.rise(&time);
    

   
    while (1) {        
        if(success_lecture || pas_de_vent){
            pc.printf("ANEMO Temps = %f\r\n", temps);
            vent_vit = (int)(1200/temps);
            pc.printf("ANEMO Vitesse = %d km/h\r\n", vent_vit);
        }         
    }
}
