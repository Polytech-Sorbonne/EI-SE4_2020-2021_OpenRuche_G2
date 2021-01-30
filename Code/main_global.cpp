#include "mbed.h"
#include "WakeUp.h"
#include "platform/mbed_thread.h"
#include "platform/mbed_power_mgmt.h" 
//#include "mbed_stats.h"
//#include "low_power.h"
#include "DHT.h"
#include "DS1820.h" 
#include "HX711.h"

/*****************************VARIABLES****************************************/

// Communication
Serial sigfox(D1, D0); 
Serial pc(USBTX, USBRX); //debug
//DigitalOut led_power_on(D13); // si jamais on enlève le st-link


// Sensors
DHT dht_sensor(D6, DHT22);   // INTERIEUR
DHT dht_sensor_1(D5, DHT22); // EXTERIEUR
DS1820  ds1820(D10);
//DS1820  ds1820_1(D8); //sondes supplémentaires
//DS1820  ds1820_2(D9);
//DS1820  ds1820_3(D10);
//DS1820  ds1820_4(D11);
AnalogIn girouette(A0);
InterruptIn anemo(D12);
AnalogIn bat(A2);
HX711 scale(D3, D4); //DATA,SCLK


// LDO
DigitalOut enable1(D2);
DigitalOut enable2(D11);


// D7 et D8 non connectees (cf. Datasheet STM32L432KC)


// Definition Timer Anemometre
LowPowerTimer t;
// Definition Timer Timeout Anemometre
LowPowerTimeout timeout;



//---------DHT
float dht_t_f = 0; //temperature flottante signee   (_f) lue sur DHT22
uint8_t dht_t_u = 0;   //temperature entiere non signee (_u) apres conversion pour envoi
uint8_t dht_h = 0;
uint8_t dht_h1 = 0;
int dhterror = 0;
int dhterror1 = 0;

//---------DS18B20
float sonde_f = 0;
//float sonde_f1 = 0; //sondes supplémentaires
//float sonde_f2 = 0;
//float sonde_f3 = 0;
//float sonde_f4 = 0;
uint16_t sonde_u = 0;
//int8_t sonde_1 = 0; //sondes supplémentaires
//int8_t sonde_2 = 0;
//int8_t sonde_3 = 0;
//int8_t sonde_4 = 0;

//---------GIROUETTE
unsigned short val_gir = 0;    //valeur lue sur girouette
uint8_t vent_dir = 8; //direction du vent (N=0,NE=1,...,NW=7)

//---------ANEMOMETRE
uint8_t vent_vit = 0;       // vitesse du vent
bool mode_lecture = false;  // arreter ou demarrer le chrono ?
bool premiere_lecture = true;// empeche une deuxième mesure   
bool success_lecture = false;// mesure effectuee ?
bool pas_de_vent = false;
int temps = 0; // temps entre deux interruptions EN MS

//---------POIDS
float calibration_factor = 11000;
float weight_kg = 0;
uint16_t poids = 0;

//---------BATTERIE
uint8_t bat_level = 0;

//---------LUMINOSITE
uint8_t lumi = 0;

//---------SIGFOX
int trame1_32 = 0; //32bits = 4o
int trame2_32 = 0; //32bits = 4o -> somme = 12o = 1msg
int trame3_32 = 0; //32bits = 4o
uint8_t cpt_tps = 0; //cpt_tps++ toutes les 10min pour connaitre l'heure
                     //reset a 144
uint8_t scenario = 0;

//---------ALERTES
int alerte = 0;



/*******************************FONCTIONS**************************************/

// GLOBAL - Reinitialisastion des variables (rajouter les autres) + determination scenario (ebauche pas encore fonctionnelle)
           
void init(void)
{
    mode_lecture = false;
    premiere_lecture = true;
    success_lecture = false;
    
    //COMPTEUR DE TPS (remise a 0 a minuit)
    if (cpt_tps < 145) cpt_tps++;
    else cpt_tps = 0;
    
    //determination scenario
    if (cpt_tps%2 == 0 &&  //sans batterie ET
    (  (cpt_tps < 48 && cpt_tps != 12 && cpt_tps != 24) //avant 08:00, sans son, sans poids
    || (cpt_tps > 114 && cpt_tps != 132)   //OU apres 19:00, sans poids
    ) ){
        scenario = 0;
    }
    
    else if (cpt_tps%2 == 1 && (cpt_tps < 48 || cpt_tps > 114)) { //avec batterie ET (avant 08:00 OU apres 22:00)
        scenario = 1;
    }
    else if (cpt_tps == 12) { //il est 02:00
        scenario = 2;
    }
    else if (cpt_tps == 24) { //il est 04:00
        scenario = 3;
    }
    else if (cpt_tps%2 == 0     //sans batterie
            && cpt_tps >= 48    //ET apres 08:00
            && cpt_tps <= 114   //ET avant 19:00
            && cpt_tps != 72    //ET sans son
            && cpt_tps != 84    //ET sans son
            && cpt_tps != 96    //ET sans son
            ) {
        scenario = 4;
    }
    else if (cpt_tps%2 == 1     //avec batterie
            && cpt_tps >= 48    //ET apres 08:00
            && cpt_tps <= 114   //ET avant 19:00
            ) {
        scenario = 5;
    }
    else scenario = 6; //il est 12:00 OU il est 14:00 OU il est 16:00
    
}

// ANEMOMETRE - Interruption (lance le timer au 1er passage par 0; l'arrête au 2eme)
void time(void)
{
    //si une lecture est en cours
    if (mode_lecture){
        // si cest la premiere lecture
        if (premiere_lecture){
            // on arrete le chrono
            t.stop();
            
            temps = t.read_ms();
            success_lecture = true;

        }
    }else{
        // on demarre le chrono et on passe en mode lecture
        t.start();
        mode_lecture = true;
    }
}

// ANEMOMETRE - Fonction activée par l'interruption interne sur le Timer timeout
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
        success_lecture = true;
        
        temps = 99999; // vitesse a 0
    }
}

// GIROUETTE - Modifie la variable globale vent_dir
void girouette_lecture() {
    
    val_gir = girouette.read_u16();
    
    if (val_gir < 48496){       //0.74
        //NW
        vent_dir = 7;
    }else if (val_gir < 51117){ //0.78
        //SW
        vent_dir = 5;
    }else if (val_gir < 52428){ //0.80
        //NE
        vent_dir = 1;
    }else if (val_gir < 54394){ //0.83
        //W
        vent_dir = 6;
    }else if (val_gir < 55705){ //0.85
        //SE
        vent_dir = 3;
    }else if (val_gir < 58982){ //0.90
        //N
        vent_dir = 0;
    }else if (val_gir < 59637){ //0.91
        //E
        vent_dir = 2;
    }else{
        //S
        vent_dir = 4;
    }
}

// DHT - temperature et humidite dans variables dht_t_fX et dht_hX
void dht_lecture() {
    
    dhterror = dht_sensor.readData();
    if (0 == dhterror){
        dht_t_f = dht_sensor.ReadTemperature(CELCIUS);
        dht_h = dht_sensor.ReadHumidity();
    }
    //else pc.printf("Error DHT : %d\r\n", dhterror); //debug
    
    
    dhterror1 = dht_sensor_1.readData();
    if (0 == dhterror1) dht_h1 = dht_sensor_1.ReadHumidity();
    //else pc.printf("Error1: %d\r\n", dhterror1); //debug
    
}

//DS18B20 - temperature dans variables sonde_fX
void sonde_lecture() {
    
    if(ds1820.begin()) {
        ds1820.startConversion();    
        ThisThread::sleep_for(1000);
        sonde_f = ds1820.read();
    }
    //else pc.printf("DS18B20 not found\r\n"); //debug
    /*
    if(ds1820_1.begin()) {            //sondes supplémentaires
        ds1820_1.startConversion();    
        ThisThread::sleep_for(1000);  
        sonde_f1 = ds1820_1.read();
    }
    else pc.printf("DS18B20 not found");
    
    if(ds1820_2.begin()) {
        ds1820_2.startConversion();    
        ThisThread::sleep_for(1000);  
        sonde_f2 = ds1820_2.read();
    }
    else pc.printf("DS18B20 not found");
    
    if(ds1820_3.begin()) {
        ds1820_3.startConversion();    
        ThisThread::sleep_for(1000);  
        sonde_f3 = ds1820_3.read();
    }
    else pc.printf("DS18B20 not found");
    
    if(ds1820_4.begin()) {
        ds1820_4.startConversion();    
        ThisThread::sleep_for(1000);  
        sonde_f4 = ds1820_4.read();
    }
    else pc.printf("DS18B20 not found");
*/    
}

//POIDS - lecture HX711
uint8_t first_time = 1; 
void poids_lecture() {

    if(!first_time) scale.powerUp();
    
    // acquisition de la mesure (KG)
    weight_kg = scale.getGram();
    pc.printf("poids_raw=%f\r\n",weight_kg);
    
    // passage en mode power-down
    scale.powerDown();
    first_time = 0;
}

//SON - fft algo
void fft(){
    if(cpt_tps == 12){ //il est 02:00
        //FFTbcnko!
    }
}

//BATTERIE - lecture niveau batterie
void batterie_lecture() {
    float val;

    val = bat.read()*3.3*2*1.32;
    //pc.printf("V = %f\r\n", val);
    if(val < 3.73){
        //pc.printf("  0% - 10%\r\n");
        alerte = 1;
        bat_level = 0;
    }
    else if(val < 3.78){
        //pc.printf(" 10% - 30%\r\n");
        bat_level = 1;
    }else if(val < 3.89){
        //pc.printf(" 30% - 60%\r\n");
        bat_level = 2;
    }else if(val < 4.07){
       // pc.printf(" 60% - 90%\r\n");
        bat_level = 3;
    }else{
       // pc.printf(" 90% -100%\r\n");
        bat_level = 4;
    }
}

//LUMINOSITE - 
void panneau_lecture() {
    
}


//SIGFOX - conversion des données + maj trames
void sigfox_conversion(uint8_t scenario) {
    
    //ANEMO
    if(success_lecture || pas_de_vent) vent_vit = (uint8_t)(1200/temps);
   
    //DHT
    dht_t_u = (uint8_t)((dht_t_f + 40) * 2); //arrondi par defaut (3.0 to 3.4 -> 3 // 3.5 to 3.9 -> 3.5)
     
    //SONDE
    sonde_u = (int)(sonde_f * 10) + 200;     //arrondi par defaut (3.0 to 3.0625 -> 3.0 // 3.125 to 3.1875 -> 3.1)
    //*10 : arrondi a 0.1 pres + ramene en entier signe
    //+200: ramène en entier non signe (on suppose que pas de température en dessous de -20degC)
    //sonde_1 = (int8_t)((sonde_f1 - sonde_f) * 10); //temperature differentielle (8bits = +/- 12.7degC) pour les sondes supplémentaires
    //sonde_2 = (int8_t)((sonde_f2 - sonde_f) * 10);
    //sonde_3 = (int8_t)((sonde_f3 - sonde_f) * 10);
    //sonde_4 = (int8_t)((sonde_f4 - sonde_f) * 10);
    
    //POIDS
    poids = (uint16_t)(weight_kg * 10);  // pour precision de 0.1kg
    
    
    // CLEAR VARIABLES (on force les bits inutiles à prendre la valeur 0) sinon il y a des conflits avec les décalages de bits
    poids &= 0x03ff;   // on force tous les bits à 0 sauf les 10 derniers (uint16_t)
    bat_level &= 0x07; // on force tous les bits à 0 sauf les 3 derniers  (uint8_t)
        // inutile pour dht_t_u (déjà 8bits dans le uint8_t), sonde_u et dht_h
    dht_h1 &= 0x7f;    // on force tous les bits à 0 sauf les 7 derniers  (uint8_t)
    vent_dir &= 0x07; // on force tous les bits à 0 sauf les 3 derniers  (uint8_t)
    vent_vit &= 0x3f; // on force tous les bits à 0 sauf les 6 derniers  (uint8_t)
    
    // MAJ TRAMES
    trame1_32 = (sonde_u << 22) | (dht_t_u << 14) | (poids << 4) | (bat_level);
    trame2_32 = (dht_h << 25) | (dht_h1 << 18); // | (vent_dir << 15) | (vent_vit << 9);
    trame3_32 = 0;
    
    
    //TRAMES POUR LES DIFFERENTS SCENARIOS
    /*
    switch(scenario) {
        //sondes, DHT
        case 0:
            trame1_32 = (sonde_u << 22) | (dht_t_u << 14) | (dht_h << 7);
            trame2_32 = 0;
            trame3_32 = 0;
            break;
            
        //sondes, DHT, batterie
        case 1:
            trame1_32 = (sonde_u << 22) | (dht_t_u << 14) | (dht_h << 7) | (bat_level << 4);
            trame2_32 = 0;
            trame3_32 = 0;
            break;
            
        //sondes, DHT, son
        case 2:
            trame1_32 = (sonde_u << 22) | (dht_t_u << 14) | (dht_h << 7) | (vent_dir << 4) | (vent_vit >> 2);
            trame2_32 = (vent_vit << 30) | (bat_level << 27) | (poids << 17);
            trame3_32 = 0;
            break;
            
        //sondes, DHT, poids
        case 3: //7 MSBs poids on trame_1, 3 LSBs on trame_2
            trame1_32 = (sonde_u << 22) | (dht_t_u << 14) | (dht_h << 7) | (poids >> 3);
            trame2_32 = (poids << 29);
            trame3_32 = 0;
            break;
            
        //sondes, DHT, vent, luminosite
        //PROTOTYPE : apres enlever, POIDS
        case 4:
            trame1_32 = (sonde_u << 22) | (dht_t_u << 14) | (dht_h << 7) | (vent_dir << 4) | (vent_vit >> 2);
            trame2_32 = (vent_vit << 30) | (bat_level << 27) | (dht_h1 <<20) | (poids << 10) | (alerte << 9);
            trame3_32 = 0;
            break;
            
        //sondes, DHT, batterie, vent, luminosite
        case 5:
            trame1_32 = (sonde_u << 22) | (dht_t_u << 14) | (dht_h << 7) | (vent_dir << 4) | (vent_vit >> 2);
            trame2_32 = (vent_vit << 30) | (bat_level << 27) | (lumi << 25);
            trame3_32 = 0;
            break;
            
        //sondes, DHT, vent, son, luminosite
        case 6: //laisse les trames testees de base car pas fft, METS CA POUR TESTER (LE CALLBACK EST COMME CA)
            trame1_32 = (sonde_u << 22) | (dht_t_u << 14) | (dht_h << 7) | (vent_dir << 4) | (vent_vit >> 2);
            trame2_32 = (vent_vit << 30) | (bat_level << 27) | (poids << 17);
            trame3_32 = 0;
            break;
        default:
            break;
    }
    */
    
}
/*********************************MAIN*****************************************/

int main()
{    
    //Avant d'utiliser la librairie WakeUp si on a la bonne version de Mbed  
    //WakeUp::calibrate();
    
    // Calibration
    scale.setScale(calibration_factor);
 
    // LDO: laisser le courant passer
    enable1=1;
    enable2=1;
    //enable3=1;
    
    // Allumer une LED au demarrage
    //led_power_on = 1;
    
  while(1) {
    init();
    scenario = 4;
    //pc.printf("scenario= %d",scenario); //debug
    dht_lecture();
    
    sonde_lecture();
    
    //-------VENT------//
  //  if (scenario == 4 || scenario == 5 || scenario == 6 ) {
        //-----GIROUETTE----//
        girouette_lecture();
        
        //-------ANEMO------//
            // Interruption timeout après 1 seconde
        timeout.attach(&inter_timeout, 1.0);
            // Interruption externe déclenche la foncion time
        anemo.rise(&time);
        
        while (!success_lecture || !pas_de_vent){
            wait_us(0);
            }
        anemo.rise(NULL);
        timeout.detach();
 //   }
    //else {
    //    anemo.rise(NULL);
    //    timeout.detach();
    //}
    
    //-------POIDS------//
    //scenarios : 3
   // if (scenario == 3 || scenario == 4)
    poids_lecture();   
    //---------SON-------//
    //if (scenario == 2 || scenario == 6) fft();
    
    //-------BATTERIE-----//
    //scenarios : 1,5
   //if (scenario == 1 || scenario == 5 || scenario == 4)
    batterie_lecture(); //enlever (scenario == 4) apres
    
    //------LUMINOSITE-----//
    //scenarios : 4,5,6
    //if (scenario == 5 || scenario == 6 ) 
    //panneau_lecture();
 
    //-----CONVERSIONS-----//     
    sigfox_conversion(scenario);
    
    //-------DEBUG---------//
    //pc.printf("scenario= %d \r\n",scenario);
    //pc.printf("vent_dir=%x\r\n",vent_dir);
    pc.printf("sonde_u=%f\r\n",(float)(sonde_u-200)/10);
    pc.printf("dht_temp=%f\r\n",(float)(dht_t_u/2)-40);
    pc.printf("dht_humi=%d\r\n",dht_h);
    //pc.printf("vent_vit=%x\r\n",vent_vit);
    pc.printf("bat_level=%d\r\n",bat_level);
    pc.printf("dht_humibis=%d\r\n",dht_h1);
    pc.printf("poids=%d\r\n",poids);
    pc.printf("trame 1= %x \r\n",trame1_32);
    pc.printf("trame 2= %x \r\n",trame2_32);
    //pc.printf("%x%04x%08x\r\n", trame1_32, trame2_32, trame3_32);
    
    //Vérification que le dispositif est rentré en deepsleep par exemple
    //mbed_stats_cpu_get(&stats);
    //pc.printf("TIME SPENT IN DEEPSLEEP MODE = %llu\r\n", stats.deep_sleep_time);
    
    //pc.printf("TIME SPENT IN DEEPSLEEP MODE = %llu\r\n", mbed_time_deepsleep()); //returns us_timestamp_t
        // similar available functions : mbed_time_sleep(), mbed_time_idle(), mbed_time_uptime()
    // possible de faire un reset -> system_reset();
    
    sigfox.printf("AT$SF=%x%04x%08x\r\n", trame1_32, trame2_32, trame3_32);
    
    //led_power_on = 0;
    
    wait_us(10000000); //10000000=10sec
    
    //Essai mise en sleep ou standby au lieu du wait (problème de version de Mbed)
    /*WakeUp::set_ms(60000);   //Set wakeup time for 60 seconds
    sleep();*/
    
    //WakeUp::standby_then_reset(60000);
   }
}


/****************************EXPLICATIONS***************************************
Maximum de bits dans la trame : 96 bits
//--------CONVERSION_DHT---------//
temp_conv = (uint8_t)((temp_init + 40) * 2);
Temperature initiale  flottante de -40 a +80 a 0.1degC pres
Temperature convertie entiere sur 8 bits non signes -> de 0 a 240 avec un pas de 0.5 (80 pour 0degC)
Sur Ubidots : temp_init = (temp_conv / 2) - 40
//-------CONVERSION_DS18B20-------//
sonde_u = (int)(sonde_f * 10) + 200;
sonde_u = sonde_s + 200
Sonde precision de 0.5 de -10 a 85
Temperature sonde flottante (_f) de -55 a +125 (resolution = 0.0625). On va prendre [-20degC;75degC]
Temperature sonde signee entiere (_s) de -200 a +750 avec un pas de 0.1
Temperature sonde convertie entiere non signee (_u) -> de 0 a 950
Sur Ubidots : sonde_f  = (sonde_u - 200) / 10
              sonde_fX = sonde_f + 10 * sonde_X
              
//-------CONVERSION_POIDS-------//
poids = weight_g / 10 pour precision de 0.1kg ex: (uint16_t)5275g/10=528=52.8kg
Sur Ubidots : weight_kg = poids / 10 (ex: 528/10=52.8kg)
              
//-----------ANEMOMETRE-----------//
Quand on démarre une mesure, on attend de recevoir un front montant sur D12 (port lie a l'anemometre).
L'anemometre envoie un front montant par tour.
La reception du front montant declenche un timer (interruption externe).
On attend un deuxieme front montant.
Le deuxieme front montant genere une autre interruption qui arrete le timer.
Alors, le timer contient le temps en ms d'un tour d'anemometre.
S'il n'y a pas de vent. l'anemometre ne bougera pas.
Alors on definit un autre timer (lowpowertimeout) qui forcera l'arret de la mesure si elle depasse une certaine duree.
Sachant qu'un tour par seconde correspond a 2.4km/h, un timeout de 1 s neglige toutes les vitesses inferieures a 2.4km/h.
Sur Ubidots : vent_vit = vitesse entiere en km/h
*******************************************************************************/
