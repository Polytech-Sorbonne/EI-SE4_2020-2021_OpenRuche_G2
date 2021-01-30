#include "mbed.h"
#include "fft.h"

// PROGRAMME FFT SEULE

// Nombre d'echantillons
int N = 1024;

/*
 * Fmax = 2000Hz
 * Theoreme de Shanon => Fe > 2 x Fmax
 * Fe = 4600Hz
 */
int Fe = 4600;

// Periode d'echantillonage en microsecondes
float Te=(1000000.0/Fe);

AnalogIn son_entree(A0);
Serial pc(USBTX,USBRX);

/*
 * Remplit le tableau son[N] avec N echantillons 
 * pris avec une frequence d'echantillonage Fe 
 */
void lire(double *son, int taille)
{
    for(int i=0;i<taille;i++){
        son[i] = (double)son_entree.read();
        wait_us(Te);
    } 
}

int main()
{
        double *son, *w;
        int *ip;
        
        
        // Initialisation tableau son
        son = (double*) malloc(sizeof(double) * N); // Allocation
        lire(son, N);                               // Remplissage
        
        
        // variables necessaires pour la fft
        w = (double*) malloc(sizeof(double) * (N/2 - 1));
        ip = (int*) malloc(sizeof(int) * 25);
        ip[0] = 0;
        
                
        // FFT
        rdft(N, 1, son, ip, w);
        
        son[0]=0;
        son[2]=0;
        son[4]=0;
        son[6]=0;
        son[8]=0;
        for (int i = 0; i<N/2; i++){
            printf("%f\r\n", son[2*i]*son[2*i]); 
        }
        // diviser fréquence obtenue par 1.1307 * nb_harmonique * Fe / N
        
        free(son);
        free(w);
        free(ip);
}
