# Projet Vision

Projet réaliser avec [Askar SEYADOUMOUGAMMADOU](https://github.com/Amst64).  
  

Dans ce projet, on cherche à  implémenter un algorithme de vision sur une carte SABRE équipé d’un processeur RISC.  
L’algorithme de vision doit réaliser 2 filtrages sur une image. Les filtres sont le filtre de Sobel et le filtre Médian. Le filtre de Sobel a pour but de détecter les contours sur des images, quant au filtre Médian il est utilisé pour réduire les bruits parasites (salt et pepper) que l’on trouve sur les images.  

Ce genre de filtres peuvent être implémentés dans une voiture pour par exemple détecter les lignes continues pour avertir le conducteur s’il y a eu un franchissement de ligne, ou bien même la présence de piétons et donc éviter les risques de collision. Comme une voiture est un véhicule qui se déplace très vite, il faut que le temps de traitement des images soit le plus rapide possible pour une question de sécurité (éviter les dépassements de lignes ou bien les collisions).  

Dans ce projet, on va utiliser une carte SABRE/freescale IMX6 (ARM Cortex-A9,  quad-core )  et une webcam, pour exécuter le filtrage. Avec l’image captée par la webcam on réalise le filtrage de Sobel et Médian et l'affiche sur l’écran.  

On utilise OpenCV v2 pour avoir une image/video noir et blanc de la webcam et on applique les filtres sur l'image ou video en noir et blanc.

On utilise OpenCV v4 pour le code macos.

## Compiler et exécuter les programmes :  

Commande pour compiler le programme optimiser :  
```g++ -std=c++11 `pkg-config --cflags opencv` projet_opti.cpp `pkg-config --libs opencv` -o projet_opti```  

Commande pour exécuter le programme optimiser :  
```./projet_opti 480 640 5```  
La commande ci-dessus va exécuter le programme avec une image de largeur 480 pixels et de longueur 640 pixels et avec une matrice kernel de taille 5*5 pour le filtre médian.  
    
Commande pour comiler le programme naïve :  
```g++ -std=c++11 `pkg-config --cflags opencv` projet_naive.cpp `pkg-config --libs opencv` -o projet_naive```  


Commande pour exécuter le programme naïve :  
```./projet_naive 480 640 5```  
La commande ci-dessus va exécuter le programme avec une image de largeur 480 pixels et de longueur 640 pixels et avec une matrice kernel de taille 5*5 pour le filtre médian.