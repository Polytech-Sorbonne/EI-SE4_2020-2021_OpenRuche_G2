![](https://i.imgur.com/WyLN2yD.png)
















![](https://i.imgur.com/spFmWPf.png)

# Pourquoi BeeWAN?

Les abeilles sont essentielles à la biodiversité et au maintien de nos écosystèmes. Pourtant, de plus en plus de facteurs les empêchent de vivre sereinement. Les apiculteurs, pour veiller à la survie de leurs colonies, sont contraints de se déplacer de nombreuses fois pour éviter tout accident pouvant arriver à la ruche. Notre priorité est d'apporter aux apiculteurs une solution facile d'utilisation, leur permettant de gagner du temps sur leurs déplacements et d'identifier les facteurs de l'augmentation de la production.

![](https://i.imgur.com/oixIBU3.jpg)

# Présentation du produit

BeeWAN est un dispositif de ruche connectée ayant vocation à accompagner les apiculteurs professionnels comme amateurs dans la surveillance de leurs ruches et colonies. 
BeeWAN propose notamment : une autonomie énergétique grâce à son panneau solaire et sa batterie, un affichage de plusieurs paramètres via un tableau de bord accessible depuis un appareil numérique (téléphone,tablette, ordinateur) avec une connexion internet. BeeWAN vous permet d’afficher en temps presque réel des variations dans l'environnement de la ruche, comme par exemple des mesures des capteurs de température (intérieure et extérieure), d'humidité (extérieure) et de poids ainsi que de l’état de charge de la batterie. BeeWAN vous offre tous les outils nécessaires pour monitorer la ruche en toute sérénité.

# Organisation du projet et déroulement

Le projet BeeWAN a été réalisé dans le cadre de la participation de Polytech Sorbonne au concours ["Aider les apiculteurs à sauver les abeilles"](https://www.snapiculture.com/challenge-electro-apicole/) organisé par le Syndicat National des Apiculteurs la Fédération Nationale des Groupements Techniques Apicoles (FNGTA) et "Demain la Terre".

![](https://i.imgur.com/lIACt54.png)

Le groupe ayant travaillé dessus est composé de quatre étudiants d'EISE4 : Sharon BAURBERG, Florent HAMELET-DELVAL, André PINTO NUNES et Aya SADOUKI.

L'équipe BeeWAN a travaillé sur ce projet de septempre 2020 à janvier 2021.

## Le cahier des charges

Pour la réalisation du cahier des charges, M.Yann Douze, professeur de Polytech Sorbonne et apiculteur amateur, a été consulté afin de cerner les besoins essentiels des apiculteurs.

Le poids de la ruche est une indication clé pour l'apiculteur car il permet de suivre la production de miel de la colonie lors de la saison haute (printemps-été) et de vérifier que la colonie survit et reste dans la ruche en saison basse (autonomne-hiver).

La température intérieure est essentielle afin de pouvoir monitorer la présence de couvain (amas de larves) indispensable au renouvellement et à la survie de la colonie. La température et l'humidité extérieure permettent de rendre compte des caractéristiques les plus importantes de l'environnement autour de la ruche et influent sur la sortie des abeilles.

La batterie est un point clé d'un dispositif autonome. Il faut donc, a minima, que l'apiculteur soit prévenu que la batterie doit être rechargée manuellement quand il le faut.

Enfin, des fonctionnalités comme la mesure de la direction du vent, de sa vitesse, de la luminosité au niveau de la ruche et l'analyse des sons de la colonie sont des pistes qui sont intéressantes à explorer pour fournir une explication plus précise du comportement des abeilles et permettre aux apiculteurs de prévoir les évolutions de la production de miel et de l'effectif de la colonie. 

Après élaboration du cahier des charges, nos priorités ont été définies comme suit:

![](https://i.imgur.com/jngkfds.png)

## Lancement du projet et choix des composants

Le but final étant d'avoir un dispositif compact et solide, la forme du prototype visée est un PCB. Néanmoins, le PCB implique beaucoup de soudure, travailler dessus est très chronophage. Il est recommandé de monter son prototype sur une platine afin de pouvoir réagir rapidement aux changements à réaliser.

La liste des composants nécessaires pour réaliser ce projet est donc:
            
  * Une [platine](https://www.cdiscount.com/informatique/cables-connectiques/breadboard-carte-d-experimentation-400-points-sans/f-1072015-auc6931908077815.html?idOffre=780093304&cid=search_pla&cm_mmc=PLA!COR!INF!MP!983658467!m295299381_pAUC6931908077815-780093304_l9056140_tpla-1168533929274_&gclid=EAIaIQobChMIlbD4nPa17gIVwgh7Ch1SrAhAEAYYBSABEgJ8lvD_BwE)
            
  * Un [microcontrôleur](https://os.mbed.com/platforms/ST-Nucleo-L432KC/) (ici le STM32L432KC)
            
  * Un [panneau solaire](https://www.gotronic.fr/art-cellule-solaire-sol2w-18995.htm) 5.5V
            
  * Une [batterie Li-Ion](https://www.gotronic.fr/art-accu-li-ion-3-7-v-1050-mah-pr474446-5811.htm) 3.7V 1050mAh
            
  * Une [carte d'alimentation Lipo Rider](https://www.gotronic.fr/art-carte-lipo-rider-pro-106990008-19050.htm)
            
  * Un [module Wisol avec son antenne](https://yadom.fr/carte-breakout-sfm10r1.html)
            
  * Une [jauge de contrainte maximale](https://fr.aliexpress.com/item/32821335975.html?spm=a2g0o.detail.1000060.1.70c57419XUIr2b&gps-id=pcDetailBottomMoreThisSeller&scm=1007.13339.128609.0&scm_id=1007.13339.128609.0&scm-url=1007.13339.128609.0&pvid=bee5c452-83cb-4266-97bf-3a4ea713013e&_t=gps-id:pcDetailBottomMoreThisSeller,scm-url:1007.13339.128609.0,pvid:bee5c452-83cb-4266-97bf-3a4ea713013e,tpp_buckets:668#0%23131923%2358_668%23808%237756%23616_668%23888%233325%239_668%232846%238116%23928_668%232717%237566%23874__668%233468%2315618%23960) de 200kg avec une précision de 100g à fixer sur un support en métal de forme et de taille similaire à une ruche.
            
  * Un [module HX711](https://www.gotronic.fr/art-amplificateur-pour-capteur-de-force-sen-13879-25334.htm)
            
  * Une [sonde de température DS18B20](https://www.amazon.fr/dp/B075FYYLLV/ref=asc_df_B075FYYLLV1601089200000/?tag=qwantcom75-21&creative=22950&creativeASIN=B075FYYLLV&linkCode=df0)
            
  * Un [capteur de température/humidité DHT22 Grove](https://www.gotronic.fr/art-capteur-d-humidite-et-de-t-grove-101020019-18964.htm)
            
  * Un cable micro-USB
            
  * Un cable mini-USB
            
  * Une plaque de cuivre et une machine à laser pour imprimer le PCB
            
  * Deux résistances de 1MΩ
  
  * 3 LDO pour la consommation et la conversion 5V vers 3V3.
            
       Et éventuellement:
      
  * Un [anémomètre avec girouette intégrée](https://www.lextronic.fr/ensemble-capteurs-girouette-anemometre-57683.html) pour le vent avec deux résistances de 10kΩ
  
  * Un [adaptateur RJ11](https://www.conrad.fr/p/fiche-modulaire-femelle-sans-outils-tru-components-1572349-rj12-femelle-droit-noir-1-pcs-1572349?gclid=EAIaIQobChMI5eu53JmK7AIVgp3VCh3G9Q39EAQYBiABEgJlVvD_BwE&gclsrc=aw.ds) pour connecter l'anémomètre
         
  * Un [amplificateur LM386](https://fr.farnell.com/texas-instruments/lm386n-1-nopb/ampli-audio-classe-ab-dip-8/dp/2496437), 5 résistances de 10kΩ, 1 de 12kΩ et 1 de 1Ω  pour la mesure de la luminosité
            
  * Un [Micro Loudness Sensor Grove](https://www.seeedstudio.com/Grove-Loudness-Sensor.html) pour le son.
            
Il est à noter que tous les capteurs mis dehors doivent pouvoir être protégés des intempéries, des gaines seront donc utilisées. 

Le dispositif entier sera placé dans une petite boité fermée (avec des trous sur le côté pour laisser passer les fils des capteurs).

Le choix des capteurs va influencer notre développement. Par exemple, l'étendue de mesures des capteurs choisis ici ne permet pas d'utiliser ce dispositif dans des conditions de températures extrêmes. Les consommations de courant de chaque capteur vont influencer nos choix d'optimisations de la consommation dans le dispositif. Plus un capteur consomme, plus on devra trouver des manières de réduire notre consommation pour garantir l'autonomie énergétique du dispositif.

# Première étape: réalisation du prototype sur platine (Labdec)

Cette première étape va permettre de tester rapidement nos fonctions à implémenter et d'ajuster le code en cas de problème.

Tout le code a été réalisé sur la plateforme Mbed Online. Cela donne l'avantage de pouvoir utiliser directement des librairies développées par d'autres utilisateurs en OpenSource. L'utilisation de Mbed Studio pourrait même être encore plus judicieuse, les fonctions d'optimisation de la consommation semblent être plus facilement configurables dessus que sur la version en ligne.

Nous allons regarder en détail chaque fonctionnalité qui peut être intégrée par la suite à notre prototype.



## Mesure du poids: pesée de la ruche

Pour peser la ruche, nous avons choisi une **jauge de contrainte** pouvant mesurer jusqu'à 200kg disponible pour **10.43€** sur le site [AliExpress](https://fr.aliexpress.com/item/32821335975.html?spm=a2g0o.detail.1000060.1.70c57419XUIr2b&gps-id=pcDetailBottomMoreThisSeller&scm=1007.13339.128609.0&scm_id=1007.13339.128609.0&scm-url=1007.13339.128609.0&pvid=bee5c452-83cb-4266-97bf-3a4ea713013e&_t=gps-id:pcDetailBottomMoreThisSeller,scm-url:1007.13339.128609.0,pvid:bee5c452-83cb-4266-97bf-3a4ea713013e,tpp_buckets:668#0%23131923%2358_668%23808%237756%23616_668%23888%233325%239_668%232846%238116%23928_668%232717%237566%23874__668%233468%2315618%23960). Nous l'avons ensuite relié à un module comportant un **amplificateur pour jauge de contrainte, le HX711** (le nôtre est un module [Sparkfun](https://www.sparkfun.com/products/13879) intégrant le [HX711](https://cdn.sparkfun.com/datasheets/Sensors/ForceFlex/hx711_english.pdf)).

### Matériel

La jauge de contrainte que nous avons choisie a été assemblée avec un support métallique sur lequel sera positionnée la ruche. Celle-ci est composée d'un **pont de Wheatstone** traduisant ainsi une contrainte physique en une tension différentielle.
<img align="left" width="350" src="https://i.imgur.com/42F00HQ.png">
<img align="center" width="270" src="https://i.imgur.com/IZ132Pp.png">
<img align="right" width="220" src="https://i.imgur.com/F8F4Bid.png">

Si vous choisissez la jauge de contrainte proposée, les couleurs des fils (non standardisées) ne correspondent pas aux couleurs annoncées sur le module (standardisées). Ainsi, voici la correspondance des fils sur l'image du module :
| Signification | Fil sortant de la jauge de contrainte | Nom de la pastille sur le module|
|--|----|----|
| alimentation +5V | fil noir | RED |
| masse | fil blanc | BLK |
| Vout- | fil vert | WHT |
| Vout+ | fil rouge | GRN |
| Shield | fil non gainé (brins argentés) | YLW |

### Logiciel
Une [librairie MBED](https://os.mbed.com/teams/Cr300-Litho/code/HX711/) permet de récupérer la valeur du poids depuis le module.

Le code donné en exemple dans la librairie permet de configurer la calibration et de faire la tare de la jauge. Nous avons déterminé le `calibration_factor` et effectué une tare puis l'avons inscrit en dur en début de code pour ne pas avoir à la refaire.


## Mesure de la température intérieure

![](https://i.imgur.com/l3J83B7.png)

Afin d'évaluer la température à l'intérieur de la ruche, nous avons mis en place une sonde de température de type [DS18B20](https://datasheets.maximintegrated.com/en/ds/DS18B20.pdf). Notre choix s'est porté sur ce modèle car ce dernier est adapté aux conditions climatiques rencontrées : les fils sont entourés par une gaine de protection et empêchent un quelconque dysfonctionnement lié aux intempéries. De plus, sa finesse permet de l'intégrer dans des espaces restreints comme entre les cadres de la ruche.

### Comment ça marche ?

La sonde peut mesurer des températures de -55 à +125°C avec une précision maximale de ±0,0625°C. 
Trois fils multibrins sont identifiés en sortie du capteur : un premier (rouge) pour l'alimentation entre 3 et 5,5V, un deuxième (noir) pour la connexion à la masse du système et un troisième (jaune) pour l'envoi des données numériques. Une résistance de 4,7kΩ est nécessaire entre l'alimentation et la donnée afin de ne pas corrompre cette dernière (la sonde étanche proposée intègre déjà cette résistance).

### La technologie OneWire

L'interface OneWire permet d'échanger avec un microcontrôleur sur un unique bus de données de façon bidirectionnelle. Les données sont converties par l'intermédiaire d'un CAN (Convertisseur Analogique-Numérique). La résolution par défaut du capteur est de 12 bits pour une précision de ±0,0625°C. Elle peut être configurable par l'utilisateur à 9, 10 ou 11 bits. Le dispositif DS18B20 est, par ailleurs, composé d'une zone mémoire de 8 octets et d'une EEPROM de 3 octets. Celles-ci permettent de stocker les valeurs de température converties, la configuration du CAN et l'identifiant du capteur. 


## Mesures de température et d'humidité extérieures simultanées

Au lieu d'utiliser un capteur dédié uniquement aux relevés d'humidité, nous avons choisi de coupler température et humidité pour notamment mettre en parallèle les données récupérées en dehors et à l'intérieur de la ruche. Notre choix s'est porté sur le module Grove-Temperature&Humidity avec un [DHT22](https://wiki.seeedstudio.com/Grove-Temperature_and_Humidity_Sensor_Pro/) intégré. Tout comme la sonde, les composants sont intégrés et protégés. Le cablâge est semblable avec une tension d'alimentation entre 3,3 et 6V. 

### Comment ça marche ?

![](https://i.imgur.com/iErutwD.png)

La technologie OneWire n'est plus utilisée. Les données converties par son CAN 8 bits sont envoyées directement sur un port digital du microcontrôleur pour traitement. Le module peut réaliser des mesures entre -40 et +80°C avec une précision de ±0,5°C et entre 0 et 100%HR(Humidity Rate) avec une précision de ±2%HR.

 
## Batterie

![Circuit](https://i.imgur.com/GWOmzBZ.png)

&nbsp;
### Mesure de la charge de la batterie

Il est possible de déterminer le niveau de charge d'une batterie à partir de sa tension de sortie. La relation entre la charge et la tension (que l'on appelle état de charge) est généralement donnée dans la datasheet de la batterie. Dans le cas contraire, on peut mesurer nous-mêmes les seuils de tension (une fois connectée à la carte d'alimentation, on peut connaître l'état de charge de la batterie en appuyant sur le bouton poussoir de la Lipo Rider Pro, il suffit de mesurer la tension grâce au pont diviseur de tension et d'un multimètre).
Une fois que cette relation est connue, il suffit de mesurer la tension de sortie avec un pont diviseur de tension et de calculer la charge.



## Communication des données du dispositif

Afin de répondre aux exigences formulées dans le cahier des charges (notamment en termes de consommation énergétique), notre système communique via la technologie LPWAN (Low-Power Wide Area Network comprenez "Réseau longue portée basse consommation"). Nous avons choisi un des opérateurs français les plus courants dans le monde de l'Internet des objets, **Sigfox** (pensez à vérifier que votre zone géographique est couverte par le réseau Sigfox [ici](https://www.sigfox.com/en/coverage). Nous utilisons en outre [un kit](https://yadom.fr/carte-breakout-sfm10r1.html) composé d'un **module WISOL**, d'une **antenne 868MHz** et d'un **abonnement d'un an** au résesau Sigfox (limite d'envoi à 140 messages par jour et de réception à 4 messages par jour). Nous pouvons ainsi formater et retransférer les informations collectées par le backend (les "coulisses") de Sigfox vers une interface conviviale en configurant des **callbacks**. Finalement, nous avons mis en place un tableau de bord personnalisé sur la plateforme **Ubidots** dont nous avons utilisé la version non-commerciale : [Ubidots STEM](https://ubidots.com/stem/). Celle-ci permet la configuration de 3 appareils, 10 variables par appareil connecté et 10 widgets par tableau de bord.

![](https://i.imgur.com/LtW8NdU.png)

### BeeWAN - encoder les données

Un message est composé de **12 octets** soit 96 bits. Donc, pour économiser de l'espace dans la trame de données envoyée, nous n'envoyons que des _entiers non signés_ dont la taille dépend de l'intervalle et de la précision de chaque variable.

| Variable             | Taille (quand on l'envoie) | Intervalle              | Précision | Conversion                                                                     | Exemple                                |
|----------------------|------------------|--------------------|-----------|--------------------------------------------------------------------------------|----------------------------------------|
| Température intérieure (`sonde_u`) | 10 bits          | -20.0°C à +82.4°C | 0.1°C     | `sonde_u = (int)(sonde_f * 10) + 200;`                                         | -4.2°C sera encodé par 158          |
| Température extérieure (`dht_t_u`) | 8 bits           | -40.0°C à +88.0°C | 0.5°C     | `dht_t_u = (uint8_t)((dht_t_f + 40) * 2);`                                     | -4.5°C sera encodé par 71           |
| Masse (`poids`)              | 10 bits          | 0.0kg à 102.4kg   | 0.1kg     | `poids = (uint16_t)(weight_kg * 10);`                                          | 35.4kg sera encodé par 354          |
| Niveau de la batterie (`bat_level`)       | 3 bits           | 0% à 100%         | max 20%   | 0% à 10% = 0, 10% à 30% = 1, 30% à 60% = 2, 60% à 90% = 3, 90% à 100% = 4 | 67% sera encodé par 3               |
| Humidité extérieure (`dht_h`)   | 7 bits           | 0% à 100%         | 1%        | aucune                                                                           | 84% sera encodé par 84              |
| Direction du vent (`vent_dir`)      | 3 bits           | 0° à 360°         | 45°       | N = 0, NE = 1, ... , NW = 7                                                    | un vent du Sud-Ouest sera encodé par 5 |
| Vitesse du vent (`vent_vit`)         | 6 bits           | 0km/h à 64km/h    | 1km/h     | aucune   | un vent de 32km/h sera encodé par 32    |

### BeeWAN vers Sigfox - formater les données encodées

Pour que les variables occupent la bonne place et aient la bonne taille dans la trame d'envoi, on force d'abord les bits inutilisés à 0 par masquage :

```c
poids &= 0x03ff;   // mettre tous les bits inutiles a 0 sauf les 10 derniers 
bat_level &= 0x07; // mettre tous les bits inutiles a 0 sauf les 3  derniers
dht_h1 &= 0x7f;    // mettre tous les bits inutiles a 0 sauf les 7  derniers
vent_dir &= 0x07;  // mettre tous les bits inutiles a 0 sauf les 3  derniers
vent_vit &= 0x3f;  // mettre tous les bits inutiles a 0 sauf les 6  derniers
```

Puis, on effectue des shifts sur les bits des variables :
```c
trame1_32 = (sonde_u << 22) | (dht_t_u << 14) | (poids << 4) | (bat_level);
trame2_32 = (dht_h << 25) | (dht_h1 << 18) | (vent_dir << 15) | (vent_vit << 9); //comporte aussi l'humidité intérieure dht_h1 que nous avons retirée du projet
trame3_32 = 0;
```

Avant de concaténer les trames ensemble et de les envoyer par une commande comprise par le module WISOL (voir [doc](https://yadom.fr/media/product-attachment//home/magento///File-1571653382.pdf) pour d'autres commandes) :
```c
// Déclaration plus haut de la liaison série : Serial sigfox(D1, D0);
sigfox.printf("AT$SF=%x%04x%08x\r\n", trame1_32, trame2_32, trame3_32);
```

### Sigfox vers Ubidots - "déformater" les données encodées

Pour configurer un callback (préciser à Sigfox l'emplacement et la taille de chaque variable dans la suite de bits envoyée pour envoyer les variables vers Ubidots), vous pouvez suivre ce [tutoriel](https://help.ubidots.com/en/articles/924209-setup-your-sigfox-callback-to-talk-with-ubidots-cloud) très complet en l'adaptant aux variables envoyées. Paradoxalement, la complexité de l'implémentation résidait en une ligne; la configuration de la grammaire du message ("Custom payload config") dont la syntaxe est expliquée en cliquant sur la petite icône "Help" :
```
sonde::uint:10 dhtemp:1:uint:8:big-endian:5 poids:2:uint:10:big-endian:5 bat:3:uint:4:big-endian:3 dhum:4:uint:7 hum1:4:uint:7:big-endian:0 gir:5:uint:3:big-endian:1 anemo:6:uint:6:big-endian:6
```
Le corps du message retransmis est écrit en JSON. Le callback final ainsi implémenté ressemble à ceci :
![](https://i.imgur.com/sW0sEu4.png)

### Ubidots - décoder les données et les afficher

#### Ajouter un appareil
Après avoir créé un compte Ubidots, il faut y ajouter l'appareil que l'on souhaite connecter :
![](https://i.imgur.com/zW2mtBG.png)

Le "Device Name" correspond à l'identifiant unique du module WISOL (6 caractères en hexadécimal).

Une fois le callback (bien) configuré et l'appareil créé dans Ubidots, toutes les variables seront automatiquement ajoutées sur Ubidots après que le 1er envoi ait correctement eu lieu (onglet **"Devices"**, cliquer sur le nom choisi pour visualiser les variables ainsi créées).

#### Décoder les variables
La température intérieure, la température extérieure et le poids doivent être convertis afin de récupérer la valeur initiale.
* **Créer une variable synthétique**
![](https://i.imgur.com/BOHTyeL.png)
* **Configurer la variable synthétique** On entre ici la formule inverse de celle utilisée pour encoder la donnée. Par exemple, pour la température extérieure :
![](https://i.imgur.com/uKM88I3.png)

#### Affichage personnalisé
Vous pouvez enfin configurer le tableau de bord comme bon vous semble en ajoutant des **widgets** en cliquant sur l'icône "**+**".
Un tableau de bord vierge peut ressembler à cela :
![](https://i.imgur.com/Wjw2FND.png)

# Autres pistes de fonctionnalités explorées

## Analyse du son

Les abeilles émettent du son. Pour communiquer entre elles, elles font vibrer leur ailes d'une façon spéciale afin de produire un bruit caractéristique.

L'analyse du son peut permettre de repérer un état de stress ou une préparation de la colonie à son départ vers une autre ruche. Pour que l'analyse du son soit faite correctement, il faut avoir le moins de bruit possible aux alentours de la ruche. Idéalement, la mesure devrait se faire vers 2 ou 3h du matin pour éviter un maximum les bruits parasites. De plus, une ou plusieurs mesures devraient pouvoir être faites dans l'après-midi pour repérer un éventuel état de stress dus à des prédateurs des abeilles comme les frelons asiatiques. Réaliser des mesures en pleine journée implique de pouvoir repérer avec précisions les raies de fréquences qui nous intéressent.

### FFT

Pour analyser les fréquences (harmoniques) contenues dans un son, nous utilisons l'algorithme de la FFT. Cet algorithme mathématique est très largement utilisé dans le monde du traitement audio. 

Un des risques de la FFT est qu'elle peut être gourmande en courant consommé. Nous utilisons la RDFT pour réaliser cette analyse. Contrairement à la FFT de base, cet algorithme prend des points précis à un intervalle précisé lors de l'utilisation de l'algorithme. De plus, l'algorithme de base de la FFT est fait pour analyser des points complexes (avec une partie réelle et une partie imagaire), la RDFT permet de prendre uniquement la partie réelle du point pour calculer les raies de fréquences présentes. Cela est suffisant dans notre cas car, avec notre micro, on ne récupère que la partie réelle du point à analyser, prendre une analyse incorporant les parties imaginaires (qui seraient à 0 dans notre cas) compliqueraient les calculs pour le microcontôleur sans ajouter de plus-value. Cela permet donc d'économiser un peu de courant dans notre consommation par le micro.

### Branchement du capteur sur la platine

L'avantage de ce capteur est qu'il possède un connecteur grove, il suffit donc de brancher un câble Grove d'un coté et avec 4 fils mâles de l'autre pour le relier à la platine. Il faut relier le fil rouge à l'alimentation 3V3 du STM32, le fil noir à sa masse et le fil jaune à la pin du microconrôleur où l'on veut lire les données.

![](https://i.imgur.com/JuP2tA6.png)

### Librairie utilisée

La [librairie]() que nous avons utilisée n'est pas directement importable depuis le bouton Import de Mbed Online.

Pour utiliser la librairie, le nombre de points choisis doivent être impérativement d'une puissance de 2.

Il faut allouer de la place en mémoire pour 2 tableaux afin que le code puisse les utiliser pour y placer ses résultats de calculs intermédiaires.

Enfin, un tableau contenant les valeurs acquises pour les échantillons à analyser doit être passé en paramètre de la fonction. Ce tableau, après que la fonction rdft() de la librairie ait fini de s'exécuter, contiendra le tableau avec des amplitudes correspondant aux fréquences trouvées par la RDFT. Il faudra ensuite multiplier l'indice de la case par Fe, la fréquence d'échantillonnage et diviser le tout par N, le nombre d'échantillons pour obtenir la fréquence correspondante.

Pour régler la précision de la RDFT, on peut jouer sur 2 paramètres: Fe et N. La seule chose à respecter étant que la fréquence maximale détectable par l'algorithme (donc la case avec le plus haut indice) soit inférieure à Fe/2.
 
## Luminosité

![Circuit](https://i.imgur.com/0eO0WgA.png)

### Mesure de la luminosité

Pour mesurer la luminosité nous avions d'abord pensé à incorporer un capteur de lumière tel que [TSL2561](https://www.adafruit.com/product/439). Ce capteur nous aurait permis de déterminer la luminosité en lux avec précision. Nous avons décidé de ne pas l'utiliser pour plusieurs raisons: premièrement, nous n'avons pas besoin d'une mesure précise de la luminosité et deuxièmement ce capteur est assez coûteux (surtout en sachant qu'il est dispensable).

À la place du capteur de luminosité, on utilisera le panneau solaire. D'après [Joseph Amajama](https://www.researchgate.net/publication/306059733_Effect_of_Solar_ILLuminance_or_Intensity_on_Solar_Photovoltaic_cell%27s_output_and_the_use_of_Converging_lenses_and_X_or_Gamma_rays_to_enhance_output_performance), la luminosité est proportionnelle au courant fourni par le panneau. Ainsi, il nous suffit de mesurer ce courant. La donnée obtenue ne sera pas la valeur exacte de la luminosité en lux, mais elle permettra d'en faire une estimation approximative. Cela suffira pour mettre en relation les variations de productivité des abeilles avec les variations de luminosité.

### Comment ça marche?

Comme nous venons de le dire, pour estimer la luminosité, il faut mesurer le courant généré par le panneau solaire.

![Circuit1](https://i.imgur.com/h2ljhz2.png)
#### 1- Mesure d'un courant electrique
Pour mesurer un courant, on utilise une résistance de shunt (de 1Ω). Il s'agit d'une résistance placée entre le panneau solaire et la Lipo Rider de façon à ce qu'elle soit traversée par le courant fourni par le panneau. Puisque la résistance vaut 1 Ω, alors le courant qui la traverse est égale à la tension à ses bornes. Ainsi, pour mesurer le courant, il suffit de mesurer la tension aux bornes de la résistance.

![Circuit2](https://i.imgur.com/b3FPWd1.png)
#### 2- Mesure d'une différence de potentiel
Pour calculer la différence de potentiel de la shunt, on utilise un AOP LM386 dans un montage soustracteur. Si toutes les résistances ont la même impédance alors la tension de sortie du montage sera égale à la différence entre les deux entrées. Le gain de l'amplificateur est choisi de façon à ne pas dépasser la limite imposée par les pins analogiques (3V3).

![Circuit](https://i.imgur.com/0eO0WgA.png)
#### 3- S'assurer que la tension de sortie ne dépasse pas 3V3
Notre panneau solaire délivre un courant maximal de 360mA, donc la tension maximale lue vaudra 360mV.
Le coefficient d'amplification de l'AOP vaut entre 20 et 200: si les pins de gain (1 et 8) sont court-circuitées, le gain vaut 200; si elles ne sont pas connectées, le gain vaut 20; si elles sont connectées par une résistance, le gain sera inversement proportionnel à son impédance.
On a choisi de ne pas connecter ces pins, vu qu'un gain de 20 crée déjà une tension de sortie maximale de 7.2V.
Pour ramener cette tension en dessous de 3V3, on utilise un pont diviseur de tension qui divisera ce voltage par 2,2 et ramènera la tension maximale à 3.27V.


## Mesure de la vitesse et de la direction du vent

Pour ce projet, nous avons utilisé l'**ensemble de capteurs anémomètre/girouette LEXCA007**.
Le capteur coûte **28€ TTC** sur le site de [Lextronic](https://www.lextronic.fr/ensemble-capteurs-girouette-anemometre-57683.html) et il communique à travers un **câble RJ11** de 50 cm. Pour pouvoir communiquer avec un microcontrôleur, il est possible d'acheter une [Interface Grove-Arduino-micro:bit](https://www.lextronic.fr/platine-pour-capteur-meteo-57577.html) à **8,40€ TTC**. Nous avons décidé de faire notre propre interface en utilisant un [adaptateur RJ11](https://www.conrad.fr/p/fiche-modulaire-femelle-sans-outils-tru-components-1572349-rj12-femelle-droit-noir-1-pcs-1572349) à **2,04€ TTC** et deux [résistances](https://fr.rs-online.com/web/p/resistances-traversantes/0131895) pull-up de **10kΩ**.

### L'anémomètre

#### Comment ça marche?

<img align="right" width="400" src="https://media1.giphy.com/media/19k9QSdvBoZyW5wrt9/giphy.gif">

L'anémomètre est constitué par une **turbine**, deux **aimants** et un **I**ntérrupteur à **L**amelles **S**ouples (**ILS**).
Les aimants sont attachés à la turbine alors que l'interrupteur est fixé au support.
Ainsi, lorsque le vent souffle, les aimants passent régulièrement sur l'interrupteur.
Quand un aimant est sur l'interrupteur, les lamelles qui le constituent rentrent en contact et ferment l'interrupteur.
Quand l'aimant est loin de l'interrupteur, les lamelles qui le constituent s'éloignent et ouvrent l'interrupteur.
En comptant le temps que prend une rotation, on peut connaître le nombre de rotations par unité de temps qui traduit la vitesse du vent.

&nbsp;
 
&nbsp;

<img align="right" width="400" src="https://i.imgur.com/xicoq5M.png">

À la sortie de l'anémomètre, on trouve 2 fils. L'un relie la masse à l'interrupteur ILS et l'autre relie l'interrupteur à une résistance pull-up et à un port digital du microcontrôleur. Lorsque l'interrupteur est ouvert, le signal reçu par le microcontrôleur est VCC. Lorsque l'interrupteur est fermé, le signal reçu par le microcontrôleur est GND.

Pour mesurer la vitesse de rotation de l'anémomètre, il suffit de compter le temps entre 2 passages par 0. Cela peut se faire en utilisant un TIMER qui se déclenchera par une interruption externe (passage à 0 du signal) et qui s'arrêtera par une autre interruption externe (deuxième passage à 0).

&nbsp;

&nbsp;


#### Durée de vie

Le composant le plus à même de poser des problèmes de durée de vie est l'interrupteur. On estime la durée de vie électronique d'un ILS à 10 millions de cycles et la durée de vie mécanique entre 100 millions et 1 milliard de cycles.

Or, sachant qu'un vent de 2.4 km/h correspond à un contact par seconde et que le vent souffle à 14.4 km/h en moyenne (à Paris), on aura 6 contacts par seconde. Alors, on estime que sa durée de vie mécanique se situe entre 192 jours (soit 6 mois) et 1929 jours (soit 5 ans et 3 mois).

En supposant que l'on lit la vitesse du vent en permanence (ce qui n'est pas le cas), la durée de vie electronique serait de seulement 19 jours. En faisant seulement une mesure toutes les 10 minutes (supposons qu'une mesure nécessite 10 cycles) sa durée de vie passe à 1157 jours (soit 3 ans et 2 mois).

Si l'interrupteur arrive en fin de vie, il peut simplement être remplacé par un autre. Si la durée de vie est jugée trop courte, il faudra le remplacer par un capteur à effet Hall. De même que les ILS, un capteur à effet de Hall détecte les variations de champs magnétiques et permettra de compter le nombre de rotations par seconde de l'anémomètre.


&nbsp;
 
&nbsp;

&nbsp;

### La girouette

#### Comment ça marche?

<img align="right" width="400" src="https://media2.giphy.com/media/CsC9KlMHeo3pYcr2a7/giphy.gif">

Tout comme l'anémomètre, la girouette utilise des ILS pour effectuer des mesures. Elle est constituée par une fléche et 8 ILS disposés en forme d'étoile (radialement) de façon à ce que chaque ILS pointe vers un point cardinal (N, S, E, W, NE, NW, SE, SW). Chaque interrupteur est connecté à une resistance différente. Ces résistances formeront un pont diviseur de tension avec la résistance pull-up. Lorsqu'un interrupteur est fermé, tous les autres sont ouverts, donc il y aura toujours un pont diviseur de tension avec une seule résistance. Le signal (analogique) qui arrive en entrée du microcontrôleur aura une valeur différente selon la valeur de la résistance qui est connectée. Si on note la résistance de la girouette ***Rgir*** et la résistance pull-up ***Rpull*** alors, la valeur ***Va*** lue dans l'entrée analogique est "***Va*** = ***Rgir*** / (***Rgir + Rpull***) x ***Vcc***". Dans le cas du capteur **LEXCA007** (en supposant ***Rpull = 10KΩ*** et ***Vcc = 3V3l***), les résistances et les tensions lues correspondantes ont les valeurs suivantes:

&nbsp;

&nbsp;


| N | NE | E | SE | S | SW | W | NW |
|:-:|:-:|:-:|:-:|:-:|:-:|:-:|:-:|
| &nbsp;&nbsp;&nbsp;64,4 KΩ &nbsp;&nbsp;&nbsp;| &nbsp;&nbsp;&nbsp;39,2 KΩ&nbsp;&nbsp;&nbsp; | &nbsp;&nbsp;&nbsp;99,7 KΩ&nbsp;&nbsp;&nbsp; | &nbsp;&nbsp;&nbsp;54,4 KΩ&nbsp;&nbsp;&nbsp; | &nbsp;&nbsp;&nbsp;119,4 KΩ&nbsp;&nbsp;&nbsp; | &nbsp;&nbsp;&nbsp;33,8 KΩ&nbsp;&nbsp;&nbsp; | &nbsp;&nbsp;&nbsp;47,1 KΩ&nbsp;&nbsp;&nbsp; | &nbsp;&nbsp;&nbsp;27,2 KΩ&nbsp;&nbsp;&nbsp; |
|2.86 V|2.63 V|3.00 V|2.79 V|3.04 V|2.55 V|2.72 V|2.41 V|

On remarque que les valeurs pouvant être lues par le microcontrôleur se situent entre 0V et 3V3 mais la fonction `AnalogIn.read()` renvoie une valeur normalisée (entre 0.0 et 1.0).Donc, les valeurs vue précédemment deviennent:

| N | NE | E | SE | S | SW | W | NW |
|:-:|:-:|:-:|:-:|:-:|:-:|:-:|:-:|
| &nbsp;&nbsp;&nbsp;&nbsp;2.86 V &nbsp;&nbsp;&nbsp;&nbsp;| &nbsp;&nbsp;&nbsp;&nbsp;2.63 V &nbsp;&nbsp;&nbsp;&nbsp;| &nbsp;&nbsp;&nbsp;&nbsp;3.00 V &nbsp;&nbsp;&nbsp;&nbsp;| &nbsp;&nbsp;&nbsp;&nbsp;2.79 V &nbsp;&nbsp;&nbsp;&nbsp;| &nbsp;&nbsp;&nbsp;&nbsp;3.04 V &nbsp;&nbsp;&nbsp;&nbsp;| &nbsp;&nbsp;&nbsp;&nbsp;2.55 V &nbsp;&nbsp;&nbsp;&nbsp;| &nbsp;&nbsp;&nbsp;&nbsp;2.72 V &nbsp;&nbsp;&nbsp;&nbsp;| &nbsp;&nbsp;&nbsp;&nbsp;2.41 V &nbsp;&nbsp;&nbsp;&nbsp;|
|0.87|0.80|0.91|0.84|0.92|0.77|0.82|0.73|

&nbsp;

&nbsp;

&nbsp;

&nbsp;



#### Durée de vie

<img align="right" width="400" src="https://i.imgur.com/yAODgwt.png">

Contrairement à l'anémomètre, la girouette ne fera pas plusieurs rotations par seconde. De plus, on ne prend en compte que des grosses variations (pour 8 ILS, on a des angles de 45º) et de telles variations n'arrivent pas toutes les secondes. Ainsi, on estime que la durée de vie de la girouette sera largement supérieure à celle de l'anémomètre.

Si un interrupteur arrive en fin de vie, il peut simplement être remplacé par un autre. Pour cette application, les ILS sont plus adaptés que les capteurs à effet de Hall.


## Autre piste explorée: les alertes

Nous avons pensé à intégrer un système d'alarme à notre dispotif. En théorie, des flags seraient envoyés vers la plateforme Ubidots afin de déclencher une alerte pour prévenir l'apiculteur d'un danger. Elles peuvent être dirigées vers une boîte mail.
Cinq types d'alerte ont été développées correspondant chacune à un évènement particulier :
  - essaimage d'une partie de la colonie : l'harmonique fondamentale du son est autour de 200Hz, on peut remarquer une augmentation de la densité spectrale en-dessous de 100Hz et une diminution soudaine de température est observée.
  - reine manquante : la fondamentale tourne autour de 400Hz et une diminution soudaine de la masse de la ruche est observée.
  - état de stress des ouvrières : la fondamentale tourne autour de 300Hz au lieu de 200Hz en temps normal, il y a également une présence éventuelle d'individus étrangers à 150Hz ou moins.
  - chute de la ruche : les températures et humidités intérieures et extérieures sont identiques, le masse relevée est devenue nulle.
  - bas niveau de batterie : charge relevée à 10% ou moins.
  

# Réalisation du prototype sur circuit imprimé (PCB)

Cette seconde étape nous a permis d'intégrer l'ensemble des composants de notre système de façon plus robuste, tout en optimisant la densité d'intégration. Nous nous sommes appuyés sur un schéma synthétique de notre système.

![](https://i.imgur.com/vi1HfQr.png)

A partir de cela, nous avons pu développer notre circuit imprimé.

![](https://i.imgur.com/Rx3gHyQ.png)

Notamment, nous avons rajouté des régulateurs de tension (LDO) pour autoriser ou non l'alimentation de certains éléments : la jauge de contrainte, les DHT22 et le capteur sonore. Ceux-ci font office d'interrupteurs pour ces capteurs. 

Ces LDO peuvent aussi permettre de convertir l'alimentation d'entrée (par exemple convertir du 5V en 3V3) et à terme nous permettre de ne plus passer par le ST-Link du microcontôleur. Un connecteur Grove permet d'alimenter le microcontrôleur, via le port USB de la carte LiPo Rider Pro (gestionnaire d'alimentation avec batterie et panneau solaire), lorsque le câble USB n'est pas branché. Un second connecteur est utilisé pour l'analyse de la luminosité et de la charge de la batterie. Dans le premier cas, un montage soustracteur à base d'AOP sert à déterminer la tension aux bornes d'une résistance de Shunt, positionnée en sortie du panneau solaire. Le courant délivré par ce dernier est alors déterminable, par loi d'Ohm, et est proportionnel à la luminosité captée. Dans le second cas, un pont diviseur de tension permet de calculer la valeur analogique de la charge de batterie.

Enfin, il est conseillé d'intégrer puis tester les fonctions une après l'autre afin de s'assurer du fonctionnement global du système. Dans un souci de solidité, d'autres connecteurs Grove ont servi à brancher les capteurs de température, d'humidité et de son. Des rallonges, renforcées par des gaines thermiques, ont été créées spécialement pour les capteurs destinés à être placés dans la ruche ou à l'extérieur du boitier et de la ruche.

# Pistes à utiliser pour réduire la consommation du système

Afin de consommer moins et de faire durer la batterie plus longtemps, plusieurs solutions peuvent être utilisées:

   * Des Solder Bridge permettent l'alimentation de la carte par un cable micro-USB avec le ST-Link. Or cette partie consomme beaucoup, on a donc intérêt, une fois que l'on a plus besoin de reprogrammer le microcontrôleur par le cable micro-USB, à enlever les Solder Bridges et alimenter par le connecteur Grove prévu à cet effet.

   * Il y a deux LED sur le microcontrôleur, on peut laisser la petite LED qui consomme peu pour pouvoir s'assurer du fait que le système tourne. La grosse LED peut être enlevée.
   
   * Nous pouvons avoir recours à des fonctions spéciales (utilisables sur Mbed Studio ou sur Mbed Online mais avec une version de la librairie mbed-os plus vieille). Ces fonctions telles aue le sleep, le deepsleep ou le standby permettent de diminuer fortement la consommation du STM32.
   
   * L'utilisation des LDO permet de pouvoir couper l'alimentation des capteurs lorsque l'on ne s'en sert pas et permet ainsi de ne pas consommer encore plus de courant.




